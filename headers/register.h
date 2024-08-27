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

    bool                      RESERVED     ;
    bool                      SIGN     = 0 ;
    short                     BYTES    = 4 ;
    string                    REG_NAME = "";
    Register(bool RESERVED, const string& REG_NAME): 
        RESERVED(RESERVED),
        REG_NAME(REG_NAME)
    {}

    Register(const size_t& SPACE_SIZE){
        BYTES = SPACE_SIZE;
    }

    Register() :
        RESERVED(true),
        SIGN(0)
    {}
};

static Register ZERO_REG   = Register(false, "$zero");
static Register AT_REG     = Register(true, "$at");

static Register V_REGS[2]  = {
                         Register(false, "$v0"), 
                         Register(false, "$v1")
};
static Register A_REGS[4]  = {
                         Register(false, "$a0"),
                         Register(false, "$a1"),
                         Register(false, "$a2"),
                         Register(false, "$a3")
};
static Register T_REGS[10] = {
                         Register(false, "$t0"),
                         Register(false, "$t1"),
                         Register(false, "$t2"),
                         Register(false, "$t3"),
                         Register(false, "$t4"),
                         Register(false, "$t5"),
                         Register(false, "$t6"),
                         Register(false, "$t7"),
                         Register(false, "$t8"),
                         Register(false, "$t9"),
};
static Register S_REGS[8]  = {
                         Register(false, "$s0"),
                         Register(false, "$s1"),
                         Register(false, "$s2"),
                         Register(false, "$s3"),
                         Register(false, "$s4"),
                         Register(false, "$s5"),
                         Register(false, "$s6"),
                         Register(false, "$s7"),
};
static Register K_REGS[2]  = {
                         Register(true, "$k0"),
                         Register(true, "$k1"),
};
static Register GP_REG     = Register(false, "$gp");
static Register SP_REG     = Register(false, "$sp");
static Register FP_REG     = Register(false, "$fp");
static Register RA_REG     = Register(false, "$ra");
static Register HI         = Register(true, "hi");
static Register LO         = Register(true, "lo");

void WRITE_REG(const string& REG, ...);

Register* LOAD_REG(const string& REG);

static map<string, Register*> STR_REG;

static map<string, Register*> DATA_REG;

void ADD_DATA(const string& VARIABLE, const string& TYPE, const string& VALUE);

void REGS_INIT();