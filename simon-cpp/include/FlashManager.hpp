#pragma once
#include <SFML/System/Clock.hpp>
#include <vector>

struct Flash {
	int buttonId;
	sf::Clock timer;
};

class FlashManager {
private:
	std::vector<Flash> activeFlashes;
	float duration;

public:
	FlashManager(float flashDuration = 0.1f) : duration(flashDuration) {}

	void add(int buttonId) {
		activeFlashes.push_back({ buttonId, sf::Clock() });
	}

	template<typename ButtonContainer>

	void update(ButtonContainer& buttons) {
		for (auto it = activeFlashes.begin(); it != activeFlashes.end();) {
			if (it->timer.getElapsedTime().asSeconds() < duration) {
				buttons[it->buttonId].flash();
				++it;
			}
			else {
				buttons[it->buttonId].resetColor();
				it = activeFlashes.erase(it);
			}
		}
	}
};