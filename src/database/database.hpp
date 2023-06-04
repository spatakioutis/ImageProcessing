#ifndef DATABASE_H
#define DATABASE_H

#include <list>

#include "Token.hpp"
#include "../fileio/fileio.hpp"

/*prints the contents of the database of images
*/
void print_list(list<Token*>& db);

/*Searches for an image through the unique $token ID that the image has in the database
  Returns a pointer to the database entry if the search was successful, otherwise returns nullptr*/
Token* search_image(list<Token*>& db, string& token_name);

/*--Attempts to import an image from file system and insert it into the database.
  --Possible errors: 1) image file can't be found/opened.
                     2) file format is not manageable
                     3) $token ID already exists
  --Prints corresponding messages both for success and failure
*/
void insert_image(list<Token*>& db, string& token_name, const char* filename);

/*--Attempts to delete an image from the database.
  --Possible errors: 1) $token ID doesn't exists
  --Prints corresponding messages both for success and failure
*/
void delete_image(list<Token*>& db, string& token_name);

/*--Deletes all database entries and deletes all dynamically allocated memory associated with the database
*/
void db_cleanup(list<Token*>& db);

#endif