//
// Created by voidptr on 2020/2/15.
//
#include <iostream>
#include <vector>
#include <fstream>
#include "token.h"
#include "lexer.h"
#include "ast.h"
using namespace std;
void printVersion(){
    cout << "XLang" << " Dev 0.1 " << endl;
    cout << "Github: https://github.com/lwingteam/xlang" << endl;
}
int main(int argc,char *argv[]){
    vector<string> sources;
    for (int i = 1; i < argc; ++i) {
        string element = argv[i];
        bool handled = false;
        if(element == "-v" || element == "--version"){
            printVersion();
            handled = true;
        }
        if (!handled){
            //如果参数没有被处理
            if(element.substr(0,1) == "-"){
                //以-开头的报未知参数
                cerr << "Unknown Argument " << element << endl;
            }else{
                //否则当做源代码文件处理
                sources.push_back(element);
            }
        }
    }
    for(auto source : sources){
        fstream fs(source);
        stringstream ss;
        ss << fs.rdbuf();
        fs.close();

        vector<Token> tokens = LexParser(ss.str(), source);
        Ast ast = SynParse(tokens);
    }
    return 0;
}
