#pragma once
#include <SFML/System/Clock.hpp>

class IntroAnimation {
private:
	const int sequence1[4] = { 0, 1, 3, 2 };
	const int sequence2[4] = { 0, 2, 1, 3 };
	const int sequence3[4] = { 0, 3, 1, 2 };
	const int* currentSequence;
	int currentIndex = 0;
	int cycleCount = 0;
	bool flashOn = false;
	sf::Clock timer;
	float flashDuration;
	float pauseDuration;
	int totalCycles;

public:
	IntroAnimation(float flash = 0.15f, float pause = 0.15f, int cycles = 2)
		: flashDuration(flash), pauseDuration(pause), totalCycles(cycles) { }

	void reset() {
		currentIndex = 0;
		cycleCount = 0;
		flashOn = false;

		int choice = rand() % 3;
		if (choice == 0) {
			currentSequence = sequence1;
		}
		else if (choice == 1) {
			currentSequence = sequence2;
		}
		else {
			currentSequence = sequence3;
		}

		timer.restart();
	}


	template<typename ButtonContainer, typename AudioCallback>
	bool update(ButtonContainer& buttons, AudioCallback playSound) {
		if (cycleCount >= totalCycles) {
			return true;
		}

		int currentButton = currentSequence[currentIndex];
		float elapsed = timer.getElapsedTime().asSeconds();

		if (!flashOn) {
			buttons[currentButton].flash();
			playSound(currentButton);
			flashOn = true;
			timer.restart();
		}
		else if (elapsed >= flashDuration && elapsed < flashDuration + pauseDuration) {
			if (elapsed >= flashDuration && elapsed < flashDuration + 0.01f) {
				buttons[currentButton].resetColor();
			}
		}
		else if (elapsed >= flashDuration + pauseDuration) {
			flashOn = false;
			currentIndex++;

			if (currentIndex >= 4) {
				currentIndex = 0;
				cycleCount++;
			}

			timer.restart();
		}

		return false;
	}

	bool isComplete() const {
		return cycleCount >= totalCycles;
	}
};