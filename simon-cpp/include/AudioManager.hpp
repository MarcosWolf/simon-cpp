#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

using namespace std;

class AudioManager {
private:
	map<string, sf::SoundBuffer> buffers;
	map<string, sf::Sound> sounds;

public:
	AudioManager() = default;

	bool loadSound(const string& name, const string& filename) {
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(filename))
			return false;

		buffers[name] = buffer;
		sounds[name].setBuffer(buffers[name]);
		return true;
	}

	void play(const string& name) {
		if (sounds.find(name) != sounds.end()) {
			sounds[name].play();
		}
	}
};