#include "Sound.h"

[[noreturn]] void error(const std::string& s) { throw std::runtime_error(s); }

void Sound::SetUpSound()
{
    //LoadSound("assets/Siren.ogg");
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
