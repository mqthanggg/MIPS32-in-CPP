#include "../headers/label.h"

void ADD_LABEL(const string &LABEL, unsigned int LINE){
    LABELS_LINE[LABEL] = LINE;
}

inline unsigned int GET_LABEL(const string &LABEL){
    if (LABELS_LINE.find(LABEL) == LABELS_LINE.end()) {
        SYS_PRINT("Unknown label!\n");
        return -1;
        }
    return LABELS_LINE[LABEL];
}