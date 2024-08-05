#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "../headers/instruction.h"
#include "../headers/register.h"

using namespace std;

int compile(const string& INPUT_FILE_NAME, const string& OUTPUT_FILE_NAME);