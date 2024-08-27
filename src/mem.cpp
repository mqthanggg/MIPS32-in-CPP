#include <windows.h>
#include "../headers/mem.h"

HANDLE cFile;
HANDLE fMapping;

int MEM_INIT(){
    
    cFile = CreateFileA(
        "mem/mem.dat", 
        GENERIC_READ | GENERIC_WRITE, 
        0, 
        0, 
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL,
        0
    );

    if (cFile == INVALID_HANDLE_VALUE){

        // printf("Failed to create file. Exiting...\n");
        SYS_PRINT("Failed to create file. Exiting...\n");
        return -1;

    }

    fMapping = CreateFileMappingA(
        cFile, 
        0, 
        PAGE_READWRITE, 
        0, 
        User::HEAP.CEIL_LIM - User::TEXT.FLOOR_LIM + 1, 
        0
    );

    if (fMapping == NULL){

        // printf("Failed to map file. Exiting...\n");
        SYS_PRINT("Failed to map file. Exiting...\n");
        return -1;

    }

    MEM_PTR = MapViewOfFile(
        fMapping, 
        FILE_MAP_ALL_ACCESS, 
        0, 
        0, 
        0
    );

    if (MEM_PTR == NULL) {

        // printf("Failed to allocate memory. Exiting...\n");
        SYS_PRINT("Failed to allocate memory. Exiting...\n");
        return -1;

    }

    User::REGS_MEM_ADDR["$v0"] = User::STATIC.FLOOR_LIM;
    User::REGS_MEM_ADDR["$v1"] = User::REGS_MEM_ADDR["$v0"] + 0x00000004;
    User::REGS_MEM_ADDR["$a0"] = User::REGS_MEM_ADDR["$v1"] + 0x00000004;
    User::REGS_MEM_ADDR["$a1"] = User::REGS_MEM_ADDR["$a0"] + 0x00000004;
    User::REGS_MEM_ADDR["$a2"] = User::REGS_MEM_ADDR["$a1"] + 0x00000004;
    User::REGS_MEM_ADDR["$a3"] = User::REGS_MEM_ADDR["$a2"] + 0x00000004;
    User::REGS_MEM_ADDR["$t0"] = User::REGS_MEM_ADDR["$a3"] + 0x00000004;
    User::REGS_MEM_ADDR["$t1"] = User::REGS_MEM_ADDR["$t0"] + 0x00000004;
    User::REGS_MEM_ADDR["$t2"] = User::REGS_MEM_ADDR["$t1"] + 0x00000004;
    User::REGS_MEM_ADDR["$t3"] = User::REGS_MEM_ADDR["$t2"] + 0x00000004;
    User::REGS_MEM_ADDR["$t4"] = User::REGS_MEM_ADDR["$t3"] + 0x00000004;
    User::REGS_MEM_ADDR["$t5"] = User::REGS_MEM_ADDR["$t4"] + 0x00000004;
    User::REGS_MEM_ADDR["$t6"] = User::REGS_MEM_ADDR["$t5"] + 0x00000004;
    User::REGS_MEM_ADDR["$t7"] = User::REGS_MEM_ADDR["$t6"] + 0x00000004;
    User::REGS_MEM_ADDR["$s0"] = User::REGS_MEM_ADDR["$t7"] + 0x00000004;
    User::REGS_MEM_ADDR["$s1"] = User::REGS_MEM_ADDR["$s0"] + 0x00000004;
    User::REGS_MEM_ADDR["$s2"] = User::REGS_MEM_ADDR["$s1"] + 0x00000004;
    User::REGS_MEM_ADDR["$s3"] = User::REGS_MEM_ADDR["$s2"] + 0x00000004;
    User::REGS_MEM_ADDR["$s4"] = User::REGS_MEM_ADDR["$s3"] + 0x00000004;
    User::REGS_MEM_ADDR["$s5"] = User::REGS_MEM_ADDR["$s4"] + 0x00000004;
    User::REGS_MEM_ADDR["$s6"] = User::REGS_MEM_ADDR["$s5"] + 0x00000004;
    User::REGS_MEM_ADDR["$s7"] = User::REGS_MEM_ADDR["$s6"] + 0x00000004;
    User::REGS_MEM_ADDR["$t8"] = User::REGS_MEM_ADDR["$s7"] + 0x00000004;
    User::REGS_MEM_ADDR["$t9"] = User::REGS_MEM_ADDR["$t8"] + 0x00000004;
    User::REGS_MEM_ADDR["$gp"] = User::REGS_MEM_ADDR["$t9"] + 0x00000004;
    User::REGS_MEM_ADDR["$sp"] = User::REGS_MEM_ADDR["$gp"] + 0x00000004;
    User::REGS_MEM_ADDR["$fp"] = User::REGS_MEM_ADDR["$sp"] + 0x00000004;
    User::REGS_MEM_ADDR["$ra"] = User::REGS_MEM_ADDR["$fp"] + 0x00000004;
    User::REGS_MEM_ADDR["pc"]  = User::REGS_MEM_ADDR["$ra"] + 0x00000004;
    User::REGS_MEM_ADDR["hi"]  = User::REGS_MEM_ADDR["pc"]  + 0x00000004;
    User::REGS_MEM_ADDR["lo"]  = User::REGS_MEM_ADDR["lo"]  + 0x00000004;

    MEM_PTR = memset(

        MEM_PTR, 
        '\0', 
        User::HEAP.CEIL_LIM - User::TEXT.FLOOR_LIM + 1

    );

    // printf("Allocate %d bytes of memory and filled with 0's successfully!\n", User::HEAP.CEIL_LIM - User::TEXT.FLOOR_LIM + 1);
    SYS_PRINT("Allocate %d bytes of memory and filled with 0's successfully!\n", User::HEAP.CEIL_LIM - User::TEXT.FLOOR_LIM + 1);
    return 0;
}

