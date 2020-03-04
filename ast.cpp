//
// Created by voidptr on 2020/2/23.
//

#include "ast.h"
Ast SynParse(vector<Token> tokens){
    Ast result(tokens);
    result.parse();
    return result;
}


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

void Ast::walkToken() {
    Token t = getNextToken();
    if(t.type == Token::TokenType::Identifier){
        string foo;
        int lasttype = 2;//1:Identifier 2:(.)
        while(t.type == Token::TokenType::Identifier || t.content == ".") {
            if(t.type == Token::TokenType::Identifier && lasttype == 1){
                break;
            }
            foo += t.content;
            lasttype = (t.type == Token::TokenType::Identifier)? 1 : 2;
            t = getNextToken();
        }
        if(t.type == Token::TokenType::Identifier) {
            Variable node(foo, t.content);
        }else if(t.content == "("){
            Call node(foo);
        }
        cout << "success!";
    }
}

void Ast::printError(int ErrorID, string args[]) {
    if(printFile){
        cerr << "at " << nowToken.position.file << ":";
        printFile = false;
    }

    if(ErrorID >= 5000){
        exit(ErrorID);
    }
}


Variable::Variable(string _type,string _name)  : type(_type) , name(_name){

}

Call::Call(string _target,vector<Expression> _args) : target(_target) , args(_args) {

}
