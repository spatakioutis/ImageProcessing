#include "database.hpp"

Token* search_image(list<Token*>& db, string& name){
    list<Token*>::iterator it;

    for (it = db.begin(); it != db.end(); ++it){
        if ((*it)->getName() == name){
            return *it;
        }
    }
    return nullptr;
}

void insert_image(list<Token*>& db, string& token_name, const char* filename){

    if (search_image(db, token_name) != nullptr){
        cout << "[ERROR] Token " << token_name << "exists\n";
        return;
    }
    Image *img = import_image(filename);
    if (!img) return;

    db.push_back(new Token(token_name, img));
    cout << "[OK] Import " << token_name << endl;
}

void delete_image(list<Token*>& db, string& token_name){
    list<Token*>::iterator it = db.begin();

    while (it != db.end()){
        if ((*it)->getName() == token_name)
            break;
        ++it;
    }
    if (it == db.end()){
        cout << "[ERROR] Token " << token_name << " not found!\n";
        return;
    }
    delete *it;
    db.erase(it);

    cout << "[OK] Delete " << token_name << endl;
}

void db_cleanup(list<Token*>& db){
    list<Token*>::iterator it = db.begin();

    while (it != db.end()){
        delete *it;
        it = db.erase(it);
    }
}

void print_list(list<Token*>& db){
    list<Token*>::iterator it = db.begin();

    cout << "--------LIST--------\n";

    while (it != db.end()){
        cout << "Token: " << (*it)->getName() << endl;
        ++it;
    }
    cout << "---------------------\n";
}