#include "lexer.h"
#include <print>

int main()
{
	std::string str = "MOV A, 123";
	std::vector<Token> list = tokenize(str);

	for (auto& token : list)
	{
		std::print("Token: content: {}, num: {}\n", token.content, token.number);
	}

	return 0;
}
