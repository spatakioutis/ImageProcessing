#ifndef _IMAGE_
#define _IMAGE_

#include <ostream>
#include "../pixels/Pixel.hpp"

class Image {
    protected:
        int width;
        int height;
        int max_luminocity;
    public:
        virtual ~Image(){};
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        int getMaxLuminocity() const { return max_luminocity;  }
        void setWidth(int width) { this->width = width; }
        void setHeight(int height) { this->height = height; }
        void setMaxLuminocity(int lum) { this->max_luminocity = lum; }

        virtual Image& operator += (int times) = 0;
        virtual Image& operator *= (double factor) = 0;
        virtual Image& operator !() = 0;
        virtual Image& operator ~() = 0;
        virtual Image& operator *() = 0;  
        friend std::ostream& operator << (std::ostream& out, Image& image);
};
#endif
