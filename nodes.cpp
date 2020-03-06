//
// Created by voidptr on 2020/3/6.
//

#include "ast.h"
using namespace std;


Variable::Variable(shared_ptr<Identifier> _type,shared_ptr<Identifier> _name)  : type(move(_type)) , name(move(_name)){

}

Call::Call(shared_ptr<Identifier> _target,vector<Expression> _args) : target(move(_target)) , args(_args) {

}

Identifier::Identifier(string _content) : content(_content) {
}
