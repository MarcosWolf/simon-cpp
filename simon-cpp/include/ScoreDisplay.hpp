#pragma once
#include <iostream>
#include <iomanip>
#include <string>

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

enum class ActionMessage {
	YourTurn,
	Wait,
	GameOver
};

class ScoreDisplay {
private:
	int score = 0;
	int hiScore = 0;
	int combo = 0;
	ActionMessage currentMessage = ActionMessage::Wait;

	void clearScreen() {
		system(CLEAR_SCREEN);
	}

	void printHeader() {
		std::cout << "simon-cpp v0.1" << std::endl;
		std::cout << "Developed by: Marcos Vinicios do Carmo Ramos" << std::endl;
		std::cout << "Github: https://github.com/marcoswolf" << std::endl;
		std::cout << "Linkedin: https://linkedin.com/in/marcoswolf" << std::endl;
		std::cout << "Game developed for study purposes. Hope you enjoy it!" << std::endl;
		std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;
	}

	void printScores() {
		std::cout << "Hi-Score: " << std::setfill('0') << std::setw(10) << hiScore << std::endl << std::endl;
		std::cout << "SCORE: " << std::setfill('0') << std::setw(10) << score << std::endl << std::endl;
		std::cout << "Combo: " << combo << std::endl;
		std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;
	}

	void printAction(ActionMessage message) {
		switch (message) {
		case ActionMessage::Wait:
			std::cout << "Wait" << std::endl;
			break;
		case ActionMessage::YourTurn:
			std::cout << "Your turn" << std::endl;
			break;
		case ActionMessage::GameOver:
			std::cout << "GAME OVER" << std::endl;
			std::cout << "Better luck next time!" << std::endl;
			break;
		}
		
	}

public:
	void updateScore(int points) {
		score += points;
		if (score > hiScore) {
			hiScore = score;
		}
	}

	void updateCombo() {
		combo++;
	}


	void resetScore() {
		score = 0;
		combo = 0;
	}

	void setActionMessage(ActionMessage message) {
		currentMessage = message;
	}

	void display() {
		clearScreen();
		printHeader();
		printScores();
		printAction(currentMessage);
	}

	int getScore() const { return score; }
	int getHiScore() const { return hiScore; }
};