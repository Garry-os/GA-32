#include "file.h"
#include <fstream>
#include <memory>

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

void writeFile(const std::string& path, const std::vector<uint8_t>& buffer)
{
	std::ofstream fileStream(path, std::ios::binary);

	// Write data to the file
	fileStream.write((char*)buffer.data(), buffer.size() * sizeof(uint8_t));

	fileStream.close();
}


