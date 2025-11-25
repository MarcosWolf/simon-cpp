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

void Game::handlePlayerClick(const sf::Vector2f& mousePos) {
	for (size_t i = 0; i < buttons.size(); i++) {
		if (buttons[i].contains(mousePos)) {
			bool correct = checkInput(i);

			if (!correct) {
				reset();
				addRandomButton();
			}
			else if (currentStep == 0) {
				addRandomButton();
			}

			state = GameState::ShowingSequence;
			sequenceIndex = 0;
			timer.restart();

			break;
		}
	}
}

void Game::reset() {
	sequence.clear();
	currentStep = 0;
	addRandomButton();
	state = GameState::ShowingSequence;
	sequenceIndex = 0;
	timer.restart();
	cout << "Game restarting..." << endl;
}

bool Game::checkInput(int buttonId) {
	if (sequence[currentStep] == buttonId) {
		currentStep++;
		if (currentStep >= sequence.size()) {
			currentStep = 0;
			cout << "Correct entire seq... Getting " << endl;
			return true;
		}
		cout << "Correct seq... " << endl;
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
	sf::Event event;

	while (window.get().pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				window.get().close();
				break;

			case sf::Event::MouseButtonPressed:
				if (state == GameState::WaitingInput) {
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					handlePlayerClick(mousePos);
				}
				break;

			default:
				break;
		}
	}
}

void Game::update() {
	if (state == GameState::ShowingSequence) {
		if (sequenceIndex < sequence.size()) {
			int btnId = sequence[sequenceIndex];
			buttons[btnId].flash();

			if (timer.getElapsedTime().asSeconds() > flashDuration) {
				sequenceIndex++;
				timer.restart();
			}
		}
	}
	else {
		state = GameState::WaitingInput;
		sequenceIndex = 0;
	}
}

void Game::render() {
	window.clear();
	auto& win = window.get();

	for (auto& btn : buttons)
		btn.draw(win);

	window.display();
}