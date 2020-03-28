//
// Created by voidptr on 2020/3/6.
//

#include <utility>

#include "ast.h"
using namespace std;

Import::Import(vector<shared_ptr<Type>> _type) : type(std::move(_type)) {

}
Import::Import(shared_ptr<Type> _type){
    type.push_back(_type);
}