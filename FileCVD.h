#pragma once
#include <vector>
#include <string>
#include "Encoder.h" // INDISPENSABLE ici

class FileCVD {
public:
    static void save(const std::string& filename, const std::vector<ColorBlock>& data, unsigned int width, unsigned int height);
    static std::vector<ColorBlock> load(const std::string& filename, int& width, int& height);
};
