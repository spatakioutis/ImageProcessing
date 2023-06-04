#include "imageProcessing.hpp"

void grayscale_image(list<Token*>& db, string& token_name){

    Token *found = search_image(db, token_name);
    if (!found){
        cout << "[ERROR] Token " << token_name << " not found!\n";
        return;
    }

    if (!dynamic_cast<RGBImage*>(found->getPtr())){
        cout << "[NOP] Already grayscale " << token_name << endl;
        return;
    }

    GSCImage *gsc = new GSCImage(*dynamic_cast<RGBImage*>(found->getPtr()));

    delete found->getPtr();
    found->setPtr(gsc);
    cout << "[OK] Grayscale " << token_name << endl;
}

void color_invert_image(list<Token*>& db, string& token_name){
    
    Token *found = search_image(db, token_name);
    if (!found){
        cout << "[ERROR] Token " << token_name << " not found!\n";
        return;
    }
    Image *inverted = found->getPtr();
    if (dynamic_cast<GSCImage*>(found->getPtr())){
        *inverted = !(*dynamic_cast<GSCImage*>(found->getPtr()));
    }
    else {
        *inverted = !(*dynamic_cast<RGBImage*>(found->getPtr()));
    }
    found->setPtr(inverted);
    
    cout << "[OK] Color Inversion " << token_name << endl;
}

void mirror_image(list<Token*>& db, string& token_name){
    Token *found = search_image(db, token_name);
    if (!found){
        cout << "[ERROR] Token " << token_name << " not found!\n";
        return;
    }

    Image *mirrored = found->getPtr();
    if (dynamic_cast<GSCImage*>(found->getPtr())){
        *mirrored = *(*dynamic_cast<GSCImage*>(found->getPtr()));
    }
    else {
        *mirrored = *(*dynamic_cast<RGBImage*>(found->getPtr()));
    }
    found->setPtr(mirrored);
    
    cout << "[OK] Mirror " << token_name << endl;   
}

void rotate_image(list<Token*>& db, string& token_name, int& times){
    Token *found = search_image(db, token_name);
    if (!found){
        cout << "[ERROR] Token " << token_name << " not found!\n";
        return;
    }

    Image* rotated = found->getPtr();
    if (dynamic_cast<GSCImage*>(found->getPtr())){
        *rotated = (*dynamic_cast<GSCImage*>(found->getPtr())) += times;
    }
    else {
        *rotated = (*dynamic_cast<RGBImage*>(found->getPtr())) += times;
    }
    found->setPtr(rotated);
    cout << "[OK] Rotate " << token_name << endl; 
}

void scale_image(list<Token*>& db, string& token_name, double& factor){
    Token *found = search_image(db, token_name);
    if (!found){
        cout << "[ERROR] Token " << token_name << " not found!\n";
        return;
    }

    Image* scaled = found->getPtr();
    if (dynamic_cast<GSCImage*>(found->getPtr())){
        *scaled = (*dynamic_cast<GSCImage*>(found->getPtr())) *= factor;
    }
    else {
        *scaled = (*dynamic_cast<RGBImage*>(found->getPtr())) *= factor;
    }
    found->setPtr(scaled);
    cout << "[OK] Scale " << token_name << endl; 
}

void equalize_image(list<Token*>& db, string& token_name){
    Token *found = search_image(db, token_name);
    if (!found){
        cout << "[ERROR] Token " << token_name << " not found!\n";
        return;
    }

    Image* equalized = found->getPtr();
    if (dynamic_cast<GSCImage*>(found->getPtr())){
        *equalized = ~(*dynamic_cast<GSCImage*>(found->getPtr()));
    }
    else {
        *equalized = ~(*dynamic_cast<RGBImage*>(found->getPtr()));
    }
    found->setPtr(equalized);
    cout << "[OK] Equalize " << token_name << endl; 
}