#include "lexer.h"
#include <print>

int main()
{
	std::string str = "Hello World 123 dfsd";
	std::vector<Token> list = tokenize(str);

	for (auto& token : list)
	{
		std::print("Token: content: {}, num: {}\n", token.content, token.number);
	}

	return 0;
}
