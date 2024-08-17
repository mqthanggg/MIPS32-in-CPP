#include "../headers/instruction.h"
#define ZERO '0'
#define ONE '1' 
// #include <iostream>

void REG_READ_ADDR(const Register& REG){
    SYS_PRINT("Value: %c %s", REG.SIGN == 0 ? '+' : '-', REG.ADDR[0].c_str());
    for (short i = 1; i < REG.BYTES; i++) {
        SYS_PRINT("|%s",REG.ADDR[i].c_str());
    }
    SYS_PRINT("\n");
    return;
}

string* NUM_TO_BYTE(const int& NUM){
    string* ADDR = new string[4];
    ADDR[3] = ADDR[2] = ADDR[1] = ADDR[0] = "00000000";
    for (short i = 31, byte = 0, bit = 0; i >= 0; i--) {
        int k = NUM >> i;
        if (k & 1) ADDR[byte][bit] = ONE;
        else ADDR[byte][bit] = ZERO;
        if (i % 8 == 0 || bit == 7) {
            byte++; 
            bit = 0;
        }
        else bit++;
    }
    return ADDR;
}

string BITS_OR(const string& byte1, const string& byte2){
    string BITS_RESULT = "00000000";
    for (short i = 7; i >= 0; i--) {
        if (byte1[i] == ZERO && byte2[i] == ZERO) BITS_RESULT[i] = ZERO;
        else BITS_RESULT[i] = ONE;
    }
    return BITS_RESULT;
}

string BITS_SUB(bool& OVERFLOW, const string& byte1, const string& byte2){
    bool        borrow       = OVERFLOW;
    string BITS_RESULT = "00000000";
    for (short i = 7; i >= 0; i--){
        if (borrow) {

            //1, 1 or 0, 0
            if (byte1[i] == ONE && 
                byte2[i] == ONE ||
                byte1[i] == ZERO &&
                byte2[i] == ZERO)
                    BITS_RESULT[i] = ONE;

            //1, 0
            else if (byte1[i] == ONE ) 
                {

                    BITS_RESULT[i] = ZERO;
                    borrow = false;

                }
            
            //0, 1
            else 
                BITS_RESULT[i] = ZERO;
        }
        else {
            
            //1, 1 or 0, 0
            if (byte1[i] == ONE && 
                byte2[i] == ONE ||
                byte1[i] == ZERO &&
                byte2[i] == ZERO)
                    BITS_RESULT[i] = ZERO;

            //1, 0
            else if (byte1[i] == ONE ) 
                    BITS_RESULT[i] = ONE;
            
            //0, 1
            else 
                {

                    BITS_RESULT[i] = ONE;
                    borrow = true;

                }
            }
    }
    return BITS_RESULT;
}

string BITS_ADD(bool& OVERFLOW, const string& byte1, const string& byte2){
    bool        carry       = OVERFLOW;
    string BITS_RESULT = "00000000";
    for (short i = 7; i >= 0; i--) {
        if (carry) {

            //1, 1
            if (byte1[i] == ONE && 
                byte2[i] == ONE)
                BITS_RESULT[i] = ONE;

            //1, 0 or 0, 1
            else if (byte1[i] == ONE || 
                     byte1[i] == ZERO && 
                     byte2[i] == ONE) 
                BITS_RESULT[i] = ZERO;

            //0, 0
            else {

                BITS_RESULT[i] = ONE;
                carry = false;

            }

        }
        else {
            
            //1, 1
            if (byte1[i] == ONE && 
                byte2[i] == ONE)
                {

                    BITS_RESULT[i] = ZERO;
                    carry = true;

                }

            //1, 0 or 0, 1
            else if (byte1[i] == ONE || 
                     byte1[i] == ZERO && 
                     byte2[i] == ONE) 
                BITS_RESULT[i] = ONE;

            //0, 0
            else
                BITS_RESULT[i] = ZERO;

        }
    }
    if (carry) OVERFLOW = true;
    return BITS_RESULT;
}

void ADD(Register& DES_REG, const Register& ARG1, const Register& ARG2){
    bool OVERFLOW = false;

    for (short i = 3; i >= 0; i--)
        DES_REG.ADDR[i] = BITS_ADD(OVERFLOW, ARG1.ADDR[i], ARG2.ADDR[i]);

    if (OVERFLOW) 
        SYS_PRINT("Warning!: Overflow detected when ADD.\n");

    REG_READ_ADDR(DES_REG);
    return;
}

void SUB(Register& DES_REG, const Register& ARG1, const Register& ARG2){
    bool OVERFLOW = false;

    for (short i = 3; i >= 0; i--)
        DES_REG.ADDR[i] = BITS_SUB(OVERFLOW, ARG1.ADDR[i], ARG2.ADDR[i]);

    if (OVERFLOW){
        SYS_PRINT("Warning!: Overflow detected when SUB.\n");
        DES_REG.SIGN = 1;    
    }
    
    REG_READ_ADDR(DES_REG);
    return;
}

void ORI(Register &DES_REG, const Register &ARG1, const int& IMMEDIATE){
    string* IMMEDIATE_ADDR = NUM_TO_BYTE(IMMEDIATE);

    for (short i = 0; i < 4; i++)
        DES_REG.ADDR[i] = BITS_OR(ARG1.ADDR[i], IMMEDIATE_ADDR[i]);

    REG_READ_ADDR(DES_REG);
    return;
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