#pragma once
#include <SFML/System/Clock.hpp>
#include <vector>

class SequencePlayer {
private:
	size_t index = 0;
	bool flashOn = false;
	sf::Clock timer;
	float flashDuration;
	float pauseBetweenButtons;

public:
	SequencePlayer(float flash = 0.1f, float pause = 0.5f)
		: flashDuration(flash), pauseBetweenButtons(pause) { }

	void reset() {
		index = 0;
		flashOn = false;
		timer.restart();
	}

	template<typename ButtonContainer, typename AudioCallback>
	bool update(const std::vector<int>& sequence, ButtonContainer& buttons, AudioCallback playSound) {
		if (index >= sequence.size()) {
			return true;
		}

		int btnId = sequence[index];
		float elapsed = timer.getElapsedTime().asSeconds();

		if (!flashOn) {
			buttons[btnId].flash();
			playSound(btnId);
			flashOn = true;
			timer.restart();
		}
		else if (elapsed >= flashDuration && elapsed < flashDuration + pauseBetweenButtons) {
			if (elapsed >= flashDuration && elapsed < flashDuration + 0.01f) {
				buttons[btnId].resetColor();
			}
		}
		else if (elapsed >= flashDuration + pauseBetweenButtons) {
			flashOn = false;
			index++;
			timer.restart();
		}

		return false;
	}
};