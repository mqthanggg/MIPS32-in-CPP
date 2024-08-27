#include "../headers/compiler.h"

#define EXIT_FAILED() {input_file.close(); output_file.close(); return -1;}

int IMMEDIATE_CHECK(const string& IMMEDIATE_STR){

    long long IMMEDIATE = 0;

    try {
        
        if (IMMEDIATE_STR.substr(0,2) == "0x") IMMEDIATE = stoll(IMMEDIATE_STR, 0, 16);
        else IMMEDIATE = stoll(IMMEDIATE_STR);

    } catch (exception&) {

        SYS_PRINT("Invalid number for immediate value!\n");
        return -1;

    }

    if (IMMEDIATE > 0xFFFF || IMMEDIATE < 0){

        SYS_PRINT("Immediate value out of range!\n");
        return -1;

    }

    return 1;
}

void SYS_PRINT(const char* format, ...){
    va_list arg;

    va_start(arg, format);
    if (_COMPILER_OUTPUT_FILE_NAME != "DEFAULT_TERMINAL_OUTPUT"){

        char buffer [100];
        int nc = vsnprintf(buffer, 100, format, arg);
        if (nc >= 0 && nc < 100)

            output_file << string(buffer);

    }
    else        
        vfprintf(stdout, format, arg);

    va_end(arg);
}

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

            SYS_PRINT("Invalid number of arguments for instruction %s!\n", INSTRUCTION.c_str());
            return -1;

        }

        for (const string& ARG : ARGS) {
            if (find(REGISTERS_NAME.begin(), REGISTERS_NAME.end(), ARG) == REGISTERS_NAME.end()){

                SYS_PRINT("Invalid register name at %s!\n", ARG.c_str());
                return -1;

            }
        }

    }
    else if(find(_2_REGS_I_INSTRUCTIONS.begin(), _2_REGS_I_INSTRUCTIONS.end(), INSTRUCTION) != _2_REGS_I_INSTRUCTIONS.end()){
        if (ARGS.size() != 3){

            SYS_PRINT("Invalid number of arguments for instruction %s!\n", INSTRUCTION.c_str());
            return -1;

        }
        for (short i = 0; i < 2; i++) {
            if (find(REGISTERS_NAME.begin(), REGISTERS_NAME.end(), ARGS[i]) == REGISTERS_NAME.end()){

                SYS_PRINT("Invalid register name at %s!\n", ARGS[i].c_str());
                return -1;

            }
        }

        if (IMMEDIATE_CHECK(ARGS[2]) == -1) return -1;
    }
    //0 = DES_REG
    //1 = IMMEDIATE
    //2 = ARG_REG
    else if(find(LOAD_STORE_INSTRUCTIONS.begin(), LOAD_STORE_INSTRUCTIONS.end(), INSTRUCTION) != LOAD_STORE_INSTRUCTIONS.end()){

        if (find(REGISTERS_NAME.begin(), REGISTERS_NAME.end(), ARGS[0]) == REGISTERS_NAME.end()){

            SYS_PRINT("Invalid register name at %s!\n", ARGS[0].c_str());
            return -1;

        }

        char buff1[50];
        char buff2[50];

        if (sscanf(ARGS[1].c_str(), "%[^(](%[^)])", &buff1, &buff2) < 0) return -1;

        string IMMEDIATE_STR = buff1;
        string REG = buff2;

        if (IMMEDIATE_CHECK(IMMEDIATE_STR) == -1) return -1;

        ARGS[1] = stoi(IMMEDIATE_STR);
        ARGS[2] = REG;
        
    }

    else{

        SYS_PRINT("Invalid instruction at %s.\n",INSTRUCTION.c_str());
        return -1;

    }
    return 0;
}

