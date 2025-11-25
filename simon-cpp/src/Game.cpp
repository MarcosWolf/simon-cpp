#include "../include/Game.hpp"
#include <SFML/Window/Event.hpp>

Game::Game()
	: window(800, 600, "simon-cpp")
{
	buttons.emplace_back(sf::Vector2f(250, 250), sf::Vector2f(50, 50), sf::Color::Green);
	buttons.emplace_back(sf::Vector2f(250, 250), sf::Vector2f(300, 50), sf::Color::Red);
	buttons.emplace_back(sf::Vector2f(250, 250), sf::Vector2f(50, 300), sf::Color::Yellow);
	buttons.emplace_back(sf::Vector2f(250, 250), sf::Vector2f(300, 300), sf::Color::Blue);
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {

}

void Game::update() {

}

void Game::render() {
	window.clear();
	auto& win = window.get();

	for (auto& btn : buttons)
		btn.draw(win);

	window.display();
}