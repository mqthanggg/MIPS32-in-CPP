#pragma once
#include "global.h"
#include "instruction.h"
#include "register.h"
#include "mem.h"

static ifstream input_file;
static ofstream output_file;

int compile(const string& INPUT_FILE_NAME);