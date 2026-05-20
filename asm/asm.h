#pragma once
#include <string>
#include "lexer.h"

struct asmContext
{
	std::vector<Token> tokens;
};

void asm_err(const std::string& msg, const std::string& file, int line, int index);

