#pragma once
#include <string>
#include "lexer.h"

#define CAST_INT(x) static_cast<int>(x)
#define CAST_U8(x)  static_cast<uint8_t>(x)

// Pushing vectors (big endian)
#define PUSH8(vec, x)  (vec.push_back(CAST_U8(x)))
#define PUSH16(vec, x) (PUSH8(vec, x >> 8), PUSH8(vec, x))
#define PUSH32(vec, x) (PUSH16(vec, x >> 16), PUSH16(vec, x))

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
	std::vector<uint8_t> buffer; // Output buffer binary code
};

// Opcode lookup table
struct Op
{
	std::string name;
	int numArgs;
	Arg arg[5];
	uint8_t opcode;
};

extern Op opTables[20];

void asm_err(const std::string& msg, const std::string& file, int line, int index);

