#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::RectangleShape shape;
	sf::Color baseColor;

public:
	Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);

	void draw(sf::RenderWindow& window);
	bool isClicked(const sf::Vector2f& mousePos);
	void flash();
	void resetColor();

	bool contains(const sf::Vector2f& point) const;
};