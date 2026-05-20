#include "asm.h"
#include "lexer.h"
#include "file.h"
#include <print>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::print("Syntax: ./asm <file>\n");
		return -1;
	}

	char* filePath = argv[1];
	std::string content = readFile(filePath);

	asmContext context;
	context.tokens = tokenize(content, filePath);

	for (auto& token : context.tokens)
	{
		std::print("Token: content: {}, num: {}\n", token.content, token.number);
	}

	return 0;
}
