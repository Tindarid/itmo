#pragma once

  #include "parser.h"

extern std::string cur_string;
void next_token();
token cur_token();
void scan_string(std::string &s);
