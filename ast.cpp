//
// Created by voidptr on 2020/2/23.
//

#include "ast.h"
#define __check_type(a,b) a.type == b
#define __check_value(a,b) a.content == b
////////////////////////////////////////////////////

Ast SynParse(vector<Token> tokens){
    Ast result(tokens);
    result.parse();
    return result;
}

////////////////////////////////////////////////////

Ast::Ast(const vector<Token> _tokens) : tokens(_tokens) , pointer(0) , rootNode(new Node()){

}

void Ast::parse() {
    while(pointer < tokens.size()){
        walkToken();
    }
}

Token Ast::getNextToken() {
    Token result;
    if(this->pointer >= this->tokens.size()){
        printError(5001);
    }else {
        result = this->tokens[this->pointer];
    }
    this->pointer++;
    return (nowToken = result);
}

/////////////////////////////////////////////////////

shared_ptr<Node> Ast::walkToken() {
    Token t = getNextToken();
    shared_ptr<Node> node = nullptr;
    if(__check_type(t,Token::TokenType::Keyword)){
        if(__check_value(t,"import")){
            node = handleImport();
        }else if(__check_value(t,"class")){

        }
    }
    return node;
}

shared_ptr<Import> Ast::handleImport() {
    Token t = getNextToken();
    if(__check_value(t,"{")){
        //import {xxx,xxx...}
        vector<shared_ptr<Type>> types;
        do{
            shared_ptr<Type> type = handleType();
            types.push_back(type);
            t = getNextToken();
            if(__check_value(t,"}")){
                break;
            }else if(!(__check_value(t,","))){
                printError(5003);
            }
        }while (true);
        return make_shared<Import>(types);
    }else if(__check_type(t,Token::TokenType::Identifier)){
        shared_ptr<Type> type = handleType();
        return make_shared<Import>(type);
    }else {
        printError(5002);
    }
    return nullptr;
}

shared_ptr<Type> Ast::handleType(){
    vector<Node> tokens;

}

////////////////////////////////////////////////

void Ast::printError(int ErrorID, vector<string> args) {
    if(printFile){
        cerr << "at " << nowToken.position.file << ":";
        printFile = false;
    }

    if(ErrorID >= 5000){
        exit(ErrorID);
    }
}

