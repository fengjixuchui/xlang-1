//
// Created by voidptr on 2020/2/15.
//

#pragma once

#include <iostream>
#include <vector>
using namespace std;

extern vector<string> Keywords;
extern vector<string> Separarers;
extern vector<string> Operators;
extern vector<string> Filters;
extern vector<string> Strings;

class Token{
public:
    enum class Type{
        Keyword,
        Separarer,
        Operator,
        Number,
        Identifier,
        String
    };
    struct Position{
        string file;
        size_t line;
        size_t offset;
    };
    Position position;
    string content;
    Type type;
};

