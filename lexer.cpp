//
// Created by voidptr on 2020/2/15.
//
#include "lexer.h"
#define __save_and_clear(ty) {\
Token t;\
t.content = buffer;\
t.type = (ty);\
Token::Position position;\
position.file = file;\
position.line = line;\
position.offset = stream.tellg();\
t.position = position;\
result.push_back(t);\
buffer.clear();\
}
#define __not_eof(s)  (s).good() && !(s).eof()
vector<Token> LexParser(string source ,string file){
    stringstream stream(source);
    //当前读入的字符
    char character = ' ';
    string character_str = " ";
    //注释等级：0当前不在注释状态，1当前属于单行注释，2当前属于多行注释，3当前属于多行注释疑似结尾
    int note_level = 0;
    //保留字符
    bool keep_character = false;
    string buffer = "";
    size_t line = 0;
    vector<Token> result;
    while (__not_eof(stream)){
        /* 处理保留字符 */
        if(!keep_character) {
            stream.get(character);
            if(!__not_eof(stream)){
                break;
            }
        }else{
            keep_character = false;
        }
        character_str = {character};
        if(note_level != 0){
            if(character == '\n' && note_level == 1){
                note_level = 0;
            }else if(character == '*' && note_level == 2){
                note_level = 3;
            }else if(character == '/' && note_level == 3){
                note_level = 0;
            }else if(note_level == 3){
                note_level = 2;
            }
            if(note_level == 0){
                buffer.clear();
            }
            continue;
        }
        /* 正常处理 */
        if(InVector(character_str, Filters)){
            //当当前字符在 不处理字符 列表中
            if(character == '\n'){
                line++;
            }
            continue;
        }
        /* 处理注释语法 */
        if(buffer == "/"){
            if(character == '*'){
                note_level = 2;
            }else if(character == '/'){
                note_level = 1;
            }else{
                __save_and_clear(Token::Type::Operator);
                keep_character = true;
            }
            continue;
        }
        if(IsLetter(character)){
            /* 当读到了字母 */
            while (IsLetter(character) && __not_eof(stream)){
                //读取数据直到不是字母为止
                buffer += character;
                stream.get(character);
            }
            if(InVector(buffer,Keywords)){
                //如果是关键字
                __save_and_clear(Token::Type::Keyword);
            }else{
                //如果不是关键字
                while ((IsLetter(character) || IsNumber(character)) && __not_eof(stream)){
                    //读取数据直到不是字母或者数字为止
                    buffer += character;
                    stream.get(character);
                }
                __save_and_clear(Token::Type::Identifier);
            }
            keep_character = true;
        }else if(IsNumber(character)){
            /* 读到了数字 */
            while (IsNumber(character) && __not_eof(stream)){
                buffer += character;
                stream.get(character);
            }
            if((buffer == "0" && character == 'x') || character == '.'){
                bool hexnumber = character == 'x';
                do {
                    buffer += character;
                    stream.get(character);
                }while ((hexnumber ? IsHexNumber(character) : IsNumber(character)) && __not_eof(stream));
            }
            __save_and_clear(Token::Type::Number);
            keep_character = true;
        }else if(InVector(character_str,Operators)){
            /* 读取到了符号 */
            buffer += character;
            if(character != '/') {
                __save_and_clear(Token::Type::Operator);
            }

        }else if(InVector(character_str, Separarers)){
            buffer += character;
            __save_and_clear(Token::Type::Separarer);
        }
    }
    return result;
}

bool IsLetter(char s){
    return ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'));
}
bool IsHexNumber(char s){
    return IsNumber(s) || (s >= 'A' && s <= 'F') || (s >= 'a' && s <= 'f');
}
bool IsNumber(char s){
    return (s >= '0' && s <= '9');
}

bool InVector(string s,vector<string> v){
    for(string e : v){
        if(e == s) return true;
    }
    return false;
}