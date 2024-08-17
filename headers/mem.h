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

namespace Kernel{

    static Memory RESERVED[2]   = 
        {
                       Memory(0xfffffffe,0xffff0010),
                       Memory(0x03ffffff,0x00000000)
        };
    static Memory MEM_MAPPED_IO = Memory(0xffff000f,0xffff0000);
    static Memory DATA          = Memory(0xfffeffff,0x90000000);
    static Memory TEXT          = Memory(0x8fffffff,0x80000000);

};

namespace User{

    static Memory              HEAP               = Memory(0x7fffffff,
                                                          0x10000380);
    static Memory              STATIC             = Memory(0x1000037f,
                                                          0x10000000);                                                   
    static Memory              TEXT               = Memory(0x0fffffff,
                                                          0x04000000);
    static unsigned int TRUE_MEM_OFFSET           = 0x04000000;                                                          
    static unsigned int CURRENT_TEXT_ADDR;
    static unsigned int CURRENT_STACK_ADDR;

    static map<string,unsigned int> REGS_MEM_ADDR;
    
};

static void* MEM_PTR;

int MEM_INIT();
int MEM_UNMAP();
void WRITE_MEM(const string& REG, const string& ADDR);
string* GET_MEM(const string& REG, const int& IMMEDIATE);
void MEM_ALLOC(const string& REG, const int& IMMEDIATE);