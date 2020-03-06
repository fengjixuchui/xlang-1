//
// Created by voidptr on 2020/2/23.
//

#include "ast.h"
Ast SynParse(vector<Token> tokens){
    Ast result(tokens);
    result.parse();
    return result;
}

Node *getnode(shared_ptr<Node> s){
    return s.get();
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
        shared_ptr<Expression> node = parseIdentifier();
        cout << "success";
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

shared_ptr<Expression> Ast::parseIdentifier() {
    Token t = nowToken;
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

    shared_ptr<Expression> result = nullptr;
    if(t.type == Token::TokenType::Identifier) {
        result = makeVariable(foo,t.content);
    }else if(t.content == "(") {
        result = makeCall(foo);
    }
    return result;
}

shared_ptr<Expression> Ast::makeVariable(string type,string name) {
    Token t = getNextToken();
    if(t.content == "(") {
        return makeFunction(type, name);
    }
    shared_ptr<Expression> node = make_shared<Variable>(make_shared<Identifier>(type),make_shared<Identifier>(name));
    if(t.content == "="){

    }else if(t.content == ";"){

        return node;
    }else{
        printError(10001,new string{t.content});
    }
    return nullptr;
}

shared_ptr<Expression> Ast::makeCall(string target) {
    shared_ptr<Expression> node = make_shared<Call>(make_shared<Identifier>(target));


    return node;
}


