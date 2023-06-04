#ifndef _TOKEN_
#define _TOKEN_

#include "../images/Image.hpp"
#include "../images/RGBImage.hpp"
#include "../images/GSCImage.hpp"

using namespace std;

/* Class for the elements of the database, consisting of a unique token ID and a pointer to an image object
*/
class Token {
    private:
        string name;
        Image* ptr;
    public:
        Token(const string& name="", Image* ptr= nullptr);
        ~Token();
        string getName() const;
        Image* getPtr() const;
        void setName(const string& name);
        void setPtr(Image* ptr);
};

#endif
