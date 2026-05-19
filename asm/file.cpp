#include "file.h"
#include <fstream>

std::string readFile(const std::string& file)
{
	std::string line;
	std::string content;

	// Open file
	std::ifstream fileStream(file);

	while (std::getline(fileStream, line))
	{
		content.append(line);
	}

	// Close file
	fileStream.close();
	return content;
}


