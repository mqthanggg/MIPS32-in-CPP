#include "../headers/instruction.h"
#define ZERO '0'
#define ONE '1' 
// #include <iostream>

void REG_READ_ADDR(const Register& REG){
    SYS_PRINT("Value: %c ", REG.SIGN == 0 ? '+' : '-');
    READ_MEM(REG.REG_NAME, REG.BYTES);
    SYS_PRINT("\n");
    return;
}

void ADD(Register& DES_REG, const Register& ARG1, const Register& ARG2){
    unsigned char* DES_REG_PTR = GET_REG_PTR(DES_REG.REG_NAME);
    unsigned char* ARG1_PTR = GET_REG_PTR(ARG1.REG_NAME);
    unsigned char* ARG2_PTR = GET_REG_PTR(ARG2.REG_NAME);
    for (short i = 3; i >= 0; i--)
        DES_REG_PTR[i] = ARG1_PTR[i] + ARG2_PTR[i];

    REG_READ_ADDR(DES_REG);
    return;
}

void SUB(Register& DES_REG, const Register& ARG1, const Register& ARG2){
    unsigned char* DES_REG_PTR = GET_REG_PTR(DES_REG.REG_NAME);
    unsigned char* ARG1_PTR = GET_REG_PTR(ARG1.REG_NAME);
    unsigned char* ARG2_PTR = GET_REG_PTR(ARG2.REG_NAME);
    for (short i = 3; i >= 0; i--)
        DES_REG_PTR[i] = ARG1_PTR[i] - ARG2_PTR[i];
    
    REG_READ_ADDR(DES_REG);
    return;
}

void ORI(Register &DES_REG, const Register &ARG1, const int& IMMEDIATE){
    unsigned char* DES_REG_PTR = GET_REG_PTR(DES_REG.REG_NAME);
    unsigned char* ARG1_PTR = GET_REG_PTR(ARG1.REG_NAME);

    for (short i = 0; i < 4; i++)
        DES_REG_PTR[i] = ARG1_PTR[i] | IMMEDIATE >> (i * 8) & 0x000000FF;

    REG_READ_ADDR(DES_REG);
    return;
}

int LW(Register &DES_REG, const Register &ARG, const int &IMMEDIATE){
    int ARG_CONTENT = GET_MEM_CONTENT(ARG.REG_NAME);
    return WRITE_MEM(ARG_CONTENT, DES_REG.REG_NAME, 4, IMMEDIATE);
}

int SW(Register& DES_REG, const Register& ARG, const int& IMMEDIATE){
    int ARG_CONTENT = GET_MEM_CONTENT(ARG.REG_NAME);
    return WRITE_MEM(DES_REG.REG_NAME, ARG_CONTENT,4,IMMEDIATE);
}
// int main(){
//     int num = 0;
//     while(true) {
//         cout << "Num: ";
//         cin >> num;
//         if (num == -1) break;
//         string* test = NUM_TO_BYTE(num);
//         for (short i = 0; i < 4; i++) {
//             SYS_PRINT("Byte #%d: %s\n", i, test[i].c_str());
//         }
//         delete [] test;
//     }
//     return 0;
// }