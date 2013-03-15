#pragma once

#include "boost/unordered_set.hpp"

namespace Plandipitous {

class SnowflakeNode;

template <typename Token>
struct INodeFactory
{
    virtual SnowflakeNode* get(std::string token) = 0;
};

template <typename Token>
class SnowflakeNode
{
private:

    struct Link
    {
        SnowflakeNode* node;
        double weight;
    };

    struct Edge
    {
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

        struct Tracker
        {
            // Tracks which paths are taken and which still open when generating a tree.
            EdgeTypes const parent;
            EdgeTypes const child;
            EdgeTypes const chain;

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

            bool can_grow(EdgeTypes direction) const
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
                    return { no_direction, opposite(direction), no_direction };

                // If going from parent to child, can't go to any parent again that level.
                // Chain and children reset so the child can visit its own chain and children.
                if (is_child(direction))
                    return { opposite(direction), no_direction, no_direction };

                // If chaining, we must not forget the fact if we have a parent or not anywhere in chain.
                // Otherwise we might try to create a different root when we have one already at other end.
                // Child state is wiped out though because the child only concerns our chain predecessor.
                if (is_chain(direction))
                    return { parent, no_direction, opposite(direction) };
            }

            Tracker check_parent(Tracker other)
            {
                if (other.has_parent())
                    return { other.parent, child, chain };
                else
                    return { parent, child, chain };
            }
        };

        typedef boost::unordered_map<std::string, Link> LinkSet;
        LinkSet links;
        EdgeTypes edge_type;
        INodeFactory& node_factory;

        Edge(EdgeTypes edge_type_, INodeFactory& node_factory_)
            : edge_type(edge_type_), node_factory(node_factory_)
        {
        }

        Link& get(Token const& token)
        {
            auto this_link = this_link_set.find(token);

            if (this_link == this_link_set.end())
            {
                SnowflakeNode* next = node_factory.get(token);
                this_link[token] = Link { next, weight };
                next->add(node_factory, node);
            }
            else
            {
                this_link->weight += weight;
                this_link->node->add(node_factory, node);
            }
        }

        void add(Link const& that_link)
        {
            get(that_link.node->token).weight += that_link.weight;
        }

        void add(Edge const& that_edge)
        {
            for (auto const& that_link : that_edge.links)
                add(that_link);
        }
    };

    Token token;
    Edge edges[6];

    SnowflakeNode(Token token_)
        : token(token_), edges({})
    {
    }

    int const chain_dir(int const from_dir)
    {
        return from_dir ^ 1;
    }

    static void add(NodeFactory node_factory, LinkSet& this_link_set, LinkSet& that_link_set, int const from_dir)
    {
        for (auto const& that_link : that_link_set)
        {
            std::string const& token = that_link.first;
            double weight = that_link.second.weight;
            SnowflakeNode* node = that_link.second.node;

            auto this_link = this_link_set.find(token);

            if (this_link == this_link_set.end())
            {
                SnowflakeNode* next = node_factory(token);
                this_link[token] = new Link { next, weight };
                next->add(node_factory, node);
            }
            else
            {
                this_link->weight += weight;
                this_link->node->add(node_factory, node);
            }
        }
    }

    std::pair<Link&, Link&> get_links(LinkSet& from_set, std::string const& token)
    {
        auto from_link = from_set.find(token);

        if (from_link == this_link_set.end())
        {
            SnowflakeNode* next = node_factory(token);
            from_set[token] = new Link { next, weight };
            next->add_link(opposite_dir, this);
            return std::make_pair(from_set[token], next->get_link(opposite_dir, this));
        }
        else
        {
            return std::make_pair(*from_link, next->get_link(opposite_dir, this));
        }
    }

    static void addNodes(NodeFactory node_factory, LinkSet& this_link_set, LinkSet& that_link_set)
    {
        for (auto const& that_link : that_link_set)
        {
            std::string const& token = that_link.first;
            SnowflakeNode* node = that_link.second.node;

            auto this_link = this_link_set.find(token);
            if (this_link == this_link_set.end())
            {
                SnowflakeNode* next = node_factory(token);
                this_link[token] = new Link { next, 0 };
                next->addNodes(node_factory, node);
            }
        }
    }

public:

    SnowflakeNode();
    SnowflakeNode(const SnowflakeNode& other);

    void add(NodeFactory node_factory, SnowflakeNode<Token, Link>* root, int const from_dir, )
    {
        for (int i=left_parent+1; i<right_parent; ++i)
            if (i != from_dir)
                add(node_factory, edges[i], root->edges[i]);
    }

    // TODO: Write addNodes so that both addWeights and consider
    // can just assume the path exists.

    Probability consider(SnowflakeNode<Token, Link>* root)
    {
        Probability result;

        for (int i=left_parent; i<=right_parent; ++i)
        {
            auto thisLink = getLink(edges[i], root->edges[i].token);
            double total = sumChoices(edges[i]);
            result.addBranch(thisBranch, total, thisLink.node->consider(root->edges[i]));
        }

        return result;
    }

    // TODO:  Allow existing learned nodes to create new tree based on existing weights
    SnowflakeNode* postulate(TokenSource tokens, PathTracker track)
    {
        // Sanity check that tokens.peek() == this->token.
        // Create a new node for the token
        // Look across the six Edges to guess most likely connection to next.
        // Add non-zero chance to go to one of the other edges anyway.
        // Use our NodeFactory to get next node on our side.
        // Call postulate on that node to get a proposal node.
        // Attach proposal node to result node on the edge we picked.
        // Terminate all the other Edges with appropriate termination nodes.
    }
};

}
