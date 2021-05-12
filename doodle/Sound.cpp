#include "Sound.h"
void Sound::PlaySound(int index)
{
    for (auto& sound : Sounds)
    {
        if (sound.getStatus() != sf::SoundSource::Playing)
        {
            sound.setBuffer(SoundBuffers[index]);
            sound.play();
            return;
        }
    }
    Sounds.emplace_back(SoundBuffers[index]);
    Sounds.back().play();
}

void Sound::LoadSound(const std::string& file_path)
{
    SoundBuffers.emplace_back();
    sf::SoundBuffer& buffer = SoundBuffers.back();
    if (!buffer.loadFromFile(file_path))
    {
        throw std::runtime_error("failed to load " + file_path);
    }
}

void Sound::setup()
{
    //LoadSound("assets/item.wav");
    //LoadSound("assets/thump.wav");
    //LoadSound("assets/zoom.wav");
    //LoadSound("assets/teleport.wav");
    //LoadSound("assets/switch.wav");
}