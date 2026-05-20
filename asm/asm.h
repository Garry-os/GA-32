#pragma once
#include <string>
#include "lexer.h"

enum class Arg
{
	REG = (1 << 0),
	IMM = (1 << 1),
	IMM_REG = (IMM | REG)
};

// Assembler context
struct asmContext
{
	std::vector<Token> tokens;
};

// Opcode lookup table
struct Op
{
	std::string name;
	int numArgs;
	Arg arg[5];
	uint8_t opcode;
};

extern Op opTables[];

void asm_err(const std::string& msg, const std::string& file, int line, int index);

