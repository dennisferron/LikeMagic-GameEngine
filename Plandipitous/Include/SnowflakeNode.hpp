#pragma once

#include <cstdlib>

#include "boost/unordered_set.hpp"
#include "boost/unordered_map.hpp"
#include "boost/fusion/iterator/advance.hpp"
#include "boost/fusion/include/advance.hpp"

namespace Plandipitous {

typedef int Token;
class SnowflakeNode;

struct INodeFactory
{
    virtual SnowflakeNode* get(Token token) = 0;
};

struct ITokenSource
{
    virtual Token take() = 0;
};

struct Probability
{
};

class SnowflakeNode
{

public:

    static const Token no_token = -1;
    static const Token terminator = 0;

private:

    class Edge
    {
    public:

        enum EdgeTypes
        {
            no_direction = -1,
            left_parent = 0,
            left_chain = 1,
            left_child = 2,
            right_child = 3,
            right_chain = 4,
            right_parent = 5
        };

    private:

        struct Link
        {
            SnowflakeNode* node;
            double weight;
        };

        typedef boost::unordered_map<Token, Link> LinkSet;
        LinkSet links;
        EdgeTypes edge_type;
        INodeFactory& node_factory;

    public:

        struct Tracker
        {

            // Tracks which paths are taken and which still open when generating a tree.
            EdgeTypes const parent;
            EdgeTypes const child;
            EdgeTypes const chain;

            int depth;

            Tracker()
                : parent(no_direction), child(no_direction), chain(no_direction), depth(0)
            {
            }

            bool has_parent() const
            {
                return parent != -1;
            }

            bool has_child() const
            {
                return child != -1;
            }

            bool has_chain() const
            {
                return chain != -1;
            }

            static bool is_parent(EdgeTypes direction)
            {
                return direction == left_parent || direction == right_parent;
            }

            static bool is_child(EdgeTypes direction)
            {
                return direction == left_child || direction == right_child;
            }

            static bool is_chain(EdgeTypes direction)
            {
                return direction == left_chain || direction == right_chain;
            }

            static EdgeTypes opposite(EdgeTypes direction)
            {
                switch (direction)
                {
                    case left_parent:  return right_child;
                    case left_chain:   return right_chain;
                    case left_child:   return right_parent;
                    case right_child:  return left_parent;
                    case right_chain:  return left_chain;
                    case right_parent: return left_child;
                    default: return no_direction;
                }
            }

            bool can_go(EdgeTypes direction) const
            {
                // Don't turn backwards while chaining.
                if (has_chain() && chain == direction)
                    return false;

                // Don't try to create multiple roots for the tree.
                if (has_parent() && is_parent(direction))
                    return false;

                // Don't turn back down a branch that led up here.
                if (has_child() && child == direction)
                    return false;

                return true;
            }

            Tracker go(EdgeTypes direction) const
            {
                // If going from child to parent, only rule is don't come back to same child.
                // Parent clears because our parent is allowed to find a parent.
                // Chain clears because our parent is allowed to itself be in its own chain.
                // Direction is opposite because from point of view of parent, we are child.
                if (is_parent(direction))
                    return { no_direction, opposite(direction), no_direction, depth-1 };

                // If going from parent to child, can't go to any parent again that level.
                // Chain and children reset so the child can visit its own chain and children.
                if (is_child(direction))
                    return { opposite(direction), no_direction, no_direction, depth+1 };

                // If chaining, we must not forget the fact if we have a parent or not anywhere in chain.
                // Otherwise we might try to create a different root when we have one already at other end.
                // Child state is wiped out though because the child only concerns our chain predecessor.
                if (is_chain(direction))
                    return { parent, no_direction, opposite(direction), depth };
            }

            Tracker check_parent(Tracker other)
            {
                if (other.has_parent())
                    return { other.parent, child, chain };
                else
                    return { parent, child, chain };
            }
        };

        Edge(EdgeTypes edge_type_, INodeFactory& node_factory_)
            : edge_type(edge_type_), node_factory(node_factory_)
        {
        }

        Link& get_or_add(Token const& token)
        {
            auto this_link = links.find(token);

            if (this_link == link.end())
            {
                SnowflakeNode* new_node = node_factory.get(token);
                links[token] = Link { new_node, 0 };
            }
            else
            {
                return *this_link;
            }
        }

        bool is_terminated() const
        {
            return links.find(node_factory.terminator()) != links.end();
        }

        bool empty_or_terminated() const
        {
            return links.empty() || is_terminated();
        }

        void terminate()
        {
            get_or_add(node_factory.terminator());
        }

        void add_open_edges(Tracker path, boost::unordered_set<Edge>& results)
        {
            if (path.can_go(edge_type) && !is_terminated() && !results.contains(this))
            {
                Tracker this_path = path.go(edge_type);
                for (auto kv : links)
                {
                    result.insert(edges[i]);
                    kv.second->open_edges(this_path, results)
                }
            }
        }

        void assign_tokens(ITokenSource* tokens, Edge::Tracker path) const
        {
            if (path.can_go(edge_type))
                for (auto kv : links)
                    if (kv.first != node_factory->terminator())
                        kv.second->node->assign_tokens(tokens, path.go(edge_type));
        }

