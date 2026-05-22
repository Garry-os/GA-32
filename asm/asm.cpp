#include "asm.h"
#include <print>
#include <architecture.h>

Op opTables[20] = {
	{
		"MOV",
		2,
		{ Arg::REG, Arg::IMM_REG },
		OP_MOV
	},
	{
		"LOAD",
		2,
		{ Arg::REG, Arg::IMM_REG },
		OP_LOAD
	},
	{
		"STORE",
		2,
		{ Arg::IMM_REG, Arg::REG },
		OP_STORE
	},
	{
		"PUSH",
		1,
		{ Arg::IMM_REG },
		OP_PUSH
	},
	{
		"POP",
		1,
		{ Arg::REG },
		OP_POP
	},
	{
		"JNZ",
		1,
		{ Arg::IMM_REG },
		OP_JNZ
	},
	{
		"ADD",
		2,
		{ Arg::REG, Arg::IMM_REG },
		OP_ADD
	},
	{
		"SUB",
		2,
		{ Arg::REG, Arg::IMM_REG },
		OP_SUB
	},
	{
		"CALL",
		1,
		{ Arg::IMM_REG },
		OP_CALL
	},
	{
		"RET",
		0,
		{  },
		OP_RET
	},
	{
		"HLT",
		0,
		{  },
		OP_HLT
	},
	{
		"NOP",
		0,
		{  },
		OP_NOP
	},
	{
		"MOVU",
		2,
		{ Arg::REG, Arg::IMM },
		OP_MOVU
	}
};

void asm_err(const std::string& msg, const std::string& file, int line, int index)
{
	std::print("{} at line {} at {}: {}\n", file, line, index, msg);
}