int MEM_UNMAP(){

    if (UnmapViewOfFile(MEM_PTR)){

        CloseHandle(fMapping);
        CloseHandle(cFile);
        // printf("Unmapped successfully!\n");
        SYS_PRINT("Unmapped successfully!\n");
        return 0;

    }

    // printf("Error unmapping memory!\n");
    SYS_PRINT("Error unmapping memory!\n");
    return -1;

}

void READ_MEM(const string& REG, const int& BYTES){
    unsigned char* REG_PTR = (unsigned char*)MEM_PTR + User::REGS_MEM_ADDR[REG];
    SYS_PRINT("%X ",*REG_PTR);
    for (short byte = 1; byte < BYTES; byte++) {
        SYS_PRINT("| %u ", *(REG_PTR + byte));
    }
    return;
}

int WRITE_MEM(const string &SOURCE_REG, const string &DES_REG, const int& BYTES, const int &OFFSET){
    unsigned char* SOURCE_REG_PTR = (unsigned char*)MEM_PTR + User::REGS_MEM_ADDR[SOURCE_REG];
    unsigned char* DES_REG_PTR = (unsigned char*)MEM_PTR + User::REGS_MEM_ADDR[DES_REG] + OFFSET/4;
    for (short byte = 0; byte < BYTES; byte++)
        DES_REG_PTR[byte] = SOURCE_REG_PTR[byte];
    return 0;
}

int WRITE_MEM(const unsigned int& SOURCE_ADDR, const string& DES_REG, const int& BYTES, const int& OFFSET){
    if (SOURCE_ADDR < User::HEAP.FLOOR_LIM || SOURCE_ADDR > User::HEAP.CEIL_LIM){
        SYS_PRINT("Error accessing address 0x%08x! Permission denied!\n", SOURCE_ADDR);
        return -1;
    }
    unsigned char* SOURCE_ADDR_PTR = (unsigned char*)MEM_PTR + SOURCE_ADDR;
    unsigned char* DES_REG_PTR = (unsigned char*)MEM_PTR + User::REGS_MEM_ADDR[DES_REG] + OFFSET/4;
    for (short byte = 0; byte < BYTES; byte++)
        DES_REG_PTR[byte] = SOURCE_ADDR_PTR[byte];
    return 0;
}

int WRITE_MEM(const string& SOURCE_REG, const unsigned int& DES_ADDR, const int& BYTES, const int& OFFSET){
    if (DES_ADDR < User::HEAP.FLOOR_LIM || DES_ADDR > User::HEAP.CEIL_LIM){
        SYS_PRINT("Error accessing address 0x%08x! Permission denied!\n", DES_ADDR);
        return -1;
    }
    unsigned char* SOURCE_ADDR_PTR = (unsigned char*)MEM_PTR + User::REGS_MEM_ADDR[SOURCE_REG] + OFFSET/4;
    unsigned char* DES_REG_PTR = (unsigned char*)MEM_PTR + DES_ADDR;
    for (short byte = 0; byte < BYTES; byte++)
        DES_REG_PTR[byte] = SOURCE_ADDR_PTR[byte];
    return 0;
}

unsigned char* GET_REG_PTR(const string& REG){
    if (REG == "$zero" || REG == "$r0") return ZERO_PTR;
    return (unsigned char*)MEM_PTR + User::REGS_MEM_ADDR[REG];
}

int GET_MEM_CONTENT(const string &REG, const int& BYTES){
    int RETURN_CONTENT = 0;
    unsigned char* REG_PTR = (unsigned char*)MEM_PTR + User::REGS_MEM_ADDR[REG];
    for (short byte = 0; byte < BYTES; byte++)
        RETURN_CONTENT |= REG_PTR[byte] >> (3-byte) * 8;
    return RETURN_CONTENT;
}

// int main(){
//     int ret = MEM_INIT();
//     if (!ret) {
//         int unmap = MEM_UNMAP();
//         return unmap;
//         }
//     return 1;
// }