#pragma once

#include <SFML/Audio.hpp>
#include <vector>

struct Sound
{
public:
     void SetUpSound();
    void SetMusic(const std::string& file_path, bool isLoop);
    void LoadSound(const std::string& file_path);
    void PlaySound(const int soundType);

    std::vector<sf::SoundBuffer> SoundBuffers{};
    std::vector<sf::Sound>       Sounds{};
    sf::Music                    music;
};

