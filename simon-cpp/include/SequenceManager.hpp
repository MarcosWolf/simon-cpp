#pragma once
#include <vector>

class SequenceManager {
private:
	std::vector<int> sequence;
	size_t currentStep = 0;

public:
	void addRandom() {
		sequence.push_back(rand() % 4);
	}

	bool checkStep(int buttonId) {
		if (sequence[currentStep] == buttonId) {
			currentStep++;
			return true;
		}

		return false;
	}

	bool isSequenceComplete() const {
		return currentStep >= sequence.size();
	}

	void resetStep() {
		currentStep = 0;
	}

	void clear() {
		sequence.clear();
		currentStep = 0;
	}

	const std::vector<int>& getSequence() const {
		return sequence;
	}

	size_t size() const {
		return sequence.size();
	}
};