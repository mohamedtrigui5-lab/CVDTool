#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>

struct ColorBlock {
    sf::Color color;
    std::vector<uint8_t> bitstream; // 1 bit = 1 pixel
    std::vector<uint32_t> positions; // Gardé pour tes tests si besoin
};

class Encoder {
public:
    // On ajoute le paramètre quality pour le mode Lossy
    static std::vector<ColorBlock> encode(const sf::Image& img, int quality = 0);
    static sf::Image decode(const std::vector<ColorBlock>& data, unsigned int w, unsigned int h);
};