int compile(const string &INPUT_FILE_NAME){
    string   fstr                       = "";
    int      line                       = 0;
             input_file.open(INPUT_FILE_NAME,ios::in);

    if (!input_file.is_open() || !input_file.good()) {

        SYS_PRINT("Bad or unknown file at input file: %s. Exiting...\n", INPUT_FILE_NAME.c_str());
        input_file.close();
        return -1;

    }

    //Output to file
    if (_COMPILER_OUTPUT_FILE_NAME != "DEFAULT_TERMINAL_OUTPUT"){

        output_file.open(_COMPILER_OUTPUT_FILE_NAME,ios::in);

        if (!output_file.is_open() || !output_file.good()) {

            SYS_PRINT("Bad or unknown file at output file: %s. Exiting...\n", _COMPILER_OUTPUT_FILE_NAME.c_str());
            EXIT_FAILED();

        }

        output_file.close();
        output_file.open(_COMPILER_OUTPUT_FILE_NAME, ios::trunc | ios::out);
    }
    SYS_PRINT("All the values are displayed in HEXadecimal!!\n");
    SYS_PRINT("Reading content of input file...\n");
    string         INSTRUCTION = "";
    string         ARGUMENTS   = "";

    REGS_INIT();
    MEM_INIT();
    while(getline(input_file,fstr)){
        SYS_PRINT("Line #%d: ", line);
        //Comment
        if (fstr[0] == '#') continue;
        
        vector<string> ARGS;
        //Split string, execute instruction
        string::iterator space_ptr = find(fstr.begin(), fstr.end(), ' ');
        if (space_ptr == fstr.end()) {

            SYS_PRINT("Undefined behaviour at this line: %s.\n", fstr.c_str());
            EXIT_FAILED();

        }

        INSTRUCTION = fstr.substr(0, space_ptr - fstr.begin());
        ARGUMENTS   = fstr.substr(space_ptr - fstr.begin() + 1);

        SYS_PRINT("Instruction: %s Args: %s\n", INSTRUCTION.c_str(), ARGUMENTS.c_str());

        if (PROCESS_ARGUMENTS(INSTRUCTION, ARGS, ARGUMENTS) == -1) EXIT_FAILED();
        for (const string& ARG : ARGS) {
            
            SYS_PRINT("Argument: %s\n",ARG.c_str());

        }

        if (INSTRUCTION == "add"){

            SYS_PRINT("Performing add instruction: %s = %s + %s here\n", ARGS[0].c_str(), ARGS[1].c_str(), ARGS[2].c_str());

            Register* DES_REG  = LOAD_REG(ARGS[0]);
            Register* ARG1_REG = LOAD_REG(ARGS[1]);
            Register* ARG2_REG = LOAD_REG(ARGS[2]);

            if (DES_REG  == nullptr ||
                ARG1_REG == nullptr ||
                ARG2_REG == nullptr)
                EXIT_FAILED();

            ADD(*DES_REG, *ARG1_REG, *ARG2_REG);

        }
        else if(INSTRUCTION == "sub"){
            
            SYS_PRINT("Performing sub instruction: %s = %s + %s here\n", ARGS[0].c_str(), ARGS[1].c_str(), ARGS[2].c_str());

            Register* DES_REG  = LOAD_REG(ARGS[0]);
            Register* ARG1_REG = LOAD_REG(ARGS[1]);
            Register* ARG2_REG = LOAD_REG(ARGS[2]);

            if (DES_REG  == nullptr ||
                ARG1_REG == nullptr ||
                ARG2_REG == nullptr)
                EXIT_FAILED();

            SUB(*DES_REG, *ARG1_REG, *ARG2_REG);

        }
        else if(INSTRUCTION == "ori"){

            SYS_PRINT("Performing ori instruction: %s = %s + %s here\n", ARGS[0].c_str(), ARGS[1].c_str(), ARGS[2].c_str());

            Register* DES_REG  = LOAD_REG(ARGS[0]);
            Register* ARG_REG  = LOAD_REG(ARGS[1]);

            if (DES_REG == nullptr ||
                ARG_REG == nullptr)
                EXIT_FAILED();

            ORI(*DES_REG, *ARG_REG, stoll(ARGS[2]));

        }
        else if(INSTRUCTION == "lw"){
            
            Register* DES_REG = LOAD_REG(ARGS[0]);
            Register* ARG_REG = LOAD_REG(ARGS[2]);

            unsigned int IMMEDIATE = stoll(ARGS[1]);
            SYS_PRINT("Performing lw instruction: *%s = %d[%d] here\n", ARGS[0].c_str(), ARGS[2].c_str(), IMMEDIATE);
            if (IMMEDIATE % 4 != 0) {
                SYS_PRINT("Invalid offset for lw!\n");
                EXIT_FAILED();
            }

            if (LW(*DES_REG, *ARG_REG, IMMEDIATE) == -1) {
                SYS_PRINT("Load word failed! Exiting...\n");
                EXIT_FAILED();
            }
        }
        else if(INSTRUCTION == "sw"){

            Register* DES_REG = LOAD_REG(ARGS[0]);
            Register* ARG_REG = LOAD_REG(ARGS[2]);
            
            unsigned int IMMEDIATE = stoll(ARGS[1]);
            SYS_PRINT("Performing sw instruction: %d[%d] = *%s here\n", ARGS[2].c_str(), IMMEDIATE, ARGS[0].c_str());
            if (IMMEDIATE % 4 != 0) {
                SYS_PRINT("Invalid offset for lw!\n");
                EXIT_FAILED();
            }

            if (SW(*DES_REG, *ARG_REG, IMMEDIATE)){
                SYS_PRINT("Store word failed! Exiting...\n");
                EXIT_FAILED();  
            }
        }
        else{
 
            SYS_PRINT("Else here\n");

        }
        line++;

    }
    input_file.close();
    MEM_UNMAP();

    if (_COMPILER_OUTPUT_FILE_NAME != "DEFAULT_TERMINAL_OUTPUT") output_file.close();

    return 0;
}