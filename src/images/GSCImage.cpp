#include "GSCImage.hpp"

GSCImage::GSCImage(){
    this->width = 0;
    this->height = 0;
    this->max_luminocity = Pixel::MAX_LUMINOCITY;
    pixels = NULL;
}

GSCImage::GSCImage(const GSCImage& img){
    this->width = img.getWidth();
    this->height = img.getHeight();
    this->max_luminocity = img.getMaxLuminocity();

    //copy pixels
    pixels = new GSCPixel*[getHeight()];
    for (int i=0; i<getHeight(); i++){
        pixels[i] = new GSCPixel[getWidth()];
        for (int j=0; j<getWidth(); j++){
            pixels[i][j].setValue(img.pixels[i][j].getValue());
        }
    }
}

GSCImage::GSCImage(const RGBImage& grayscaled){
    this->width = grayscaled.getWidth();
    this->height = grayscaled.getHeight();
    this->max_luminocity = grayscaled.getMaxLuminocity();

    //copy pixels
    pixels = new GSCPixel*[getHeight()];
    for (int i=0; i<getHeight(); i++){
        pixels[i] = new GSCPixel[getWidth()];
        for (int j=0; j<getWidth(); j++){
            int gray = (int)grayscaled.getRGBPixel(i,j).getRed()*0.3 +
            (int)grayscaled.getRGBPixel(i,j).getGreen()*0.59 +
            (int)grayscaled.getRGBPixel(i,j).getBlue()*0.11;
            pixels[i][j].setValue(gray);
        }
    }
}

GSCImage::GSCImage(std::istream& stream){
    int value;

    stream >> width; 
    stream >> height;
    stream >> max_luminocity;

    pixels = new GSCPixel*[getHeight()];
    for (int i=0; i<getHeight(); i++){
        pixels[i] = new GSCPixel[getWidth()];
        for (int j=0; j<getWidth(); j++){
            stream >> value;
            pixels[i][j].setValue((unsigned char)value);
        }
    }
}

GSCImage::~GSCImage(){
    if ( pixels != NULL){
        for (int i=0; i<getHeight(); i++){
            delete[] pixels[i];
        }
    }
    delete[] pixels;
}


GSCImage& GSCImage::operator = (const GSCImage& img){
    setWidth(img.getWidth());
    setHeight(img.getHeight());
    setMaxLuminocity(img.getMaxLuminocity());

    //copy pixels
    pixels = new GSCPixel*[getHeight()];
    for (int i=0; i<getHeight(); i++){
        pixels[i] = new GSCPixel[getWidth()];
        for (int j=0; j<getWidth(); j++){
            this->pixels[i][j] = img.pixels[i][j];
        }
    }
    return *this;
}

Image& GSCImage::operator !(){
    for (int i=0; i<getHeight(); i++){
        for (int j=0; j<getWidth(); j++){
            pixels[i][j].setValue(getMaxLuminocity() - pixels[i][j].getValue());
        }
    }
    return *this;
}

Image& GSCImage::operator *(){
    for (int i=0; i<getHeight(); i++){
        for (int j=0, k=getWidth()-1; j<k; j++, k--){
            pixels[i][j].swap(pixels[i][k]);
        }
    }
    return *this;
}

Image& GSCImage::operator *= (double factor){
    GSCPixel **new_pixels = new GSCPixel*[(int)(height*factor)];
    for (int i=0; i<(int)(height*factor); i++){
        new_pixels[i] = new GSCPixel[(int)(width*factor)];
        for (int j=0; j<(int)(width*factor); j++){
            new_pixels[i][j].setValue(new_value(*this,i,j,factor));
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

int new_value(GSCImage& img, int row, int col, double factor){
    int r1 = std::min((int)floor(row/factor), img.getHeight()-1);
    int r2 = std::min((int)ceil(row/factor), img.getHeight()-1);
    int c1 = std::min((int)floor(col/factor), img.getWidth()-1);
    int c2 = std::min((int)ceil(col/factor), img.getWidth()-1);

    return (  
    img.getGSCPixel(r1,c1).getValue() + 
    img.getGSCPixel(r1,c2).getValue() + 
    img.getGSCPixel(r2,c1).getValue() + 
    img.getGSCPixel(r2,c2).getValue()  ) / 4; 
}

Image& GSCImage::operator += (int times){

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

GSCPixel& GSCImage::getGSCPixel(int row, int col){
    return pixels[row][col];
}

void rotate_right(GSCPixel ***old, int& width, int& height){
    GSCPixel **new_pixels = new GSCPixel*[width];
    for (int i=0; i<width; i++){
        new_pixels[i] = new GSCPixel[height];
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

void rotate_left(GSCPixel ***old, int& width, int& height){
    GSCPixel **new_pixels = new GSCPixel*[width];
    for (int i=0; i<width; i++){
        new_pixels[i] = new GSCPixel[height];
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

void GSCImage::gsc_to_yuv(int **Y){
    
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            Y[i][j] = ( (  66 * pixels[i][j].getValue() + 129 * pixels[i][j].getValue() +  25 * pixels[i][j].getValue() + 128) >> 8) +  16;
        }
    }
}

void GSCImage::yuv_to_gsc(int **Y){
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            int C = Y[i][j] - 16;
            pixels[i][j].setValue(clip((298*C+128)>>8));
        }
    }
}

Image& GSCImage::operator ~(){
    
    int **Y = new int*[height];
    for (int i=0; i<height; i++){
        Y[i] = new int[width]();
    }
    gsc_to_yuv(Y);

    int histogram[Pixel::MAX_LUMINOCITY+1] = {}, new_luminocity[Pixel::MAX_LUMINOCITY+1] = {};
    double probability[Pixel::MAX_LUMINOCITY+1] = {};

    calc_histogram(histogram,Y,height,width);
    calc_distributed_probability(probability, histogram, height*width);
    calc_cumulative_probability(probability);
    calc_new_luminocity(new_luminocity, probability);
    calc_new_Y_values(Y, new_luminocity, height, width);

    yuv_to_gsc(Y);

    for (int i=0; i<height; i++){
        delete [] Y[i];
    }
    delete [] Y;

    return *this;
}