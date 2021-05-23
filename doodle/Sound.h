#pragma once

#include <SFML/Audio.hpp> // sounds and music stuffs
#include <vector>   // std::vector

struct Sound
{
public:
     void SetUpSound();
    void SetMusic(const std::string& file_path, bool isLoop);
    void LoadSound(const std::string& file_path);
    void PlaySound(const int soundType);

    std::vector<sf::SoundBuffer> soundBuffers{};
    std::vector<sf::Sound>       sounds{};
    sf::Music                    music;
};

