//
// Created by voidptr on 2020/2/23.
//
#pragma once
#include <vector>
#include "token.h"
#include <memory>
using namespace std;

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
    void walkToken();
    Token getNextToken();
    void parse();

    //makes
    shared_ptr<Expression> parseIdentifier();
    shared_ptr<Expression> makeVariable(string type,string name);
    shared_ptr<Expression> makeCall(string target);
    shared_ptr<Expression> makeFunction(string returntype,string name);
    //error system
    bool printFile = true;
    void printError(int ErrorID,string arg[] = {});
};
/* Node */
class Node{
};
class Expression : public Node{
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
Ast SynParse(vector<Token> tokens);