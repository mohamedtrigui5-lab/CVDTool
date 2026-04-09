#pragma once
#include <SFML/Graphics.hpp>

class ZoomHandler
{
public:
    static sf::Image ZoomIn(const sf::Image& img, unsigned int factor);
    static sf::Image ZoomOut(const sf::Image& img, unsigned int factor);
};