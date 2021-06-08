/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
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
    void StopSound(void);
    bool IsSoundPlaying(void);

    std::vector<sf::SoundBuffer> soundBuffers{};
    std::vector<sf::Sound>       sounds{};
    sf::Music                    music;
};

