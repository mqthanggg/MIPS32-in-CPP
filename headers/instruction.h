#pragma once
#include "register.h"
#include "mem.h"

//$1, $2, $3
static vector<string> _3_REGS_INSTRUCTIONS{
    "add",
    "addu",
    "and",
    "nor",
    "or",
    "sllv",
    "srav",
    "srlv",
    "sub",
    "subu",
    "xor",
    "slt",
    "sltu",
};

//$1, $2
static vector<string> _2_REGS_INSTRUCTIONS{
    "div",
    "divu",
    "mult",
    "multu",
};

//$1, $2, i
static vector<string> _2_REGS_I_INSTRUCTIONS{
    "addi",
    "addiu",
    "andi",
    "ori",
    "xori",
    "slti",
    "sltiu"
};

//$1, $2, a
static vector<string> _2_REGS_A_INSTRUCTIONS{
    "sll",
    "sra",
    "srl",
};

//$1, i($2)
static vector<string> LOAD_STORE_INSTRUCTIONS{
    "lb",
    "lbu",
    "lh",
    "lhu",
    "lw",
    "sb",
    "sh",
    "sw"
};

//$1
static vector<string> MOVE_INSTRUCTIONS{
    "mfhi",
    "mflo",
    "mthi",
    "mtlo"
};

//ADD, SUB
void ADD(Register& DES_REG, const Register& ARG1, const Register& ARG2);
void SUB(Register& DES_REG, const Register& ARG1, const Register& ARG2);
void ORI(Register& DES_REG, const Register& ARG, const int& IMMEDIATE);
int LW(Register& DES_REG, const Register& ARG, const int& IMMEDIATE);
int SW(Register& DES_REG, const Register& ARG, const int& IMMEDIATE);