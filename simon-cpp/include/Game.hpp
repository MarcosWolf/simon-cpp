#pragma once
#include "Window.hpp"
#include "Button.hpp"
#include <vector>

using namespace std;

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int BUTTON_SIZE = 200;
constexpr int MARGIN = 50;

enum class GameState {
	ShowingSequence,
	WaitingInput
};

class Game {
private:
	Window window;
	std::vector<Button> buttons;

	vector<int> sequence;
	int currentStep;

	int startX;
	int startY;

	GameState state;
	size_t sequenceIndex;
	sf::Clock timer;
	float flashDuration = 0.5f;
public:
	Game();
	void run();
	void reset();
	const vector<int>& getSequence() const;
	bool checkInput(int buttonId);
	void addRandomButton();

private:
	void setupButtons();
	void handlePlayerClick(const sf::Vector2f& mousePos);

	void processEvents();
	void update();
	void render();
};