#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>

#include "../images/Image.hpp"
#include "../images/GSCImage.hpp"
#include "../images/RGBImage.hpp"
#include "../database/Token.hpp"
#include "../database/database.hpp"

/*--Attempts to import an image from filesystem.
  --Possible errors: 1) image file doesn't exists / can't be opened
                     2) file format is not supported
  --Prints corresponding messages both for success and failure
*/
Image* import_image(const char* filename);

/*--Attempts to export an image to the filesystem.
  --Possible errors: 1) image filename already exists
                     2) image file can't be created
                     3) token ID doesn't exist
  --Prints corresponding messages both for success and failure
*/
void export_image(list<Token*>& db, string& token_name, const char* filename);

/*--Overload of the operator '<<'
  --Attempts to print an image to a given output stream.
  --Supports both RGB and GSC images
*/
std::ostream& operator << (std::ostream& out, Image& image);

#endif