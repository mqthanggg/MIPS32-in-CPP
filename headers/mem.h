#pragma once
#define BYTE 8
#include "global.h"

struct Memory{

    unsigned int   CEIL_LIM;
    unsigned int   FLOOR_LIM;
    Memory(const unsigned int& CEIL_ADDR, const unsigned int& FLOOR_ADDR): 
        CEIL_LIM(CEIL_ADDR), 
        FLOOR_LIM(FLOOR_ADDR)
    {};

};

namespace User{

    static Memory              HEAP               = Memory(0x0f7fffff,
                                                          0x0180007c);
    static Memory              STATIC             = Memory(0x0180007b,
                                                          0x01800000);                                                   
    static Memory              TEXT               = Memory(0x017fffff,
                                                          0x00000000);

    static unsigned int CURRENT_STACK_ADDR;

    static map<string,unsigned int> REGS_MEM_ADDR;
    
};

static unsigned char ZERO_PTR[] = {0,0,0,0};

static void* MEM_PTR;

int MEM_INIT();
int MEM_UNMAP();
unsigned char* GET_REG_PTR(const string& REG);
int WRITE_MEM(const string& SOURCE_REG, const string& DES_REG, const int& BYTES, const int& OFFSET);
int WRITE_MEM(const unsigned int& SOURCE_ADDR, const string &DES_REG, const int &BYTES, const int &OFFSET);
int WRITE_MEM(const string& SOURCE_REG, const unsigned int& DES_ADDR, const int &BYTES, const int& OFFSET);
void READ_MEM(const string& REG, const int& BYTES);
int GET_MEM_CONTENT(const string& REG, const int& BYTES = 4);
int MEM_ALLOC(const string& REG, const int& SIZE);  