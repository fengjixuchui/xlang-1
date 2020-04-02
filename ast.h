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
class Type;
class Identifier;

class Statement;
class Import;

/* Ast And Parser */
class Ast{
public:
    Ast(vector<Token> _tokens);

    //token
    Token pointer_token;
    vector<Token> tokens;
    size_t pointer;
    Token getNextToken();

    //node
    shared_ptr<Node> rootNode;

    //parser
    void parse();
    shared_ptr<Node> walkToken();


    //handles
    shared_ptr<Import> handleImport();
    shared_ptr<Type> handleType();
    shared_ptr<Identifier> handleIdentifier();

    //error system
    bool printFile = true;
    void printError(int ErrorID,vector<string> arg = {});
};
/* Node */

class Node{
public:
    virtual string getNodeType();
};
class Expression : public Node{
public:
    virtual string getNodeType();
};
class Statement : public Node{
public:
    virtual string getNodeType();
};


/*
 * xxxx...
 */
class Identifier : public Expression{
public:
    virtual string getNodeType();
    string text;
};
/*
 * xxx.xxx.xxx...
 */
class Type : public Expression{
public:
    virtual string getNodeType();
    string getText();
    vector<shared_ptr<Node>> Nodes;
};
/*
 * class xxx{
 * [body]
 * }
 */
class Class : public Expression{
public:
    virtual string getNodeType();
    vector<Node> Nodes;
};

/*
 * import {xxx}
 * import xxx
 */
class Import : public Statement{
public:
    virtual string getNodeType();
    Import(vector<shared_ptr<Type>> _type);
    Import(shared_ptr<Type> _type);
    vector<shared_ptr<Type>> type;
};





Ast SynParse(vector<Token> tokens);