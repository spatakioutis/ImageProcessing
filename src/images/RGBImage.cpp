#include "RGBImage.hpp"

RGBImage::RGBImage(){
    height = 0;
    width = 0;
    max_luminocity = Pixel::MAX_LUMINOCITY;
    pixels = NULL;
}

RGBImage::RGBImage(const RGBImage& img){
    width = img.getWidth();
    height = img.getHeight();
    max_luminocity = img.getMaxLuminocity();

    //copy pixels
    pixels = new RGBPixel*[getHeight()];
    for (int i=0; i<getHeight(); i++){
        pixels[i] = new RGBPixel[getWidth()];
        for (int j=0; j<getWidth(); j++){
            this->pixels[i][j] = img.pixels[i][j];
        }
    }
}

RGBImage::RGBImage(std::istream& stream){
    int red, green, blue;

    stream >> width; 
    stream >> height;
    stream >> max_luminocity;

    pixels = new RGBPixel*[getHeight()];
    for (int i=0; i<getHeight(); i++){
        pixels[i] = new RGBPixel[getWidth()];
        for (int j=0; j<getWidth(); j++){
            stream >> red >> green >> blue;
            pixels[i][j].setRed(red);
            pixels[i][j].setGreen(green);
            pixels[i][j].setBlue(blue);
        }
    }
}

RGBImage::~RGBImage(){
    if (pixels != NULL){
        for (int i=0; i<getHeight(); i++){
            delete[] pixels[i];
        }
    }
    delete[] pixels;
}

RGBImage& RGBImage::operator = (const RGBImage& img){
    setWidth(img.getWidth());
    setHeight(img.getHeight());
    setMaxLuminocity(img.getMaxLuminocity());

    //copy pixels
    pixels = new RGBPixel*[getHeight()];
    for (int i=0; i<getHeight(); i++){
        pixels[i] = new RGBPixel[getWidth()];
        for (int j=0; j<getWidth(); j++){
            this->pixels[i][j] = img.pixels[i][j];
        }
    }

    return *this;
}

Image& RGBImage::operator !(){
    for (int i=0; i<getHeight(); i++){
        for (int j=0; j<getWidth(); j++){
            pixels[i][j].setRed(getMaxLuminocity() - pixels[i][j].getRed());
            pixels[i][j].setGreen(getMaxLuminocity() - pixels[i][j].getGreen());
            pixels[i][j].setBlue(getMaxLuminocity() - pixels[i][j].getBlue());
        }
    }
    return *this;
}

Image& RGBImage::operator *(){
    for (int i=0; i<getHeight(); i++){
        for (int j=0, k=getWidth()-1; j<k; j++, k--){
            pixels[i][j].swap(pixels[i][k]);
        }
    }
    return *this;
}

Image& RGBImage::operator *= (double factor){
    RGBPixel **new_pixels = new RGBPixel*[(int)(height*factor)];
    for (int i=0; i<(int)(height*factor); i++){
        new_pixels[i] = new RGBPixel[(int)(width*factor)];
        for (int j=0; j<(int)(width*factor); j++){
            new_pixels[i][j].setRed(new_value(*this,i,j,factor, 1));
            new_pixels[i][j].setGreen(new_value(*this,i,j,factor, 2));
            new_pixels[i][j].setBlue(new_value(*this,i,j,factor, 3));
        }
    }

    for (int i=0; i<height; i++)
        delete [] pixels[i];
    delete [] pixels;

    pixels = new_pixels;
    height =(int) (height * factor);
    width = (int) (width * factor);

    return *this;
}

int new_value(RGBImage& img, int row, int col, double factor, int type){
    int r1 = std::min((int)floor(row/factor), img.getHeight()-1);
    int r2 = std::min((int)ceil(row/factor), img.getHeight()-1);
    int c1 = std::min((int)floor(col/factor), img.getWidth()-1);
    int c2 = std::min((int)ceil(col/factor), img.getWidth()-1);

    switch (type){
        case 1: 
            return (  
    img.getRGBPixel(r1,c1).getRed() + 
    img.getRGBPixel(r1,c2).getRed() + 
    img.getRGBPixel(r2,c1).getRed() + 
    img.getRGBPixel(r2,c2).getRed()  ) / 4;
        case 2: 
            return (  
    img.getRGBPixel(r1,c1).getGreen() + 
    img.getRGBPixel(r1,c2).getGreen() + 
    img.getRGBPixel(r2,c1).getGreen() + 
    img.getRGBPixel(r2,c2).getGreen()  ) / 4;
        case 3: 
            return (  
    img.getRGBPixel(r1,c1).getBlue() + 
    img.getRGBPixel(r1,c2).getBlue() + 
    img.getRGBPixel(r2,c1).getBlue() + 
    img.getRGBPixel(r2,c2).getBlue()  ) / 4;
        default: 
            return 0;
    }
     
}

