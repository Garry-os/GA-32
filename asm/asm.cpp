#include "asm.h"
#include <print>

void asm_err(const std::string& msg, const std::string& file, int line, int index)
{
	std::print("{} at line {} at {}: {}\n", file, line, index, msg);
}


