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
            left_parent = 0,
            left_chain = 1,
            left_child = 2,
            right_child = 3,
            right_chain = 4,
            right_parent = 5
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

        // TODO:  Allow existing learned nodes to create new tree based on existing weights
        void grow(TokenSource tokens)
        {

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
};

}
