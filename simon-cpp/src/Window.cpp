#include "../include/Window.hpp";

Window::Window(int width, int height, const std::string& title)
	: window(sf::VideoMode(width, height), title) { }

bool Window::isOpen() {
	return window.isOpen();
}

void Window::clear() {
	window.clear();
}

void Window::display() {
	window.display();
}

sf::RenderWindow& Window::get() {
	return window;
}