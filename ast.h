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
class Import;
class Type;
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
    //handles
    shared_ptr<Import> handleImport();
    shared_ptr<Type> handleType();
    //error system
    bool printFile = true;
    void printError(int ErrorID,vector<string> arg = {});
};
/* Node */

class Node{
};
class Expression : public Node{
};



/*
 * xxx.xxx.xxx...
 */
class Type : public Expression{
public:
    string getText();
    vector<Node> Nodes;
};


/*
 * import {xxx}
 * import xxx
 */
class Import : public Expression{
public:
    Import(vector<shared_ptr<Type>> _type);
    Import(shared_ptr<Type> _type);
    vector<shared_ptr<Type>> type;
};





Ast SynParse(vector<Token> tokens);