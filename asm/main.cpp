#include "asm.h"
#include "lexer.h"
#include "file.h"
#include "parser.h"
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

	parse(context);

	writeFile("a.out", context.buffer);

	return 0;
}
