#ifndef _RGBIMG_
#define _RGBIMG_

#include <cmath>

#include "Image.hpp"
#include "../pixels/RGBPixel.hpp"
#include "../processing/histogram.hpp"

class RGBImage : public Image {
    private:
        RGBPixel **pixels;
    public:
        RGBImage(); 
        RGBImage(const RGBImage& img);
        RGBImage(std::istream& stream);
        virtual ~RGBImage();

        RGBImage& operator = (const RGBImage& img);
        virtual Image& operator += (int times) override ;
        virtual Image& operator *= (double factor) override;
        virtual Image& operator !() override;
        virtual Image& operator ~() override;
        virtual Image& operator *() override;
        
        RGBPixel& getRGBPixel(int row, int col) const;
        friend std::ostream& operator << (std::ostream& out, Image& image);

        void rgb_to_yuv(int **Y, int **U,int **V);
        void yuv_to_rgb(int **Y, int **U,int **V);
};

void rotate_right(RGBPixel ***old, int& width, int& height);
void rotate_left(RGBPixel ***old, int& width, int& height);
int new_value(RGBImage& img, int row, int col, double factor, int type);

#endif
