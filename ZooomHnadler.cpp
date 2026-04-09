#include "ZoomHandler.h"
#include <algorithm>

static sf::Color lerp(sf::Color a, sf::Color b, float t) {
    return sf::Color(
        (uint8_t)(a.r + (b.r - a.r) * t),
        (uint8_t)(a.g + (b.g - a.g) * t),
        (uint8_t)(a.b + (b.b - a.b) * t),
        (uint8_t)(a.a + (b.a - a.a) * t)
    );
}

sf::Image ZoomHandler::ZoomIn(const sf::Image& img, unsigned int f) {
    unsigned int w = img.getSize().x, h = img.getSize().y;
    sf::Image out; out.resize({ w * f, h * f });

    for (unsigned int y = 0; y < h * f; y++) {
        for (unsigned int x = 0; x < w * f; x++) {
            float gx = (float)x / f, gy = (float)y / f;
            int x0 = (int)gx, y0 = (int)gy;
            int x1 = std::min(x0 + 1, (int)w - 1), y1 = std::min(y0 + 1, (int)h - 1);

            sf::Color c00 = img.getPixel({ (unsigned)x0, (unsigned)y0 });
            sf::Color c10 = img.getPixel({ (unsigned)x1, (unsigned)y0 });
            sf::Color c01 = img.getPixel({ (unsigned)x0, (unsigned)y1 });
            sf::Color c11 = img.getPixel({ (unsigned)x1, (unsigned)y1 });

            out.setPixel({ x, y }, lerp(lerp(c00, c10, gx - x0), lerp(c01, c11, gx - x0), gy - y0));
        }
    }
    return out;
}

sf::Image ZoomHandler::ZoomOut(const sf::Image& img, unsigned int f) {
    if (f <= 1) return img;
    sf::Image out; out.resize({ img.getSize().x / f, img.getSize().y / f });
    for (unsigned int y = 0; y < out.getSize().y; y++) {
        for (unsigned int x = 0; x < out.getSize().x; x++) {
            out.setPixel({ x, y }, img.getPixel({ x * f, y * f })); // Simplifié pour la rapidité
        }
    }
    return out;
}
