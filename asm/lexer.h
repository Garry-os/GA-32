#pragma once
#include <cstdint>
#include <string>
#include <vector>

enum class TK
{
	NUMBER,
	INSTRUCTION,
	COMMA
};

struct Token
{
	TK type;
	std::string content;
	int32_t number;
};

std::vector<Token> tokenize(const std::string& src);

