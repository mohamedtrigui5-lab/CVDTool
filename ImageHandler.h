#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ImageHandler {
public:

public:
	
	static sf::Vector2u getImageSize(const std::string& path);

	//charger une image
	static sf::Image loadImage(const std::string& path);

	//sauvegarder une image
	static bool saveImage(const sf::Image& image, const std::string& path);

	//obtenir largeur
	static unsigned getWidh(const sf::Image& image);


	//obtenir hauteur
	static unsigned getHeight(const sf::Image& image);

	//Accés pixel sécurisé
	static sf::Color getPixelSafe(const sf::Image& image, int x, int y);

	//Modifier pixel sécurisé
	static sf::Color SetPixelSafe(sf::Image& image, int x, int y,const sf::Color& color);
};