#include "../headers/register.h"

void REGS_INIT(){
    STR_REG["$zero"] = &ZERO_REG;
    STR_REG["$at"] = &AT_REG;
    STR_REG["$v0"] = &V_REGS[0];
    STR_REG["$v1"] = &V_REGS[1];
    STR_REG["$a0"] = &A_REGS[0];
    STR_REG["$a1"] = &A_REGS[1];
    STR_REG["$a2"] = &A_REGS[2];
    STR_REG["$a3"] = &A_REGS[3];
    STR_REG["$t0"] = &T_REGS[0];
    STR_REG["$t1"] = &T_REGS[1];
    STR_REG["$t2"] = &T_REGS[2];
    STR_REG["$t3"] = &T_REGS[3];
    STR_REG["$t4"] = &T_REGS[4];
    STR_REG["$t5"] = &T_REGS[5];
    STR_REG["$t6"] = &T_REGS[6];
    STR_REG["$t7"] = &T_REGS[7];
    STR_REG["$s0"] = &S_REGS[0];
    STR_REG["$s1"] = &S_REGS[1];
    STR_REG["$s2"] = &S_REGS[2];
    STR_REG["$s3"] = &S_REGS[3];
    STR_REG["$s4"] = &S_REGS[4];
    STR_REG["$s5"] = &S_REGS[5];
    STR_REG["$s6"] = &S_REGS[6];
    STR_REG["$s7"] = &S_REGS[7];
    STR_REG["$t8"] = &T_REGS[8];
    STR_REG["$t9"] = &T_REGS[9];
    STR_REG["$k0"] = &K_REGS[0];
    STR_REG["$k1"] = &K_REGS[1];
    STR_REG["$gp"] = &GP_REG;
    STR_REG["$sp"] = &SP_REG;
    STR_REG["$fp"] = &FP_REG;
    STR_REG["$ra"] = &RA_REG;
}

//Make sure to adjust this api call for arrays
void WRITE_REG(const string& REG,...){

    va_list valist;
    va_start(valist, 4);
    for (size_t i = 0; i < 4; i++)
        STR_REG[REG]->ADDR[i] = va_arg(valist, unsigned int);
    va_end(valist);

}

Register* LOAD_REG(const string& REG){

    if (STR_REG.find(REG) == STR_REG.end()) {
        SYS_PRINT("Cannot find this register!\n");
        return &ERROR_REG;
    }
    return STR_REG[REG];

}

void ADD_DATA(const string &VARIABLE, const string &TYPE, const string &VALUE){
    if (TYPE == ".word"){
        
    }
    else if (TYPE == ".half"){

    }
    else if (TYPE == ".byte"){

    }
    else if (TYPE == ".ascii"){

    }
    else if (TYPE == ".asciiz"){

    }
    else if (TYPE == ".space") {
        
    }
    //.align
    else {
    
    }
}   