//
// Created by voidptr on 2020/2/15.
//
#include "lexer.h"

#define __save_and_clear(ty) {\
Token t;\
t.content = buffer;\
t.type = (ty);\
Token::TokenPosition position;\
position.file = file;\
position.line = line;\
position.offset = stream.tellg();\
t.position = position;\
}

vector<Token> LexParser(string source ,string file){
    stringstream stream(source);
    char character = ' ';
    //注释等级：0当前不在注释状态，1当前属于单行注释，2当前属于多行注释，3当前属于多行注释疑似结尾
    bool note_level = 0;
    bool string_level = false;
    bool keep_character = false;
    string buffer = "";
    size_t line = 0;
    while (stream.get(character) && stream.good() && !stream.eof()){
        /* 注释解决系统 */
        if(note_level != 0 && (character != '\n' || character != '*' || character != '/')){
            //当前在注释状态中
            if(note_level == 3 && character != '/'){
                //当在3多号注释疑似结尾时 没有 读取到斜杠
                note_level = 2;
            }
            continue;
        }else if(character == '\n' && note_level == 1){
            //当在1单行注释读取到了换行符号
            note_level = 0;
        }else if(character == '*' && note_level == 2){
            //当在2多行注释中读取到了星号
            note_level = 3;
        }else if(character == '/' && note_level == 3){
            //当在3多号注释疑似结尾时读取到了斜杠
            note_level = 0;
        }
        /* 正常处理 */
        if(InVector({character}, Filters)){
            //当当前字符在 不处理字符 列表中
            if(character == '\n'){
                line++;
            }
            continue;
        }
        if(IsLetter(character)){
            while (IsLetter(character)){
                //读取数据直到不是字母为止
                buffer += character;
                stream.get(character);
            }
            if(InVector(buffer,Keywords)){
                //如果是关键字
                __save_and_clear(Token::TokenType::Keyword);
            }else{
                //如果不是关键字
            }
            keep_character = true;
        }else{
            //判断是否为注释开头
        }
    }
}

bool IsLetter(char s){
    return ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'));
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