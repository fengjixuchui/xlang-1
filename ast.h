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

    vector<Token> tokens;
    size_t pointer;

    Ast(vector<Token> _tokens);
    void walkToken();
    Token getNextToken();
    void parse();
};

class Node{
};

Ast SynParse(vector<Token> tokens);