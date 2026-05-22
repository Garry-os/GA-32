#pragma once
#include <string>
#include <vector>
#include <cstdint>

std::string readFile(const std::string& file);
void writeFile(const std::string& file, const std::vector<uint8_t>& buffer);

