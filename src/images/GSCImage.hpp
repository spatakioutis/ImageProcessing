#ifndef _GSCIMAGE_
#define _GSCIMAGE_

#include <cmath>

#include "Image.hpp"
#include "../pixels/Pixel.hpp"
#include "RGBImage.hpp"
#include "../processing/histogram.hpp"

class GSCImage : public Image {
    private:
        GSCPixel **pixels;
    public:
        GSCImage();
        GSCImage(const GSCImage& img);
        GSCImage(const RGBImage& grayscaled);
        GSCImage(std::istream& stream);
        virtual ~GSCImage();
        GSCImage& operator = (const GSCImage& img); 
        
        virtual Image& operator += (int times) override ;
        virtual Image& operator *= (double factor) override;
        virtual Image& operator !() override;
        virtual Image& operator ~  () override;
        virtual Image& operator *() override;

        GSCPixel& getGSCPixel(int row, int col);
        
        friend std::ostream& operator << (std::ostream& out, Image& image);

        void gsc_to_yuv(int **Y);
        void yuv_to_gsc(int **Y);
};

void rotate_right(GSCPixel ***old, int& width, int& height);
void rotate_left(GSCPixel ***old, int& width, int& height);
int new_value(GSCImage& img, int row, int col, double factor);

#endif
