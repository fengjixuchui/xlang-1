//
// Created by voidptr on 2020/2/23.
//
#pragma once
#include <vector>
#include "token.h"
#include <memory>
using namespace std;
enum class NodeType{
    Unknown,
    Expression
};
class Ast;
class Node;
class Expression;
class Variable;
class Call;
class Identifier;
/* Ast */
class Ast{
public:
    shared_ptr<Node> rootNode;

    Token nowToken;
    vector<Token> tokens;
    size_t pointer;

    Ast(vector<Token> _tokens);
    shared_ptr<Node> walkToken();
    Token getNextToken();
    void parse();
    //parse
    shared_ptr<Expression> parseExpression();
    shared_ptr<Expression> parseIdentifier();
    //make
    shared_ptr<Expression> makeVariable(string type,string name);
    shared_ptr<Expression> makeCall(string target);
    shared_ptr<Expression> makeFunction(string returntype,string name);
    shared_ptr<Expression> makeNumber(string value);
    //error system
    bool printFile = true;
    void printError(int ErrorID,vector<string> arg = {});
};
/* Node */
class Node{
public:
    NodeType type = NodeType::Unknown;
};
class Expression : public Node{
public:
    NodeType type = NodeType::Expression;
};
class Call : public Expression{
public:
    Call(shared_ptr<Identifier> _target,vector<Expression> _args = {});
    shared_ptr<Identifier> target;
    vector<Expression> args;
};
class Variable : public Expression{
public:
    Variable(shared_ptr<Identifier> _type,shared_ptr<Identifier> _name);
    shared_ptr<Identifier> type;
    shared_ptr<Identifier> name;
    shared_ptr<Expression> value;
};
class Identifier : public Expression{
public:
    Identifier(string _content);
    string content = "";
};
class Function : public Expression{
public:
    Function(shared_ptr<Identifier> _returntype,shared_ptr<Identifier> name);
    shared_ptr<Identifier> returntype;
    shared_ptr<Identifier> name;
};
class Number : public Expression{
public:
    Number(string _content);
    string content;
};
Ast SynParse(vector<Token> tokens);