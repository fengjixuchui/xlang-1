//
// Created by voidptr on 2020/3/6.
//

#include <utility>

#include "ast.h"
using namespace std;
/* node */
string Node::getNodeType() {
    return "node";
}

/* expression */
string Expression::getNodeType() {
    return "expression";
}
/* identifier */
string Identifier::getNodeType() {
    return "identifier";
}
/* type */
string Type::getNodeType() {
    return "type";
}


/* statement */
string Statement::getNodeType() {
    return "statement";
}
/* import */
Import::Import(vector<shared_ptr<Type>> _type) : type(std::move(_type)) {

}
Import::Import(shared_ptr<Type> _type){
    type.push_back(_type);
}
string Import::getNodeType() {
    return "import";
}




