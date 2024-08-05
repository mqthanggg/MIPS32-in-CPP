#include <cstring>
#include "../headers/compiler.h"

using namespace std;

//Read file with name + args
//mips-c++.exe -F [FILENAME] -O [FILENAME]
//mips-c++.exe -F [FILENAME]

int main(int argc, const char** argv) {

    if (argc < 2) {
        printf("mips-c++.exe -F [FILENAME|DIR] -O [FILENAME|DIR]\n");
        printf("mips-c++.exe -F [FILENAME]\n");
        printf("The FILENAME argument after the -F option stands for the input file's name, file's name must end with .asm-c++.\n");
        printf("THe FILENAME after the -O option is the output file's name, it can be whatever the user want.\n");
        printf("If -O option is not given, by default, output will be printed to the terminal.\n");
        return 0;
    }

    string input_file      = "",
           output_file     = "";

    //-F

    if (!strcmp(argv[1], "-F\0")){

        input_file               = argv[2];
        printf("Reading at file: %s\n",argv[2]);
        string::iterator dot_ptr = find(input_file.begin(),input_file.end(),'.');

        if (dot_ptr != input_file.end()){

            string extension(dot_ptr,input_file.end());
            if (extension != ".mips-c++") {

                printf("Invalid extension! Exiting...\n");
                return -1;

            }

        }        
        
        else {

            printf("No extension is provided! Exiting...\n");
            return -1;

        }

        printf("Detected extension .mips-c++, OK.\n");

        //-O
        if (argc > 3){
            
            if (!strcmp(argv[3],"-O\0")){
                
                printf("Detected -O option with output file: %s, OK.\n", argv[4]);
                output_file = argv[4];

            }

            else {

                printf("Unknown %s option. Exiting...\n",argv[3]);
                return -1;

            }
        }

        else output_file = "DEFAULT_TERMINAL_OUTPUT";

    }

    else {

        printf("Unknown %s option. Exiting...\n",argv[1]);
        return -1;

    }
    
    return compile(input_file, output_file);
}