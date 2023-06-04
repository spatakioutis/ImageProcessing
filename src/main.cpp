#include <regex>
#include <vector>

#include "processing/imageProcessing.hpp"
#include "database/database.hpp"
#include "fileio/fileio.hpp"

bool format_is_valid(string& command, int format_type){

    regex pattern;

    switch (format_type){
    case 1:
        pattern = regex(R"(i\s+([^\\]+)\s+as\s+(\$\w+))");
        break;
    case 2:
        pattern = regex(R"(e\s+(\$\w+)\s+as\s+([^\\]+))");
        break;
    case 3:
        pattern = regex(R"(d\s+(\$\w+))");
        break;
    case 4:
        pattern = regex(R"(n\s+(\$\w+))");
        break;
    case 5:
        pattern = regex(R"(z\s+(\$\w+))");
        break;
    case 6:
        pattern = regex(R"(m\s+(\$\w+))");
        break;
    case 7:
        pattern = regex(R"(g\s+(\$\w+))");
        break;
    case 8:
        pattern = regex(R"(s\s+(\$\w+)\s+by\s+-?\d+(\.\d+)?)");
        break;
    case 9:
        pattern = regex(R"(r\s+(\$\w+)\s+clockwise\s+-?\d+ times)");
        break;
    case 10:
        pattern = regex(R"(h)");
        break;
    case 11: 
        pattern = regex(R"(l)");
        break;
    case 12: 
        pattern = regex(R"(q)");
        break;
    }
    if (!regex_match(command, pattern)){
        cout << "\n-- Invalid command! -\n";
        return false;
    }
    return true;
}

void command_parser(string& command, string *token_name, string *filename, double *factor, int *rotations, int command_type){

    vector<string> tokens;
    string parsed_token;
    istringstream iss(command);

    while (iss >> parsed_token){
        tokens.push_back(parsed_token);
    }

    switch (command_type){
        case 1:
            filename->append(tokens[1]);
            token_name->append(tokens[3]);
            break;
        case 2:
            filename->append(tokens[3]);
            token_name->append(tokens[1]);
            break;
        case 8:
            token_name->append(tokens[1]);
            *factor = stod(tokens[3]);
            break;
        case 9:
            token_name->append(tokens[1]);
            *rotations = stoi(tokens[3]);
            break;
        default:
            token_name->append(tokens[1]);
            break;
    }
}

void print_menu(){
    cout << "-------------------------OPTIONS-----------------------------\n";
    cout << "print imported images: l\n";
    cout << "import image to db   : i <filepath> as $<token>\n";
    cout << "export image from db : e $<token> as <filepath>\n";
    cout << "rotate image         : r $<token> clockwise <num> times\n";
    cout << "delete image         : d $<token>\n";
    cout << "mirror image         : m $<token>\n";
    cout << "invert colors        : n $<token>\n";
    cout << "scale image          : s $<token> by <factor>\n";
    cout << "grayscale image      : g $<token>\n";
    cout << "equalize histogram   : z $<token>\n";
    cout << "-------------------------------------\n";
    cout << "the \"<expression>\" indicates that you have to type the thing stated by the exression\n";
    cout << "-------------------------------------------------------------\n";
}

int main(){
    list<Token*> image_db;
    string command, filename, token_name;
    int rotations;
    double factor;

    cout << "-----------Image Processor - Formats supported: PPM, PGM-----------\n" << 
            "-----------------Type 'h' to see available options-----------------\n";

    while (true){
        filename = ""; token_name = ""; command = ""; rotations=0; factor=0;
        getline(cin,command);
        switch (command[0]){
        case 'i':
            if (format_is_valid(command, 1)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 1);
                insert_image(image_db, token_name, filename.c_str());
            }
            break;
        case 'e':
            if (format_is_valid(command, 2)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 2);
                export_image(image_db, token_name, filename.c_str());
            }
            break;
        case 'd':
            if (format_is_valid(command, 3)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 3);
                delete_image(image_db, token_name);
            }
            break;
        case 'n':
            if (format_is_valid(command, 4)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 4);
                color_invert_image(image_db, token_name);
            }
            break;
        case 'z':
            if (format_is_valid(command, 5)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 5);
                equalize_image(image_db, token_name);
            }
            break;
        case 'm':
            if (format_is_valid(command, 6)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 6);
                mirror_image(image_db,token_name);
            }
            break;
        case 'g':
            if (format_is_valid(command, 7)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 7);
                grayscale_image(image_db, token_name);
            }
            break;
        case 's':
            if (format_is_valid(command, 8)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 8);
                scale_image(image_db, token_name, factor);
            }
            break;
        case 'r':
            if (format_is_valid(command, 9)){
                command_parser(command, &token_name, &filename, &factor, &rotations, 9);
                rotate_image(image_db, token_name, rotations);
            }
            break;
        case 'h':
            if (format_is_valid(command,10)){
                print_menu();
            }
            break;
        case 'l':
            if (format_is_valid(command,11)){
                print_list(image_db);
            }
            break;
        case 'q':
            if (format_is_valid(command,12)){
                db_cleanup(image_db);
                return 0;
            }
        default:
            cout << "\n-- Invalid command! -\n";
        }
    }
}