        void set_weights(double weight, Edge::Tracker path)
        {
            for (auto kv : links)
            {
                kv.second.weight = weight;

                if (path.can_go(edge_type))
                    kv.second.node->set_weights(weight, path.go(edge_type));
            }
        }

        void add_weights(Edge* that_edge, Edge::Tracker path)
        {
            for (auto kv : other_edge.links)
            {
                Link& link = get_or_add(kv.first);
                link.weight += kv.second.weight;

                if (path.can_go(edge_type) && kv.first != node_factory->terminator())
                    link.node->add_weights(kv.second.node, path.go(edge_type));
            }
        }

        void rate(Edge* other_edge, Probability& result)
        {
            for (auto kv : other_edge.links)
            {
                Link& link = get_or_add(kv.first);
                result.add(link.weight);

                if (kv.first != node_factory->terminator())
                    link.node->rate(kv.second.node, result);
            }
        }

        double weight(Edge* test_edge)
        {
            Probability result;
            for (auto kv : other_edge.links)
            {
                Link& link = get_or_add(kv.first);
                result.add(link.weight);

                if (kv.first != node_factory->terminator())
                    link.node->add_weights(kv.second.node, path.go(edge_type));
            }
        }

        SnowflakeNode* choose()
        {
            double sum = 0;
            for (auto kv : links)
                sum += kv.second.weight;

            double average = sum / links.size();
            double target = average * (rand() % (links.size() * 100)) / 100.0;

            double so_far = 0.0;
            auto iter = links.begin();
            while (so_far < target)
            {
                so_far += iter->weight;
                ++iter;
            }

            return iter->node;
        }

    };  //struct Edge

    Token token;
    Edge edges[6];

public:

    SnowflakeNode(Token token_) : token(token_)
    {
    }

    SnowflakeNode(const SnowflakeNode& other) = delete;

    void choose(std::vector<Token>& result, Edge::Tracker path)
    {
        for (auto e : edges)
        {
            if (path.can_go(e.edge_type))
            {
                SnowflakeNode* node = e.choose();

                if (node.token != node_factory.terminator())
                    node.choose(result, path.go(e.edge_type));

                if (e.edge_type == Edge::left_child)
                    result.push_back(this->token);
            }
        }
    }

    // Top down only
    void rate(SnowflakeNode* other, Probability& result)
    {
        for (int i=Edge::left_parent+1; i < Edge::right_parent; ++i)
            if (!other->edges[i].is_terminated())
                edges[i].rate(other->edges[i], result);
    }

    void add_open_edges(Edge::Tracker path, boost::unordered_set<Edge>& results)
    {
        for (auto e : edges)
            if (!Edge::Tracker::is_parent(e))
                e.add_open_edges(path, results);
    }

    void terminate()
    {
        boost::unordered_set<Edge> open_set;
        open_edges(Edge::Tracker(), open);
        for (auto& e : open_set)
            e.terminate();
    }

    SnowflakeNode* chain_leftmost()
    {
        if (!edges[Edge::left_chain].empty_or_terminated())
            return edges[Edge::left_chain].node;
        else
            return this;
    }

    std::pair<SnowflakeNode*, Edge::Tracker> prime_ancestor(Edge::Tracker path = Edge::Tracker())
    {
        std::pair<SnowflakeNode*, Edge::Tracker> best { this->chain_leftmost(), 0 };
        for (auto e : edges)
            if (!Edge::Tracker::is_child(e.edge_type) && path.can_go(e.edge_type) && !e.empty_or_terminated())
            {
                auto test = e.node->prime_ancestor(path.go(e.edge_type));
                if (test.second.depth < best.second.depth)
                    best = test;
            }

        return best;
    }

    static SnowflakeNode* grow_new_random_tree(int target_count, INodeFactory* factory)
    {
        Token no_token = factory->no_token();
        SnowflakeNode* current_node = factory->get(no_token);

        boost::unordered_set<Edge*> open_set;

        for (int count=1; count <= target_count; ++count)
        {
            // We simply don't add parent edges in add_open_edges,
            // therefore the tree can't grow multiple roots, it
            // can only grow downward or to the left or right.
            current_node->add_open_edges(current_path, open_set);

            auto edge_iter = open_set.begin();
            boost::advance(edge_iter, rand() % open_set.size());
            current_node = edge_iter->get_or_add(no_token);
            open_set.erase(edge_iter);
        }

        SnowflakeNode* result = current_node->prime_ancestor();
        result->terminate();
        return result;
    }

    void assign_tokens(ITokenSource* tokens, Edge::Tracker path)
    {
        for (Edge& e : edges)
        {
            e->assign_tokens(path);

            if (e.edge_type == Edge::left_child)
                this->token = tokens->take();
        }
    }

    void set_weights(double weight, Edge::Tracker path)
    {
        for (Edge& e : edges)
            e.set_weights(weight, path);
    }

    void add_weights(SnowflakeNode* other_node, Edge::Tracker path)
    {
        for (int i=Edge::left_parent; i<=Edge::right_parent; ++i)
            edges[i].add_weights(other_node->edges[i], path);
    }

};

}
