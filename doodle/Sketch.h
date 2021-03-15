#pragma once
#include <SFML/Audio.hpp>
#include <vector>

class Sketch
{
public:
    struct Ball
    {
        double x{0}, y{0}, xSpeed{0}, ySpeed{0};
    };

public:
    void setup();
    void draw();

private:
    constexpr static float       RADIUS{30.0};
    std::vector<sf::SoundBuffer> SoundBuffers{};
    std::vector<sf::Sound>       Sounds{};
    sf::Music                    music;
    std::vector<Ball>            balls;

private:
    void DrawAndUpdateBall(Ball& ball);
    void LoadSound(const std::string& file_path);
    void PlaySound();
};
