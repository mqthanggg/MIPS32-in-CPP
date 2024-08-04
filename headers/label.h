#pragma once
#include <map>
#include <string>

static std::map<std::string, unsigned int> LABELS_LINE;

void ADD_LABEL(const std::string& LABEL, unsigned int LINE);

inline unsigned int GET_LABEL(const std::string& LABEL);