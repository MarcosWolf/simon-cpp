#include "../include/Game.hpp"
#include <cstdlib>
#include <ctime>
#include <SFML/Window/Event.hpp>
#include <iostream>

using namespace std;

struct Flash {
	int buttonId;
	sf::Clock timer;
	float delay = 0.0f;
	bool started = false;
};

vector<Flash> clickFlashes;

AudioManager audio;

Game::Game()
	: window(WINDOW_WIDTH, WINDOW_HEIGHT, "simon-cpp"),
	currentStep(0),
	state(GameState::ShowingSequence),
	sequenceIndex(0)

{
	cout << "Initializing new game..." << endl;

	int gridWidth = BUTTON_SIZE * 2 + MARGIN;
	int gridHeight = BUTTON_SIZE * 2 + MARGIN;

	startX = (WINDOW_WIDTH - gridWidth) / 2;
	startY = (WINDOW_HEIGHT - gridHeight) / 2;

	audio.loadSound("green", "resources/sfx/green.ogg");
	audio.loadSound("red", "resources/sfx/red.ogg");
	audio.loadSound("yellow", "resources/sfx/yellow.ogg");
	audio.loadSound("blue", "resources/sfx/blue.ogg");
	audio.loadSound("gameover", "resources/sfx/gameover.ogg");

	cout << "Loading audios..." << endl;

	setupButtons();
	srand(static_cast<unsigned>(time(nullptr)));

	addRandomButton();

	waitingToShowSequence = true;
	sequencePauseTimer.restart();
}

void Game::playButtonSound(int id) {
	switch (id) {
	case 0: audio.play("green"); break;
	case 1: audio.play("red"); break;
	case 2: audio.play("yellow"); break;
	case 3: audio.play("blue"); break;
	}

	cout << "played button sfx[" << id << "]" << endl;
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

	cout << "[";
	for (size_t i = 0; i < sequence.size(); i++) {
		cout << sequence[i];
		if (i < sequence.size() - 1) {
			cout << ", ";
		}
	}
	cout << "]" << endl;
}

void Game::handlePlayerClick(const sf::Vector2f& mousePos) {
	for (size_t i = 0; i < buttons.size(); i++) {
		if (buttons[i].contains(mousePos)) {
			clickFlashes.push_back({ (int)i, sf::Clock(), 0.0f, false });

			playButtonSound(i);

			if (sequence[currentStep] == (int)i) {
				currentStep++;

				if (currentStep >= sequence.size()) {
					cout << "Correct entire seq... Good job" << endl;
					addRandomButton();
					currentStep = 0;

					waitingToShowSequence = true;
					sequencePauseTimer.restart();
				}
			}
			else {
				cout << "GAME OVER" << endl;
				cout << "Wrong seq... Restarting game" << endl;

				audio.play("gameover");

				state = GameState::GameOver;
				sequencePauseTimer.restart();
			}

			break;
		}
	}
}

void Game::reset() {
	sequence.clear();
	currentStep = 0;
	addRandomButton();
	sequenceIndex = 0;
	flashOn = false;
	timer.restart();
	cout << "Game restarting..." << endl;
}

bool Game::checkInput(int buttonId) {
	if (sequence[currentStep] == buttonId) {
		currentStep++;
		if (currentStep >= sequence.size()) {
			currentStep = 0;
			cout << "Correct entire seq... " << endl;
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
	for (auto it = clickFlashes.begin(); it != clickFlashes.end();) {
		int id = it->buttonId;
		if (it->timer.getElapsedTime().asSeconds() < flashDuration) {
			buttons[id].flash();
			++it;
		}
		else {
			buttons[id].resetColor();
			it = clickFlashes.erase(it);
		}
	}

	if (waitingToShowSequence) {
		if (sequencePauseTimer.getElapsedTime().asSeconds() >= pauseDuration) {
			state = GameState::ShowingSequence;
			sequenceIndex = 0;
			flashOn = false;
			waitingToShowSequence = false;
			timer.restart();
		}
		return;
	}

	if (state == GameState::ShowingSequence) {
		if (sequenceIndex < sequence.size()) {
			int btnId = sequence[sequenceIndex];
			float elapsed = timer.getElapsedTime().asSeconds();

			if (!flashOn) {
				buttons[btnId].flash();
				playButtonSound(btnId);
				flashOn = true;
				timer.restart();
			}
			else if (elapsed >= flashDuration && elapsed < flashDuration + pauseDuration) {
				if (elapsed >= flashDuration && elapsed < flashDuration + 0.01f) {
					buttons[btnId].resetColor();
				}
			}
			else if (elapsed >= flashDuration + pauseDuration) {
				flashOn = false;
				sequenceIndex++;
				timer.restart();
			}
		}
		else {
			if (timer.getElapsedTime().asSeconds() >= pauseDurationPlayer) {
				state = GameState::WaitingInput;
				currentStep = 0;
				sequenceIndex = 0;
				flashOn = false;
				cout << "Waiting player input..." << endl;
			}
		}
	}

	if (state == GameState::GameOver) {
		if (sequencePauseTimer.getElapsedTime().asSeconds() >= gameOverPause) {
			reset();
			waitingToShowSequence = true;
			state = GameState::ShowingSequence;
			sequencePauseTimer.restart();
		}
		return;
	}
}

void Game::render() {
	window.clear();
	auto& win = window.get();

	for (auto& btn : buttons)
		btn.draw(win);

	window.display();
}