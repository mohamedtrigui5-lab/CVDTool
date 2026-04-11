#include "FileCVD.h"
#include <fstream>

void FileCVD::save(const std::string& filename, const std::vector<ColorBlock>& data, unsigned int width, unsigned int height) {
    std::ofstream f(filename, std::ios::binary);
    if (!f) return;

    f.write("CVD", 3);
    uint32_t w = width, h = height;
    f.write((char*)&w, 4);
    f.write((char*)&h, 4);

    uint32_t blockCount = (uint32_t)data.size();
    f.write((char*)&blockCount, 4);

    for (const auto& b : data) {
        f.write((char*)&b.color.r, 1);
        f.write((char*)&b.color.g, 1);
        f.write((char*)&b.color.b, 1);
        f.write((char*)&b.color.a, 1);

        uint32_t streamSize = (uint32_t)b.bitstream.size();
        f.write((char*)&streamSize, 4);
        // FIX C2660 : Il faut le buffer ET la taille
        f.write((char*)b.bitstream.data(), streamSize);
    }
}

std::vector<ColorBlock> FileCVD::load(const std::string& filename, int& width, int& height) {
    std::ifstream f(filename, std::ios::binary);
    std::vector<ColorBlock> result;
    if (!f) return result;

    char sig[3];
    f.read(sig, 3); // "CVD"

    uint32_t w, h, count;
    f.read((char*)&w, 4);
    f.read((char*)&h, 4);
    f.read((char*)&count, 4);

    width = w;
    height = h;

    for (uint32_t i = 0; i < count; i++) {
        ColorBlock b;
        // Lecture RGBA (4 octets)
        f.read((char*)&b.color.r, 1);
        f.read((char*)&b.color.g, 1);
        f.read((char*)&b.color.b, 1);
        f.read((char*)&b.color.a, 1);

        uint32_t streamSize;
        f.read((char*)&streamSize, 4);

        // Sécurité : évite d'allouer trop de RAM si le fichier est corrompu
        if (streamSize > 0 && streamSize < 10000000) {
            b.bitstream.resize(streamSize);
            f.read((char*)b.bitstream.data(), streamSize);
            result.push_back(b);
        }
    }
    return result;
}
