#include "asm.h"
#include <print>

void asm_err(const std::string& msg, const std::string& file, int line)
{
	std::print("{} at line {}: {}\n", file, line, msg);
}