Image& RGBImage::operator += (int times){
    switch (times % 4){
        case -3:
        case 1:
            rotate_right(&pixels, width, height);
            break;
        case -2:
        case 2:
            rotate_right(&pixels, width, height);
            rotate_right(&pixels, width, height);
            break;
        case -1:
        case 3:
            rotate_left(&pixels, width, height);
            break;
    }
    return *this;
}

void rotate_right(RGBPixel ***old, int& width, int& height){
    RGBPixel **new_pixels = new RGBPixel*[width];
    for (int i=0; i<width; i++){
        new_pixels[i] = new RGBPixel[height];
    }

    for (int i=height-1; i>=0; i--){
        for (int j=0; j<width; j++){
            new_pixels[j][height-1-i] = (*old)[i][j];
        }
    }

    for (int i=0; i<height; i++)
        delete [] (*old)[i];
    delete [] *old;

    *old = new_pixels;
    std::swap(height, width);
}

void rotate_left(RGBPixel ***old, int& width, int& height){
    RGBPixel **new_pixels = new RGBPixel*[width];
    for (int i=0; i<width; i++){
        new_pixels[i] = new RGBPixel[height];
    }

    for (int i=0; i < height; i++){
        for (int j=0; j<width; j++){
            new_pixels[width-1 - j][i] = (*old)[i][j];
        }
    }

    for (int i=0; i<height; i++)
        delete [] (*old)[i];
    delete [] *old;

    *old = new_pixels;
    std::swap(height, width);
}

RGBPixel& RGBImage::getRGBPixel(int row, int col) const{
    return pixels[row][col];
}

void RGBImage::rgb_to_yuv(int **Y, int **U,int **V){
    
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            Y[i][j] = ( (  66 * pixels[i][j].getRed() + 129 * pixels[i][j].getGreen() +  25 * pixels[i][j].getBlue() + 128) >> 8) +  16;
            U[i][j] = ( ( -38 * pixels[i][j].getRed() -  74 * pixels[i][j].getGreen() + 112 * pixels[i][j].getBlue() + 128) >> 8) + 128;
            V[i][j] = ( ( 112 * pixels[i][j].getRed() -  94 * pixels[i][j].getGreen() -  18 * pixels[i][j].getBlue() + 128) >> 8) + 128;
        }
    }
}

void RGBImage::yuv_to_rgb(int **Y, int **U,int **V){
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            int C = Y[i][j] - 16, D = U[i][j] - 128, E = V[i][j] - 128;
            pixels[i][j].setRed(   clip(( 298 * C           + 409 * E + 128) >> 8) );
            pixels[i][j].setGreen( clip(( 298 * C - 100 * D - 208 * E + 128) >> 8) );
            pixels[i][j].setBlue(  clip(( 298 * C + 516 * D           + 128) >> 8) );
        }
    }
}

Image& RGBImage::operator ~(){
    
    int **Y = new int*[height], **U = new int*[height], **V = new int*[height];
    for (int i=0; i<height; i++){
        Y[i] = new int[width](); U[i] = new int[width](); V[i] = new int[width]();
    }
    rgb_to_yuv(Y,U,V);

    int histogram[Pixel::MAX_LUMINOCITY+1] = {}, new_luminocity[Pixel::MAX_LUMINOCITY+1] = {};
    double probability[Pixel::MAX_LUMINOCITY+1] = {};

    calc_histogram(histogram,Y,height,width);
    calc_distributed_probability(probability, histogram, height*width);
    calc_cumulative_probability(probability);
    calc_new_luminocity(new_luminocity, probability);
    calc_new_Y_values(Y, new_luminocity, height, width);

    yuv_to_rgb(Y,U,V);

    for (int i=0; i<height; i++){
        delete [] Y[i]; delete [] U[i]; delete [] V[i];
    }
    delete [] Y; delete [] U; delete [] V;

    return *this;
}
