#pragma once

#include "boost/unordered_set.hpp"

namespace Plandipitous {

class SnowflakeNode
{
private:

    struct Link
    {
        SnowflakeNode* node;
        double weight;
    };

    typedef boost::unordered_map<std::string, Link> LinkSet;

    std::string token;
    LinkSet edges[6];

    static int const left_parent = 0;
    static int const left_chain = 1;
    static int const left_child = 2;
    static int const right_child = 3;
    static int const right_chain = 4;
    static int const right_parent = 5;

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
