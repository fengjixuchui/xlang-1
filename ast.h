//
// Created by voidptr on 2020/2/23.
//
#pragma once
#include <vector>
#include "token.h"
using namespace std;
class Ast;
class Node;

class Ast{
public:
    Node *rootNode;
};

class Node{

};

Ast SynParser(vector<Token> ts){

}