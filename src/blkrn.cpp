/* BLK-RN
 * A lightweight bulk rename tool for Linux
 * Github: https://www.github.com/0x4248/blk-rn
 * Licence: GNU General Public License v3.0
 * By: 0x4248
 */

#include <filesystem>
#include <iostream>
#include <string.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define BANNER                                                                 \
    " ******   **       **   **       *******   ****     **\n"                 \
    "/*////** /**      /**  **       /**////** /**/**   /**\n"                 \
    "/*   /** /**      /** **        /**   /** /**//**  /**\n"                 \
    "/******  /**      /****         /*******  /** //** /**\n"                 \
    "/*//// **/**      /**/**        /**///**  /**  //**/**\n"                 \
    "/*    /**/**      /**//**       /**  //** /**   //****\n"                 \
    "/******* /********/** //** *****/**   //**/**    //***\n"                 \
    "///////  //////// //   // ///// //     // //      /// \n"

int verbose = false;

void log(std::string msg) {
    if (verbose) {
        std::cout << "[" << BLUE << "*" << WHITE << "] " << msg << std::endl;
    }
}
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    bool quiet = false;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-q") == 0) {
            quiet = true;
        }
        if (strcmp(argv[i], "-v") == 0) {
            verbose = true;
            log("Verbose mode enabled");
        }
    }
    if (!quiet) {
        std::cout << CYAN << BANNER << WHITE << std::endl;
        std::cout << "Enter the path of the files to rename> ";
    } else {
        std::cout << "path> ";
    }
    std::string path;
    std::cin >> path;
    log("Checking if the path is valid");
    if (!fs::exists(path)) {
        std::cout << "[" << RED << "X" << WHITE << "] "
                  << "The path is not valid" << std::endl;
        return 1;
    }
    log("The path is valid");
    fs::current_path(path);
    log("The current path is now: " + fs::current_path().string());
    std::string a;
    std::string b;
    if (!quiet) {
        std::cout
            << "Files will be named in order like this: 1.txt, 2.txt, 3.txt";
        std::cout << "You need to enter two things a and b where a is the text "
                     "before the number and b is the end of the file name and "
                     "the extension"
                  << std::endl;
        std::cout << "For example if you have a =  'text_' and b = '.txt' then "
                     "the files will be named like this: text_1.txt, "
                     "text_2.txt, text_3.txt"
                  << std::endl;
        std::cout << "Enter a> ";
        std::cin >> a;
        std::cout << "Enter b> ";
        std::cin >> b;
    } else {
        std::cout << "a> ";
        std::cin >> a;
        std::cout << "b> ";
        std::cin >> b;
    }
    int i = 1;
    for (const auto &entry : fs::directory_iterator(fs::current_path())) {
        log("Creating new file name");
        std::string new_file_name = a.c_str() + std::to_string(i) + b.c_str();
        log("Renaming file: " + entry.path().string());
        fs::rename(entry.path(), new_file_name);
        log("Renamed file: " + entry.path().string() + " to " + new_file_name);
        i = i + 1;
        if (!quiet) {
            std::cout << "[" << GREEN << "+" << WHITE << "] "
                      << "Renamed file " << entry.path() << " to "
                      << new_file_name << std::endl;
        }
    }

    log("Done renaming files, freeing memory and exiting");
    path.clear();
    a.clear();
    b.clear();
    return 0;
}