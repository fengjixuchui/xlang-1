//
// Created by voidptr on 2020/2/23.
//
#pragma once
#include <vector>
#include "token.h"

using namespace std;

class Ast;
class Node;

/* code */


class Ast{
public:
    Node *rootNode;

    Token nowToken;
    vector<Token> tokens;
    size_t pointer;

    Ast(vector<Token> _tokens);
    void walkToken();
    Token getNextToken();
    void parse();

    //error system
    bool printFile = true;
    void printError(int ErrorID,string arg[] = {});
};

class Node{
};
class Expression : public Node{
};
class Call : public Expression{
public:
    Call(string _target,vector<Expression> _args = {});
    string target;
    vector<Expression> args;
};
class Variable : public Expression{
public:
    Variable(string _type,string _name);
    string type = "";
    string name = "";
};

Ast SynParse(vector<Token> tokens);