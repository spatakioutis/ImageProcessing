#include "GSCPixel.hpp"

GSCPixel::GSCPixel(const GSCPixel& p){
    this->value = p.value;
}

GSCPixel::GSCPixel(unsigned char value){
    this->value = value;
}

unsigned char GSCPixel::getValue() const{
    return value;
}

void GSCPixel::setValue(unsigned char value){
    this->value = value;
}

void GSCPixel::swap(GSCPixel& p){
    GSCPixel temp;

    temp = p;
    p = *this;
    *this = temp;
}
