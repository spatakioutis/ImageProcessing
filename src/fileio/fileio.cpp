#include "fileio.hpp"

Image* import_image(const char* filename) {
    ifstream f(filename);
    if(!f.is_open()) {
        std::cout << "[ERROR] Unable to open " << filename << std::endl;
        return nullptr;
    }
    Image* img_ptr = nullptr;
    string type;

    if(f.good() && !f.eof())
        f >> type;
    if(!type.compare("P3")) {
        img_ptr = new RGBImage(f);
    }
    else if(!type.compare("P2")) {
        img_ptr = new GSCImage(f);
    }  
    else if(f.is_open()) {
        std::cout << "[ERROR] Invalid file format" << std::endl;
    }

    return img_ptr;
}

void export_image(list<Token*>& db, string& token_name, const char* filename){

    Token* found = search_image(db, token_name);
    if (!found){
        cout << "[ERROR] Token " << token_name << " not found!\n";
        return;
    }

    ifstream filecheck(filename);
    if(filecheck.good()) {
        std::cout << "[ERROR] File exists\n";
        return;
    }
    
    ofstream f(filename);
    if (!f.is_open()){
        cout << "[ERROR] Unable to create file\n";
        return;
    }

    f << *(found->getPtr());

    cout << "[OK] Export " << token_name << endl;
}

//write image info to file in the appropriate format (differs if it is an rgb or grayscale image)
std::ostream& operator << (std::ostream& out, Image& image){
    int i,j;

    if (dynamic_cast<GSCImage*>(&image)){
        GSCImage *img = dynamic_cast<GSCImage*>(&image);
        out << "P2\n";
        out << img->width << " " << img->height << " " << img->max_luminocity << endl;
        for (i=0; i<img->height; i++){
            for (j=0; j<img->width; j++){
                out << (int)img->pixels[i][j].getValue() << endl;
            }
        }
    }
    else {
        RGBImage *img = dynamic_cast<RGBImage*>(&image);
        out << "P3\n";
        out << img->width << " " << img->height << " " << img->max_luminocity << endl;
        for (i=0; i<img->height; i++){
            for (j=0; j<img->width; j++){
                RGBPixel pixel = img->pixels[i][j];
                out << (int)pixel.getRed() << " " << (int)pixel.getGreen() << " " << (int)pixel.getBlue() << endl;
            }
        }
    }
    return out;
}