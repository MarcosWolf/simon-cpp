#include "../include/Game.hpp"
#include <ctime>
#include <SFML/Window/Event.hpp>
#include <iostream>

Game::Game()
	: window(WINDOW_WIDTH, WINDOW_HEIGHT, "simon-cpp"),
	state(GameState::ShowingSequence)
{
	int gridWidth = BUTTON_SIZE * 2 + MARGIN;
	int gridHeight = BUTTON_SIZE * 2 + MARGIN;
	startX = (WINDOW_WIDTH - gridWidth) / 2;
	startY = (WINDOW_HEIGHT - gridHeight) / 2;

	setupButtons();
	loadAudio();

	std::srand(static_cast<unsigned>(time(nullptr)));
	sequenceManager.addRandom();

	stateTimer.restart();
}

void Game::setupButtons() {
	buttons.emplace_back(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), sf::Vector2f(startX, startY), sf::Color::Green);
	buttons.emplace_back(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), sf::Vector2f(startX + BUTTON_SIZE + MARGIN, startY), sf::Color::Red);
	buttons.emplace_back(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), sf::Vector2f(startX, startY + BUTTON_SIZE + MARGIN), sf::Color::Yellow);
	buttons.emplace_back(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), sf::Vector2f(startX + BUTTON_SIZE + MARGIN, startY + BUTTON_SIZE + MARGIN), sf::Color::Blue);
}

void Game::loadAudio() {
	audioManager.loadSound("green", "resources/sfx/green.ogg");
	audioManager.loadSound("red", "resources/sfx/red.ogg");
	audioManager.loadSound("yellow", "resources/sfx/yellow.ogg");
	audioManager.loadSound("blue", "resources/sfx/blue.ogg");
	audioManager.loadSound("gameover", "resources/sfx/gameover.ogg");
}

void Game::playButtonSound(int id) {
	const char* sounds[] = { "green", "red", "yellow", "blue" };
	if (id >= 0 && id < 4) {
		audioManager.play(sounds[id]);
	}
}

void Game::handlePlayerClick(const sf::Vector2f& mousePos) {
	for (size_t i = 0; i < buttons.size(); i++) {
		if (buttons[i].contains(mousePos)) {
			flashManager.add(i);
			playButtonSound(i);

			if (sequenceManager.checkStep(i)) {
				if (sequenceManager.isSequenceComplete()) {
					startNewRound();
				}
			}
			else {
				std::cout << "Game Over" << std::endl;
				gameOver();
			}
			break;
		}
	}
}

void Game::startNewRound() {
	sequenceManager.addRandom();
	sequenceManager.resetStep();
	state = GameState::ShowingSequence();
	sequencePlayer.reset();
	stateTimer.restart();
}

void Game::gameOver() {
	audioManager.play("gameover");
	state = GameState::GameOver;
	stateTimer.restart();
}

void Game::reset() {
	sequenceManager.clear();
	sequenceManager.addRandom();
	sequencePlayer.reset();
	state = GameState::ShowingSequence;
	stateTimer.restart();
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
		if (event.type == sf::Event::Closed) {
			window.get().close();
		}
		else if (event.type == sf::Event::MouseButtonPressed &&
			state == GameState::WaitingInput) {
			sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
			handlePlayerClick(mousePos);
		}
	}
}

void Game::update() {
    flashManager.update(buttons);

    switch (state) {
        case GameState::ShowingSequence:
            if (stateTimer.getElapsedTime().asSeconds() >= PAUSE_BETWEEN_BUTTONS) {
                bool done = sequencePlayer.update(
                    sequenceManager.getSequence(), 
                    buttons,
                    [this](int id) { playButtonSound(id); }
                );
                
                if (done) {
                    state = GameState::WaitingInput;
                    sequenceManager.resetStep();
                    std::cout << "Sua vez!" << std::endl;
                }
            }
            break;

        case GameState::GameOver:
            if (stateTimer.getElapsedTime().asSeconds() >= GAME_OVER_PAUSE) {
                reset();
            }
            break;

        case GameState::WaitingInput:
            // Aguardando clique do jogador
            break;
    }
}

void Game::render() {
	window.clear();
	auto& win = window.get();

	for (auto& btn : buttons)
		btn.draw(win);

	window.display();
}