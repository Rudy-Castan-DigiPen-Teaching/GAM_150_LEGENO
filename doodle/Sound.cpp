#include "Sound.h"
#include "doodle/doodle.hpp"

using namespace doodle;

[[noreturn]] void error(const std::string& s) { throw std::runtime_error(s); }

void Sound::SetUpSound()
{
    LoadSound("assets/Siren.ogg");
}

void Sound::SetMusic(const std::string& file_path, bool isLoop)
{
    if (!music.openFromFile(file_path))
    {
        throw std::runtime_error("Failed to load the music file: " + file_path);
    }
    music.setLoop(isLoop);
}

void Sound::LoadSound(const std::string& file_path)
{
    SoundBuffers.emplace_back();
    sf::SoundBuffer& buffer = SoundBuffers.back();
    if (!buffer.loadFromFile(file_path))
    {
        error("Failed to load " + file_path);
    }
}

void Sound::PlaySound(int soundType)
{
    for (auto& sound : Sounds)
    {
        if (sound.getStatus() != sf::SoundSource::Playing)
        {
            sound.setBuffer(SoundBuffers[soundType]);
            sound.play();
            return;
        }
    }
    Sounds.emplace_back(SoundBuffers[soundType]);
    Sounds.back().play();
}
