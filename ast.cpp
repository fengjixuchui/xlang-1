//
// Created by voidptr on 2020/2/23.
//

#include "ast.h"


Ast SynParse(vector<Token> tokens){
    Ast result(tokens);
    result.parse();
    return result;
}


Ast::Ast(vector<Token> _tokens) : tokens(_tokens) , pointer(0) , rootNode(new Node()){

}

void Ast::parse() {
    while(pointer < tokens.size()){
        walkToken();
    }
}

Token Ast::getNextToken() {
    Token result;
    if(this->pointer >= this->tokens.size()){
        result.type = Token::TokenType::EndOfToken;
    }else {
        result = this->tokens[this->pointer];
    }
    this->pointer++;
    return result;
}

void Ast::walkToken() {
    Token t = getNextToken();
    if(t.type == Token::TokenType::EndOfToken){
        return;
    }else if(t.type == Token::TokenType::Keyword){
        if(t.content == "import"){

        }
    }else if(t.type == Token::TokenType::Separarer){
        if(t.content == ";"){

        }
    }
}


