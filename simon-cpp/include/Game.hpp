#pragma once
#include "Window.hpp"
#include "Button.hpp"
#include "CursorManager.hpp"
#include "AudioManager.hpp"
#include "SequenceManager.hpp"
#include "FlashManager.hpp"
#include "SequencePlayer.hpp"
#include "ScoreDisplay.hpp"
#include <vector>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int BUTTON_SIZE = 200;
constexpr int MARGIN = 50;

enum class GameState {
	ShowingSequence,
	WaitingInput,
	WaitingNextRound,
	GameOver
};

class Game {
private:
	Window window;
	std::vector<Button> buttons;

	CursorManager cursorManager;
	AudioManager audioManager;
	SequenceManager sequenceManager;
	FlashManager flashManager;
	SequencePlayer sequencePlayer;
	ScoreDisplay scoreDisplay;

	GameState state;
	sf::Clock stateTimer;

	int startX;
	int startY;

	const float PAUSE_BETWEEN_BUTTONS = 0.5f;
	const float PAUSE_AFTER_PLAYER = 0.6f;
	const float GAME_OVER_PAUSE = 5.0f;

public:
	Game();
	void run();

private:
	void setupButtons();
	void loadAudio();
	void loadCursors();
	void updateCursorHover();
	void playButtonSound(int id);
	void handlePlayerClick(const sf::Vector2f& mousePos);
	void startNewRound();
	void gameOver();
	void reset();

	void processEvents();
	void update();
	void render();
};