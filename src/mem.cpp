#include <windows.h>
#include "../headers/mem.h"

int MEM_INIT(){

    MEM_PTR = VirtualAlloc(
        NULL, 
        User::HEAP.CEIL_LIM - User::TEXT.FLOOR_LIM + 1, 
        MEM_COMMIT | MEM_RESERVE, 
        PAGE_READWRITE
        );

    if (MEM_PTR == NULL) {

        printf("Failed to allocate memory. Exiting...\n");
        // SYS_PRINT("Failed to allocate memory. Exiting...\n");
        return -1;

    }

    User::REGS_MEM_ADDR["$v0"] = User::STATIC.FLOOR_LIM;
    User::REGS_MEM_ADDR["$v1"] = User::REGS_MEM_ADDR["$v0"] + 0x00000020;
    User::REGS_MEM_ADDR["$a0"] = User::REGS_MEM_ADDR["$v1"] + 0x00000020;
    User::REGS_MEM_ADDR["$a1"] = User::REGS_MEM_ADDR["$a0"] + 0x00000020;
    User::REGS_MEM_ADDR["$a2"] = User::REGS_MEM_ADDR["$a1"] + 0x00000020;
    User::REGS_MEM_ADDR["$a3"] = User::REGS_MEM_ADDR["$a2"] + 0x00000020;
    User::REGS_MEM_ADDR["$t0"] = User::REGS_MEM_ADDR["$a3"] + 0x00000020;
    User::REGS_MEM_ADDR["$t1"] = User::REGS_MEM_ADDR["$t0"] + 0x00000020;
    User::REGS_MEM_ADDR["$t2"] = User::REGS_MEM_ADDR["$t1"] + 0x00000020;
    User::REGS_MEM_ADDR["$t3"] = User::REGS_MEM_ADDR["$t2"] + 0x00000020;
    User::REGS_MEM_ADDR["$t4"] = User::REGS_MEM_ADDR["$t3"] + 0x00000020;
    User::REGS_MEM_ADDR["$t5"] = User::REGS_MEM_ADDR["$t4"] + 0x00000020;
    User::REGS_MEM_ADDR["$t6"] = User::REGS_MEM_ADDR["$t5"] + 0x00000020;
    User::REGS_MEM_ADDR["$t7"] = User::REGS_MEM_ADDR["$t6"] + 0x00000020;
    User::REGS_MEM_ADDR["$s0"] = User::REGS_MEM_ADDR["$t7"] + 0x00000020;
    User::REGS_MEM_ADDR["$s1"] = User::REGS_MEM_ADDR["$s0"] + 0x00000020;
    User::REGS_MEM_ADDR["$s2"] = User::REGS_MEM_ADDR["$s1"] + 0x00000020;
    User::REGS_MEM_ADDR["$s3"] = User::REGS_MEM_ADDR["$s2"] + 0x00000020;
    User::REGS_MEM_ADDR["$s4"] = User::REGS_MEM_ADDR["$s3"] + 0x00000020;
    User::REGS_MEM_ADDR["$s5"] = User::REGS_MEM_ADDR["$s4"] + 0x00000020;
    User::REGS_MEM_ADDR["$s6"] = User::REGS_MEM_ADDR["$s5"] + 0x00000020;
    User::REGS_MEM_ADDR["$s7"] = User::REGS_MEM_ADDR["$s6"] + 0x00000020;
    User::REGS_MEM_ADDR["$t8"] = User::REGS_MEM_ADDR["$s7"] + 0x00000020;
    User::REGS_MEM_ADDR["$t9"] = User::REGS_MEM_ADDR["$t8"] + 0x00000020;
    User::REGS_MEM_ADDR["$gp"] = User::REGS_MEM_ADDR["$t9"] + 0x00000020;
    User::REGS_MEM_ADDR["$sp"] = User::REGS_MEM_ADDR["$gp"] + 0x00000020;
    User::REGS_MEM_ADDR["$fp"] = User::REGS_MEM_ADDR["$sp"] + 0x00000020;
    User::REGS_MEM_ADDR["$ra"] = User::REGS_MEM_ADDR["$fp"] + 0x00000020;

    MEM_PTR = memset(

        MEM_PTR, 
        '\0', 
        User::HEAP.CEIL_LIM - User::TEXT.FLOOR_LIM + 1

    );

    printf("Allocate %d bits of memory successfully!\n", User::HEAP.CEIL_LIM - User::TEXT.FLOOR_LIM + 1);
    // SYS_PRINT("Allocate %d bits of memory successfully!\n", User::TEXT.CEIL_LIM - User::TEXT.FLOOR_LIM);
    return 0;
}

int MEM_UNMAP(){

    if (VirtualFree(MEM_PTR, 0, MEM_RELEASE)) {

        printf("Unmapped successfully!\n");
        // SYS_PRINT("Unmapped successfully!\n");
        return 1;

    }

    printf("Error unmapping memory!\n");
    SYS_PRINT("Error unmapping memory!\n");
    return -1;

}

string* GET_MEM(const string& REG, const int& OFFSET){
    unsigned char* base_addr = MEM_PTR[User::REGS_MEM_ADDR[REG] + OFFSET];
    string* OUT_ADDR = new string[4];
    //READ BITS BY BITS
}

int main(){
    int ret = MEM_INIT();
    
    return ret;
}