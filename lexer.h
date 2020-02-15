//
// Created by voidptr on 2020/2/15.
//

#pragma once

#include <iostream>
#include "token.h"
#include <sstream>
using namespace std;

vector<Token> LexParser(string source,string file);
bool IsLetter(char s);
bool IsNumber(char s);
bool InVector(string s,vector<string> v);