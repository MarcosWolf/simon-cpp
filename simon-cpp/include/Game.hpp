#pragma once
#include "Window.hpp"
#include "Button.hpp"
#include <vector>

using namespace std;

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int BUTTON_SIZE = 200;
constexpr int MARGIN = 50;

class Game {
private:
	Window window;
	std::vector<Button> buttons;

	vector<int> sequence;
	int currentStep;

	int startX;
	int startY;

	void setupButtons();
public:
	Game();
	void run();
	void reset();
	const vector<int>& getSequence() const;
	bool checkInput(int buttonId);
	void addRandomButton();

private:
	void processEvents();
	void update();
	void render();
};