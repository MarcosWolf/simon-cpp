#pragma once
#include "Window.hpp"
#include "Button.hpp"
#include <vector>

class Game {
private:
	Window window;
	std::vector<Button> buttons;

public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();
};