#pragma once
#define BYTE 8

struct Memory{

    unsigned int   CEIL_LIM;
    unsigned int   FLOOR_LIM;
    unsigned char* BITS;
    Memory(const unsigned int& CEIL_ADDR, const unsigned int& FLOOR_ADDR): 
        CEIL_LIM(CEIL_ADDR), 
        FLOOR_LIM(FLOOR_ADDR)
    {
        BITS = new unsigned char[(CEIL_ADDR - FLOOR_ADDR + 1) / BYTE];
    };

};

struct Kernel{

    Memory RESERVED[2]   = 
        {
                       Memory(0xfffffffe,0xffff0010),
                       Memory(0x03ffffff,0x00000000)
        };
    Memory MEM_MAPPED_IO = Memory(0xffff000f,0xffff0000);
    Memory DATA          = Memory(0xfffeffff,0x90000000);
    Memory TEXT          = Memory(0x8fffffff,0x80000000);

};

struct User{

    Memory              TEXT               = Memory(0x0fffffff,
                                                   0x04000000);
    Memory              HEAP               = Memory(0x7fffffff,
                                                   0x10000000);
    static unsigned int CURRENT_TEXT_ADDR;
    static unsigned int CURRENT_STACK_ADDR;
    
};