#include "Token.hpp"

Token::Token(const string& name, Image* ptr){
    this->name = name;
    this->ptr = ptr;
}

Token::~Token(){
    if (dynamic_cast<GSCImage*>(ptr)){
        delete dynamic_cast<GSCImage*>(ptr);
    }
    else {
        delete dynamic_cast<RGBImage*>(ptr);
    }
}

string Token::getName()const {return name;}
Image* Token::getPtr()const {return ptr;}

void Token::setName(const string& name){
    this->name = name;
}
void Token::setPtr(Image* ptr){
    this->ptr = ptr;
}
