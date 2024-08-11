#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SDL_mixer.h>
#include <string>
#include <map>

class AudioManager {
public:
    // Constructor and Destructor
    AudioManager();
    ~AudioManager();

    // Initialize SDL_mixer
    bool init();

    // Load sound effect
    bool loadSoundEffect(const std::string& id, const std::string& path);

    // Load music
    bool loadMusic(const std::string& id, const std::string& path);

    // Play sound effect
    void playSoundEffect(const std::string& id, int loops = 0);

    // Play music
    void playMusic(const std::string& id, int loops = -1);

    // Stop music
    void stopMusic();

    void stopSoundEffect();

    // Free all loaded sounds and music
    void cleanUp();

private:
    std::map<std::string, Mix_Chunk*> soundEffects;
    std::map<std::string, Mix_Music*> music;
};

#endif
