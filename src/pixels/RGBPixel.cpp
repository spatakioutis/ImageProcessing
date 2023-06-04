#include "RGBPixel.hpp"

RGBPixel::RGBPixel(const RGBPixel& p){
    this->red = p.red;
    this->green = p.green;
    this->blue = p.blue;
}
RGBPixel::RGBPixel(unsigned char r, unsigned char g, unsigned char b){
    red = r;
    green = g;
    blue = b;
}

unsigned char RGBPixel::getRed() const{
    return red;
}
unsigned char RGBPixel::getGreen() const{
    return green;
}
unsigned char RGBPixel::getBlue() const{
    return blue;
}

void RGBPixel::setRed(int r){
    red = (unsigned char) r;
}
void RGBPixel::setGreen(int g){
    green = (unsigned char) g;
}
void RGBPixel::setBlue(int b){
    blue = (unsigned char) b;
}

void RGBPixel::swap(RGBPixel& p){
    RGBPixel temp;

    temp = p;
    p = *this;
    *this = temp;
}