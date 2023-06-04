#ifndef _GSCPIXEL_
#define _GSCPIXEL_

#include "Pixel.hpp"

class GSCPixel : public Pixel {
    private: 
        unsigned char value;
    public:
        GSCPixel() = default;
        GSCPixel(const GSCPixel& p);
        GSCPixel(unsigned char value);
        unsigned char getValue() const;
        void setValue(unsigned char value);
        void swap(GSCPixel& p);
};

#endif
