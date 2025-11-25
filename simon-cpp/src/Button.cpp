#include "../include/Button.hpp"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
	: baseColor(color)
{
	shape.setSize(size);
	shape.setFillColor(color);
	shape.setPosition(position);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

bool Button::isClicked(const sf::Vector2f& mousePos) {
	return shape.getGlobalBounds().contains(mousePos);
}

void Button::flash() {
	shape.setFillColor(sf::Color::White);
}

void Button::resetColor() {
	shape.setFillColor(baseColor);
}

bool Button::contains(const sf::Vector2f& point) const {
	return shape.getGlobalBounds().contains(point);
}