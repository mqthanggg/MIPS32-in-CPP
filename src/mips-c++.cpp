#include <cstring>
#include "../headers/compiler.h"

using namespace std;

string _COMPILER_OUTPUT_FILE_NAME;
//Read file with name + args
//mips-c++.exe -F [FILENAME] -O [FILENAME]
//mips-c++.exe -F [FILENAME]

int main(int argc, const char** argv) {

    if (argc < 2) {
        SYS_PRINT("mips-c++.exe -F [FILENAME|DIR] -O [FILENAME|DIR]\n");
        SYS_PRINT("mips-c++.exe -F [FILENAME]\n");
        SYS_PRINT("The FILENAME argument after the -F option stands for the input file's name, file's name must end with .asm-c++.\n");
        SYS_PRINT("THe FILENAME after the -O option is the output file's name, it can be whatever the user want.\n");
        SYS_PRINT("If -O option is not given, by default, output will be printed to the terminal.\n");
        return 0;
    }

    string input_file   = "";

    //-F

    if (!strcmp(argv[1], "-F\0")){

        input_file               = argv[2];
        SYS_PRINT("Reading at file: %s\n",argv[2]);
        string::iterator dot_ptr = find(input_file.begin(),input_file.end(),'.');

        if (dot_ptr != input_file.end()){

            string extension(dot_ptr,input_file.end());
            if (extension != ".mips-c++") {

                SYS_PRINT("Invalid extension! Exiting...\n");
                return -1;

            }

        }        
        
        else {

            SYS_PRINT("No extension is provided! Exiting...\n");
            return -1;

        }

        SYS_PRINT("Detected extension .mips-c++, OK.\n");

        //-O
        if (argc > 3){
            
            if (!strcmp(argv[3],"-O\0")){
                
                SYS_PRINT("Detected -O option with output file: %s, OK.\n", argv[4]);
                _COMPILER_OUTPUT_FILE_NAME = argv[4];

            }

            else {

                SYS_PRINT("Unknown %s option. Exiting...\n",argv[3]);
                return -1;

            }
        }

        else _COMPILER_OUTPUT_FILE_NAME = "DEFAULT_TERMINAL_OUTPUT";

    }

    else {

        SYS_PRINT("Unknown %s option. Exiting...\n",argv[1]);
        return -1;

    }
    
    return compile(input_file);
}