#include "lexer.h"
#include <cctype>
#include "asm.h"
#include <charconv>


bool convStrToNum(const std::string& str, int32_t& out)
{
	auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), out);
	(void)ptr;

	// Check 16-bit range
	if (out < 0 || out > 65535)
	{
		return false;
	}

	return true;
}

std::vector<Token> tokenize(const std::string& src, const std::string& fileName)
{
	std::vector<Token> tokens;
	std::vector<char> buffer;

	size_t i = 0;
	int lineCounter = 0;
	int lineIndex = 0;
	while (i < src.length())
	{
		char c = src[i];

		if (std::isalpha(c))
		{
			// Save to the buffer
			buffer.push_back(c);
			i++;

			// Do this until the end of the token
			while (i < src.length() && std::isalpha(src.at(i)))
			{
				buffer.push_back(src.at(i));
				i++;
			}

			// Push into token list
			tokens.push_back({ TK::INSTRUCTION, std::string(buffer.begin(), buffer.end()), 0, lineCounter, lineIndex, fileName, CAST_INT(tokens.size()) });
			buffer.clear();
		}
		else if (std::isdigit(c))
		{
			// Save to the buffer
			buffer.push_back(c);
			i++;

			// Do this until the end of the token
			while (i < src.length() && std::isdigit(src.at(i)))
			{
				buffer.push_back(src.at(i));
				i++;
			}

			// Push into token list
			// Convert to number
			std::string str(buffer.begin(), buffer.end());
			int32_t num;
			convStrToNum(str, num);

			tokens.push_back({ TK::NUMBER, str, num, lineCounter, lineIndex, fileName, CAST_INT(tokens.size()) });
			buffer.clear();
		}
		else if (c == ',')
		{
			tokens.push_back({ TK::COMMA, std::string(","), 0, lineCounter, lineIndex, fileName, CAST_INT(tokens.size()) });
			i++;
		}
		else if (c == '\n')
		{
			lineCounter++;
			lineIndex = 0;
			i++;
			continue;
		}
		else if (std::isspace(c))
		{
			// Ignore whitespace
			i++;
		}
		else
		{
			asm_err("Invalid token", fileName, lineCounter, lineIndex);
			break;
		}

		lineIndex++;
	}

	return tokens;
}

