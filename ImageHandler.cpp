// ImageHandler.cpp
#include "ImageHandler.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Image ImageHandler::loadImage(const std::string& path)
{
    sf::Image img;

    if (!img.loadFromFile(path))
    {
        std::cerr << "Erreur : impossible de charger l'image : " << path << std::endl;

        // Image de fallback (optionnel)
        img.resize({ 1, 1 }, sf::Color::Magenta);

        return img;
    }

    std::cout << "Image chargee avec succes : " << path << std::endl;
    std::cout << "Taille : "
        << img.getSize().x << " x "
        << img.getSize().y << std::endl;

    return img;
}


sf::Vector2u ImageHandler::getImageSize(const std::string& path) {
    sf::Image img;
    if (!img.loadFromFile(path)) {
        std::cerr << "Erreur ouverture image\n";
        return { 0,0 };
    }
    sf::Vector2u size = img.getSize();
    if (size.x > 65536) size.x = 65536;
    if (size.y > 65536) size.y = 65536;
    return size;
}

