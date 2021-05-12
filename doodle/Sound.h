#pragma once

#include <SFML/Audio.hpp>

struct Sound
{
public:
    std::vector<sf::SoundBuffer> SoundBuffers{};
    std::vector<sf::Sound>       Sounds{};
    void LoadSound(const std::string& file_path);
    void PlaySound(int index);
    void setup();
};

enum sounds
{
    //ItemSound, ThumpSound, ZoomSound, TPSound, SwitchSound
};

