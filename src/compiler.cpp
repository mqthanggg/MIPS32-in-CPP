#include "../headers/compiler.h"
#include "../headers/instruction.h"
#include "../headers/register.h"
#include <sstream>
#include <algorithm>

#define EXIT_FAILED() {input_file.close(); output_file.close(); return -1;}

string stolower(const string& instr){
    string outstr = "";
    for (const char& chr : instr)
        outstr += tolower(chr);

    return outstr;
}


int PROCESS_ARGUMENTS(string& INSTRUCTION, vector<string>&ARGS, const string& ARGUMENTS){

    string           ARGUMENTS_copy   = ARGUMENTS;
                     INSTRUCTION      = stolower(INSTRUCTION);
    string           word             = "";
    string::iterator whitespace_ptr   = find(ARGUMENTS_copy.begin(), ARGUMENTS_copy.end(), ' ');
    while(whitespace_ptr != ARGUMENTS_copy.end())
    {

        ARGUMENTS_copy.erase(whitespace_ptr);
        whitespace_ptr = find(ARGUMENTS_copy.begin(), ARGUMENTS_copy.end(), ' ');

    }
    istringstream ss(ARGUMENTS_copy);
    

    while(getline(ss, word, ','))
        ARGS.push_back(word);

    if (find(_3_REGS_INSTRUCTIONS.begin(), _3_REGS_INSTRUCTIONS.end(), INSTRUCTION) != _3_REGS_INSTRUCTIONS.end()){

        if (ARGS.size() != 3) {

            printf("Invalid number of arguments for instruction %s!\n", INSTRUCTION.c_str());
            return -1;

        }

        for (const string& ARG : ARGS) {
            if (find(REGISTERS_NAME.begin(), REGISTERS_NAME.end(), ARG) == REGISTERS_NAME.end()){

                printf("Invalid register name at %s!\n", ARG.c_str());
                return -1;

            }
        }

    }
    else if(find(_2_REGS_I_INSTRUCTIONS.begin(), _2_REGS_I_INSTRUCTIONS.end(), INSTRUCTION) != _2_REGS_I_INSTRUCTIONS.end()){
        if (ARGS.size() != 3){

            printf("Invalid number of arguments for instruction %s!\n", INSTRUCTION.c_str());
            return -1;

        }
        for (short i = 0; i < 2; i++) {
            if (find(REGISTERS_NAME.begin(), REGISTERS_NAME.end(), ARGS[i]) == REGISTERS_NAME.end()){

                printf("Invalid register name at %s!\n", ARGS[i].c_str());
                return -1;

            }
        }

        long long IMMEDIATE = 0;

        try {

            IMMEDIATE = stoll(ARGS[2]);

        } catch (exception&) {

            perror("Invalid number for immediate value!\n");
            return -1;

        }

        if (IMMEDIATE > 0xFFFFFFFF || IMMEDIATE < 0){

            perror("Immediate value out of range!\n");
            return -1;

        }
    }

    //More
    else{

        printf("Invalid instruction at %s.\n",INSTRUCTION.c_str());
        return -1;

    }
    return 0;
}

int compile(const string &INPUT_FILE_NAME, const string &OUTPUT_FILE_NAME){

    ifstream input_file(INPUT_FILE_NAME,ios::in);
    ofstream output_file;
    string   fstr = "";
    int      line = 0;

    if (!input_file.is_open() || !input_file.good()) {

        printf("Bad or unknown file at input file: %s. Exiting...\n", INPUT_FILE_NAME.c_str());
        input_file.close();
        return -1;

    }

    //Output to terminal
    if (OUTPUT_FILE_NAME != "DEFAULT_TERMINAL_OUTPUT"){

        output_file.open(OUTPUT_FILE_NAME,ios::in);

        if (!output_file.is_open() || !output_file.good()) {

            printf("Bad or unknown file at output file: %s. Exiting...\n", OUTPUT_FILE_NAME.c_str());
            EXIT_FAILED();

        }

        output_file.close();
        output_file.open(OUTPUT_FILE_NAME, ios::trunc | ios::out);
    }

    printf("Reading content of input file...\n");
    string         INSTRUCTION = "";
    string         ARGUMENTS   = "";

    REGS_INIT();
    while(getline(input_file,fstr)){
        
        //Comment
        if (fstr[0] == '#') continue;
        
        vector<string> ARGS;
        //Split string, execute instruction
        string::iterator space_ptr = find(fstr.begin(), fstr.end(), ' ');
        if (space_ptr == fstr.end()) {

            printf("Undefined behaviour at this line: %s.\n", fstr.c_str());
            EXIT_FAILED();

        }

        INSTRUCTION = fstr.substr(0, space_ptr - fstr.begin());
        ARGUMENTS   = fstr.substr(space_ptr - fstr.begin() + 1);

        printf("Instruction: %s Args: %s\n", INSTRUCTION.c_str(), ARGUMENTS.c_str());

        if (PROCESS_ARGUMENTS(INSTRUCTION, ARGS, ARGUMENTS) == -1) EXIT_FAILED();
        for (const string& ARG : ARGS) {
            
            printf("Argument: %s\n",ARG.c_str());

        }

        if (INSTRUCTION == "add"){

            printf("Performing add instruction: %s = %s + %s here\n", ARGS[0].c_str(), ARGS[1].c_str(), ARGS[2].c_str());
            ADD(LOAD_REG(ARGS[0]), LOAD_REG(ARGS[1]), LOAD_REG(ARGS[2]));

        }
        else if(INSTRUCTION == "sub"){

            printf("Performing sub instruction: %s = %s + %s here\n", ARGS[0].c_str(), ARGS[1].c_str(), ARGS[2].c_str());
            SUB(LOAD_REG(ARGS[0]), LOAD_REG(ARGS[1]), LOAD_REG(ARGS[2]));

        }
        else if(INSTRUCTION == "ori"){

            printf("Performing ori instruction: %s = %s + %s here\n", ARGS[0].c_str(), ARGS[1].c_str(), ARGS[2].c_str());
            ORI(LOAD_REG(ARGS[0]), LOAD_REG(ARGS[1]), stoi(ARGS[2]));

        }
        else{
 
            printf("Else here\n");

        }
        line++;

    }
    input_file.close();
    if (OUTPUT_FILE_NAME != "DEFAULT_TERMINAL_OUTPUT") output_file.close();

    return 0;
}