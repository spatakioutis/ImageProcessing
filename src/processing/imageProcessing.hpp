#ifndef IMG_PROCESSING_H
#define IMG_PROCESSING_H

#include <iostream>
#include <list>

#include "../images/Image.hpp" 
#include "../images/GSCImage.hpp"
#include "../images/RGBImage.hpp"
#include "../database/Token.hpp"
#include "../database/database.hpp"

using namespace std;

//image manipulation functions
void color_invert_image(list<Token*>& db, string& token_name);
void grayscale_image(list<Token*>& db, string& token_name);
void mirror_image(list<Token*>& db, string& token_name);
void rotate_image(list<Token*>& db, string& token_name, int& times);
void scale_image(list<Token*>& db, string& token_name, double& factor);
void equalize_image(list<Token*>& db, string& token_name);


#endif