/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include "Sound.h"
#include "ENUM.H"

[[noreturn]] void error(const std::string& s) { throw std::runtime_error(s); }

void Sound::Set_up_sound()
{
    Load_sound("assets/Bite.ogg");
    Load_sound("assets/BombFuse.ogg");
    Load_sound("assets/ChewingGum.ogg");
    Load_sound("assets/CrashWall.ogg");
    Load_sound("assets/Explosion.ogg");
    Load_sound("assets/FootStep.ogg");
    Load_sound("assets/GetTreasure.ogg");
    Load_sound("assets/Meow.ogg");
    Load_sound("assets/PutItem.ogg");
    Load_sound("assets/Radar.ogg");
    Load_sound("assets/SelectEffect.ogg");
    Load_sound("assets/SelectLimitEffect.ogg");
    Load_sound("assets/TimerTic.ogg");
    Load_sound("assets/TimesUp.ogg");
    Load_sound("assets/Win.ogg");
    Set_sound();
}

void Sound::Set_music(const std::string& file_path, bool isLoop)
{
    if (!music.openFromFile(file_path) == true)
    {
        throw std::runtime_error("Failed to load the music file: " + file_path);
    }
    music.setLoop(isLoop);
}

void Sound::Load_sound(const std::string& file_path)
{
    soundBuffers.emplace_back();
    sf::SoundBuffer& buffer = soundBuffers.back();
    if (!buffer.loadFromFile(file_path) == true)
    {
        error("Failed to load " + file_path);
    }
}

void Sound::Set_sound()
{
    for (int i = 0; i < static_cast<int>(SoundType::COUNT); i++)
    {
        sounds.emplace_back(soundBuffers[i]);
    }
}

void Sound::Play_sound(int soundType)
{
     sounds[soundType].setBuffer(soundBuffers[soundType]);
     sounds[soundType].play();
}

bool Sound::Is_sound_playing(const int soundType)
{
    return sounds[soundType].getStatus() == sf::SoundSource::Playing;
}

void Sound::Stop_sound()
{
    for (auto& sound : sounds)
    {
        if (sound.getStatus() == sf::SoundSource::Playing)
        {
            sound.stop();
            return;
        }
    }
}