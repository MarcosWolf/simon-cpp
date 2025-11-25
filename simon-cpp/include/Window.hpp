#pragma once
#include <SFML/Graphics.hpp>

class Window {
private:
	sf::RenderWindow window;

public:
	Window(int width, int height, const std::string& title);
	bool isOpen();
	void clear();
	void display();
	sf::RenderWindow& get();
};