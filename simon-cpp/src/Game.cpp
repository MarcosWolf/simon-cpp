#include "../include/Game.hpp"
#include <cstdlib>
#include <ctime>
#include <SFML/Window/Event.hpp>
#include <iostream>

using namespace std;

Game::Game()
	: window(WINDOW_WIDTH, WINDOW_HEIGHT, "simon-cpp"),
	currentStep(0)
{
	cout << "Initializing..." << endl;

	int gridWidth = BUTTON_SIZE * 2 + MARGIN;
	int gridHeight = BUTTON_SIZE * 2 + MARGIN;

	startX = (WINDOW_WIDTH - gridWidth) / 2;
	startY = (WINDOW_HEIGHT - gridHeight) / 2;

	setupButtons();

	srand(static_cast<unsigned>(time(nullptr)));
}

void Game::setupButtons() {
	buttons.emplace_back(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), sf::Vector2f(startX, startY), sf::Color::Green);
	buttons.emplace_back(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), sf::Vector2f(startX + BUTTON_SIZE + MARGIN, startY), sf::Color::Red);
	buttons.emplace_back(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), sf::Vector2f(startX, startY + BUTTON_SIZE + MARGIN), sf::Color::Yellow);
	buttons.emplace_back(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), sf::Vector2f(startX + BUTTON_SIZE + MARGIN, startY + BUTTON_SIZE + MARGIN), sf::Color::Blue);

	cout << "Setting buttons..." << endl;
}

void Game::addRandomButton() {
	int buttonId = std::rand() % 4;
	sequence.push_back(buttonId);

	cout << "New seq generated.... " << buttonId << endl;
}

void Game::reset() {
	sequence.clear();
	currentStep = 0;
	cout << "Game restarting..." << endl;
}

bool Game::checkInput(int buttonId) {
	if (sequence[currentStep] == buttonId) {
		currentStep++;
		if (currentStep >= sequence.size()) {
			currentStep = 0;
			cout << "Right seq... Game over" << endl;
			return true;
		}
		cout << "Right seq ... " << endl;
		return true;
	}
	cout << "Wrong seq... Game over" << endl;
	return false;
}

const vector<int>& Game::getSequence() const {
	return sequence;
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