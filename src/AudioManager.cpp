#include "AudioManager.hpp"
#include <iostream>

// Constructor
AudioManager::AudioManager() {}

// Destructor
AudioManager::~AudioManager() {
    cleanUp();
}

// Initialize SDL_mixer
bool AudioManager::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

// Load sound effect
bool AudioManager::loadSoundEffect(const std::string& id, const std::string& path) {
    Mix_Chunk* soundEffect = Mix_LoadWAV(path.c_str());
    if (soundEffect == nullptr) {
        std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    soundEffects[id] = soundEffect;
    return true;
}

// Load music
bool AudioManager::loadMusic(const std::string& id, const std::string& path) {
    Mix_Music* musicTrack = Mix_LoadMUS(path.c_str());
    if (musicTrack == nullptr) {
        std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    music[id] = musicTrack;
    return true;
}

// Play sound effect
void AudioManager::playSoundEffect(const std::string& id, int loops) {
    auto it = soundEffects.find(id);
    if (it != soundEffects.end()) {
        Mix_PlayChannel(-1, it->second, loops);
    } else {
        std::cout << "Sound effect with ID " << id << " not found!" << std::endl;
    }
}

// Play music
void AudioManager::playMusic(const std::string& id, int loops) {
    auto it = music.find(id);
    if (it != music.end()) {
        Mix_PlayMusic(it->second, loops);
    } else {
        std::cout << "Music with ID " << id << " not found!" << std::endl;
    }
}

// Stop music
void AudioManager::stopMusic() {
    Mix_HaltMusic();
}

void AudioManager::stopSoundEffect() {
    Mix_HaltChannel(-1);
}

// Free all loaded sounds and music
void AudioManager::cleanUp() {
    for (auto& pair : soundEffects) {
        Mix_FreeChunk(pair.second);
    }
    soundEffects.clear();

    for (auto& pair : music) {
        Mix_FreeMusic(pair.second);
    }
    music.clear();

    Mix_Quit();
}
