//Question 4 - Filesystem & args

// Task: Implement the code as described in the main body,
// make sure to handle cases when the requested file is not found or the "files" directory doesn't exists and you have to create it
// Prefer modern solutions over classic C style solutions and keep in mind that this code should be able to run in other windows,
// linux and other platforms (hint: '/' and '\' in file paths)

#include <fstream>
#include <string>
#include <iostream>
#if defined _WIN32
    #include <direct.h>
#else
	#include <sys/stat.h>
#endif
using namespace std;

int main(int argc, char** argv) {

    std::fstream file;
    std::string command_type, file_name, write_in_file, output_to_console, path;
    if (argc > 2 && argc < 5) { // valid input need to be bigger than 2 arguments and smaller than 5.
        command_type = argv[1]; // create or read
        file_name = argv[2]; // example: test1
        path = "files/" + file_name;

        if (command_type == "create" && argc == 4) { // that's mean that we can be sure we need to do the create command.
            write_in_file = argv[3]; // what I want to write in the txt file
            file.open(path + ".txt", std::ios::out); // write mode

            if (file.is_open()) {
                file << "Hello from" << " " << write_in_file << std::endl;
                file.close();
            } else {
                std::cout << "Error in open file" << std::endl; // need to open new dir called "files"
                std::cout << "open dir named files" << std::endl;
#if defined _WIN32
                _mkdir("files"); // for windows
#else
                mkdir("files", 0777); // for linux
#endif
                file.open(path + ".txt", std::ios::out); // write mode
                if (file.is_open()) {
                    file << "Hello from" << " " << write_in_file << std::endl; // write probably in the txt file
                    file.close();
                } else {
                    std::cout << "Error in open dir files" << std::endl;
                }
            }
        } else if (command_type == "read" && argc == 3) { // example: read test1
            file.open(path + ".txt", std::ios::in); // read mode

            if (file.is_open()) {
                while (std::getline(file, output_to_console)) { // read line by line
                    std::cout << output_to_console << std::endl;
                }
                file.close();
            } else {
                std::cout << "Error in open file (read)" << std::endl;
            }
        }
        else {
            std::cout << "invalid input- number of arguments need to be 2 for read and 3 for create" << std::endl;
            exit(1);
        }
    }
    else {
        std::cout << "invalid input- number of arguments need to be 2 for read and 3 for create" << std::endl;
        exit(1);
    }

    std::cout << "Press enter to exit" << std::endl;
    getchar();
    return 0;
}

//If user passed "create" argument
//		Create (or overwrite) a file named *argument2.txt*  with the text "Hello from *argument3*" in a folder named "files" under the current working directory
//else if user passed "read" argument
//		read a file named* argument2* from a folder named "files" under the current working directory and print it to the console

//Execution example (assuming working directory c:\code): question04.exe create test1 Nir - should create the file c:\code\files\test1.txt with the content "Hello from Nir"
//Execution example (assuming working directory c:\code): question04.exe read test1  - should print "Hello from Nir" in the console (assuming the previous command was executed)
