#include "Encoder.h"
#include <map>

// TOLERANCE = 0  -> Lossless (Parfait mais plus lourd)
// TOLERANCE = 15 -> Lossy (Très léger, idéal pour comparer au PNG)
const int TOLERANCE = 12;

std::vector<ColorBlock> Encoder::encode(const sf::Image& img, int quality) {
    unsigned int w = img.getSize().x;
    unsigned int h = img.getSize().y;
    std::map<uint32_t, ColorBlock> layers;

    for (unsigned int y = 0; y < h; y++) {
        for (unsigned int x = 0; x < w; x++) {
            sf::Color c = img.getPixel({ x, y });
            uint32_t rgba;

            if (quality == 0) {
                // LOSSLESS : On garde la couleur exacte
                rgba = (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
            }
            else {
                // LOSSY : On réduit la précision pour regrouper les couleurs
                uint8_t r = (c.r / quality) * quality;
                uint8_t g = (c.g / quality) * quality;
                uint8_t b = (c.b / quality) * quality;
                uint8_t a = (c.a < 128) ? 0 : 255;
                rgba = (r << 24) | (g << 16) | (b << 8) | a;
            }

            if (layers.find(rgba) == layers.end()) {
                layers[rgba].color = sf::Color(
                    (rgba >> 24) & 255, (rgba >> 16) & 255, (rgba >> 8) & 255, rgba & 255
                );
            }
            layers[rgba].positions.push_back(y * w + x);
        }
    }

    std::vector<ColorBlock> result;
    for (auto& p : layers) result.push_back(p.second);
    return result;
}


sf::Image Encoder::decode(const std::vector<ColorBlock>& data, unsigned int w, unsigned int h) {
    sf::Image img({ w, h }, sf::Color::Black);

    for (const auto& b : data) {
        // Si le bitstream est vide (erreur de lecture ou de sauvegarde), on passe
        if (b.bitstream.empty()) continue;

        const uint8_t* ptr = b.bitstream.data();
        size_t streamSize = b.bitstream.size();

        for (size_t i = 0; i < streamSize; i++) {
            uint8_t byte = ptr[i];

            // ASTUCE DE L'ÎLOT : Si l'octet est 0, on saute 8 pixels d'un coup
            if (byte == 0) continue;

            // Sinon, on traite les 8 bits (pixels) de cet îlot
            for (int bit = 0; bit < 8; bit++) {
                if (byte & (1 << (7 - bit))) {
                    uint32_t pos = (uint32_t)(i * 8 + bit);

                    // Sécurité pour ne pas déborder de l'image
                    if (pos < w * h) {
                        img.setPixel({ pos % w, pos / w }, b.color);
                    }
                }
            }
        }
    }
    return img;
}
