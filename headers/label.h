#pragma once
#include "global.h"

static map<string, unsigned int> LABELS_LINE;

void ADD_LABEL(const string& LABEL, unsigned int LINE);

inline unsigned int GET_LABEL(const string& LABEL);