#pragma once
#define BYTE 8
#include "global.h"

static vector<string> REGISTERS_NAME = {
    "$zero",
    "$v0",
    "$v1",
    "$a0",
    "$a1",
    "$a2",
    "$a3",
    "$t0",
    "$t1",
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    "$t8",
    "$t9",
    "$s0",
    "$s1",
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    "$gp",
    "$sp",
    "$fp",
    "$ra"
};

struct Register{

    bool                      RESERVED;
    bool                      SIGN = 0;
    vector<string>  ADDR; //By default each register has 4 bytes = 32 bits
    short                     BYTES = 4;
    Register(bool RESERVED, const string& byte1,const string& byte2,const string& byte3,const string& byte4): 
        RESERVED(RESERVED)
    {
        
        ADDR.resize(4);
        ADDR[0] = byte1;
        ADDR[1] = byte2;
        ADDR[2] = byte3;
        ADDR[3] = byte4;

    }
    Register(const size_t& SPACE_SIZE){
        BYTES = SPACE_SIZE;
        ADDR.resize(BYTES);
    }
    Register() :
        RESERVED(true),
        SIGN(0)
    {
        ADDR.resize(BYTES);
        ADDR[3] = ADDR[2] = ADDR[1] = ADDR[0] = "00000000";
    }
    bool operator==(Register& REG){

        if (
            !(
                this->RESERVED == REG.RESERVED &&
                this->SIGN     == REG.SIGN &&
                this->BYTES    == REG.BYTES)
            )
            return false;

        for (short byte = 0; byte < this->BYTES; byte++) 
            if (this->ADDR[byte] != REG.ADDR[byte]) return false;

        return true;

    }
};

static Register ERROR_REG  = Register(true, "11111111", "11111111", "11111111", "11111111");
static Register ZERO_REG   = Register(false, "00000000", "00000000", "00000000", "00000000");
static Register AT_REG     = Register(true, "00000000", "00000000", "00000000", "00000000");

static Register V_REGS[2]  = {
                         Register(false, "00000000", "00000000", "00000000", "00000000"), 
                         Register(false, "00000000", "00000000", "00000000", "00000000")
};
static Register A_REGS[4]  = {
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000")
};
static Register T_REGS[10] = {
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
};
static Register S_REGS[8]  = {
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
                         Register(false, "00000000", "00000000", "00000000", "00000000"),
};
static Register K_REGS[2]  = {
                         Register(true, "00000000", "00000000", "00000000", "00000000"),
                         Register(true, "00000000", "00000000", "00000000", "00000000"),
};
static Register GP_REG     = Register(false, "00000000", "00000000", "00000000", "00000000");
static Register SP_REG     = Register(false, "00000000", "00000000", "00000000", "00000000");
static Register FP_REG     = Register(false, "00000000", "00000000", "00000000", "00000000");
static Register RA_REG     = Register(false, "00000000", "00000000", "00000000", "00000000");
static Register HI         = Register(true, "00000000", "00000000", "00000000", "00000000");
static Register LO         = Register(true, "00000000", "00000000", "00000000", "00000000");

void WRITE_REG(const string& REG, ...);

Register* LOAD_REG(const string& REG);

static map<string, Register*> STR_REG;

static map<string, Register*> DATA_REG;

void ADD_DATA(const string& VARIABLE, const string& TYPE, const string& VALUE);

void REGS_INIT();