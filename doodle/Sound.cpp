/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include "Sound.h"

[[noreturn]] void error(const std::string& s) { throw std::runtime_error(s); }

void Sound::SetUpSound()
{
    LoadSound("assets/Bite.ogg");
    LoadSound("assets/BombFuse.ogg");
    LoadSound("assets/ChewingGum.ogg");
    LoadSound("assets/CrashWall.ogg");
    LoadSound("assets/ETC.ogg");
    LoadSound("assets/Explosion.ogg");
    LoadSound("assets/FootStep.ogg");
    LoadSound("assets/GetTreasure.ogg");
    LoadSound("assets/Meow.ogg");
    LoadSound("assets/PutItem.ogg");
    LoadSound("assets/Radar.ogg");
    LoadSound("assets/RubyAppear.ogg");
    LoadSound("assets/SelectEffect.ogg");
    LoadSound("assets/SelectLimitEffect.ogg");
    LoadSound("assets/TimerTic.ogg");
    LoadSound("assets/TimesUp.ogg");
    LoadSound("assets/Win.ogg");
}

void Sound::SetMusic(const std::string& file_path, bool isLoop)
{
    if (!music.openFromFile(file_path) == true)
    {
        throw std::runtime_error("Failed to load the music file: " + file_path);
    }
    music.setLoop(isLoop);
}

void Sound::LoadSound(const std::string& file_path)
{
    soundBuffers.emplace_back();
    sf::SoundBuffer& buffer = soundBuffers.back();
    if (!buffer.loadFromFile(file_path) == true)
    {
        error("Failed to load " + file_path);
    }
}

void Sound::PlaySound(int soundType)
{
    for (auto& sound : sounds)
    {
        if (sound.getStatus() != sf::SoundSource::Playing)
        {
            sound.setBuffer(soundBuffers[soundType]);
            sound.play();
            return;
        }
    }
    sounds.emplace_back(soundBuffers[soundType]);
    sounds.back().play();
}
