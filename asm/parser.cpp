#include "parser.h"
#include "asm.h"
#include <architecture.h>
#include <print>

//
// Recursive descent parser
//

Op parseOp(const Token& token)
{
	for (auto op : opTables)
	{
		if (token.content == op.name)
		{
			return op;
		}
	}
	
	// Invalid instruction
	asm_err("Invalid instruction", token.fileName, token.lineNumber, token.lineIndex);
	exit(-1);
}

uint8_t parseReg(const Token& token)
{
	if (token.content == "A")
	{
		return REG_A;
	}
	else if (token.content == "B")
	{
		return REG_B;
	}
	else if (token.content == "C")
	{
		return REG_C;
	}
	else if (token.content == "D")
	{
		return REG_D;
	}
	else if (token.content == "E")
	{
		return REG_E;
	}
	else if (token.content == "SP")
	{
		return REG_SP;
	}
	else if (token.content == "PC")
	{
		return REG_PC;
	}
	else if (token.type == TK::NUMBER)
	{
		return REG_IMM;
	}

	// Invalid register
	asm_err("Invalid register", token.fileName, token.lineNumber, token.lineIndex);
	return 0;
}

// Returns if it reaches the end of the tokens list
bool next(Token& current, const std::vector<Token>& list, int& index)
{
	if (current.index + 1 >= CAST_INT(list.size()))
	{
		return false;
	}

	// Next index
	current = list.at(current.index + 1);
	index++;
	return true;
}

// TODO: Check for argument format
void parse(asmContext& context)
{
	std::vector<Token>& tokens = context.tokens;
	std::vector<uint8_t>& buffer = context.buffer;
	Token current = tokens.at(0);

	int i = 0;
	while (i < CAST_INT(tokens.size()))
	{
		// Parse operation
		Op op = parseOp(current);
		PUSH8(buffer, op.opcode);
		if (!next(current, tokens, i)) { break; }

		// Start parsing registers
		uint8_t srcReg = 0;
		uint8_t dstReg = 0;
		uint16_t imm = 0;

		// Parse registers (recursive descent)
		if (op.numArgs == 1)
		{
			// [OP] [SRC]
			srcReg = parseReg(current);
			
			// Check if it is an immediate register
			if (srcReg == REG_IMM)
			{
				imm = current.number;
			}
		}
		else if (op.numArgs == 2)
		{
			// [OP] [DST], [SRC]
			// Parse destination register
			dstReg = parseReg(current);

			// Check if it is an immediate register
			if (dstReg == REG_IMM)
				imm = current.number;

			if (!next(current, tokens, i)) { break; }

			// Expects a comma
			if (current.content != ",")
			{
				asm_err("Expected a comma", current.fileName, current.lineNumber, current.lineIndex);
				break;
			}
			if (!next(current, tokens, i)) { break; }

			// Parse source register
			srcReg = parseReg(current);

			// Check if it is an immediate register
			if (srcReg == REG_IMM)
				imm = current.number;
		}

		// Emit the instruction to the buffer
		PUSH8(buffer, ((srcReg << 4) | dstReg)); // Registers
		PUSH16(buffer, imm); // Immediate register

		// Advances next token
		if (!next(current, tokens, i)) { break; }
	}
}

