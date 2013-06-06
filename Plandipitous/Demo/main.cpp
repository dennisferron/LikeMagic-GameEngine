#include <iostream>
using namespace std;

#include "SnowflakeNode.hpp"
using namespace Plandipitous;

class ITokenFactory
{
public:
    virtual Token get(std::string word) = 0;
    virtual Token terminator() = 0;
};

class TokenFactory
{
private:
    boost::unordered_map<std::string, Token> words;
    boost::unordered_map<std::string, Token> words;

public:
    virtual Token get(std::string word)
    {
        auto iter = words.find(token);
        if (iter != nodes.end())
        {
            return iter->second;
        }
        else
        {
            SnowflakeNode* node = new SnowflakeNode(token);
            nodes[token] = node;
            return node;
        }
    }

    std::string getWord(Token token)
    {
        return words[token];
    }
};

class TokenSource : public ITokenSource
{
private:
    ITokenFactory& token_factory;
    std::vector<std::string> words;

public:
    TokenSource(ITokenFactory& token_factory_, std::vector<std::string> words_)
        : token_factory(token_factory_), words(words_.crbegin(), words_.crend())
    {
    }

    virtual Token take()
    {
        if (words.size() == 0)
            return token_factory.terminator();
        else
        {
            std::string word = words.back();
            words.pop_back();
            return token_factory.get(word);
        }
    }
};

class NodeFactory : public INodeFactory
{
private:
    boost::unordered_map<Token, SnowflakeNode*> nodes;

public:
    virtual SnowflakeNode* get(Token token)
    {
        auto iter = nodes.find(token);
        if (iter != nodes.end())
        {
            return iter->second;
        }
        else
        {
            SnowflakeNode* node = new SnowflakeNode(token);
            nodes[token] = node;
            return node;
        }
    }
};


int main()
{
    NodeFactory learned_nodes;
    NodeFactory training_nodes;

    std::cout << "Press enter..." << std::endl;
    std::cin.ignore( 99, '\n' );
    return 0;
}
