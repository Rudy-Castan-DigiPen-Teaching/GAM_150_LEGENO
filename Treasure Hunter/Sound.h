/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Sound.h
Project: GAM150
Author:Hyungwon An
-----------------------------------------------------------------*/
#pragma once

#include <SFML/Audio.hpp> // sounds and music stuffs
#include <vector>   // std::vector

struct Sound
{
public:
    void Set_up_sound();
    void Set_music(const std::string& file_path, bool isLoop);
    void Load_sound(const std::string& file_path);
    void Set_sound(void);
    void Play_sound(const int soundType);
    bool Is_sound_playing(const int soundType);
    void Stop_sound();

    std::vector<sf::SoundBuffer> soundBuffers{};
    std::vector<sf::Sound>       sounds{};
    sf::Music                    music;
};

