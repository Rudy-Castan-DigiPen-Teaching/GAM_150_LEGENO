#include "Sketch.h"
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
#include <doodle/input.hpp>
#include <doodle/random.hpp>
#include <doodle/window.hpp>

using namespace doodle;

[[noreturn]] void error(const std::string& s) { throw std::runtime_error(s); }

void on_key_released(KeyboardButtons button)
{
    if (button == KeyboardButtons::Escape)
        close_window();
}

void Sketch::Set_up()
{
    if (!music.openFromFile("assets/orchestral.ogg"))
    {
        error("Failed to load the music file: assets/orchestral.ogg");
    }

    Load_Sound("assets/Tambores_1.ogg");
    Load_Sound("assets/Tambores_2.ogg");
    Load_Sound("assets/Tambores_3.ogg");

    music.setLoop(true);
    music.play();

    create_window();

    balls = {{200.0, 80.0, 8.0, 9.0}, {70.0, 200.0, 10.0 / 8.0, 10.0}, {20.0, 50.0, 10.0, 10.0 / 8.0}};

    no_fill();
    set_outline_color(240, 230, 245);
    set_outline_width(7.0f);
    set_frame_of_reference(FrameOfReference::RightHanded_OriginBottomLeft);
}

void Sketch::Draw()
{
    clear_background(0);
    for (auto& ball : balls)
    {
        Draw_and_update_ball(ball);
    }
}

void Sketch::Draw_and_update_ball(Ball& ball)
{
    draw_ellipse(ball.x, ball.y, RADIUS * 2.0);
    ball.x += ball.xSpeed;
    ball.y += ball.ySpeed;
    if (ball.y + RADIUS > Height || ball.y < RADIUS)
    {
        ball.ySpeed *= -1;
        Play_Sound();
    }
    else if (ball.x + RADIUS > Width || ball.x < RADIUS)
    {
        ball.xSpeed *= -1;
        Play_Sound();
    }
}

void Sketch::Load_Sound(const std::string& file_path)
{
    SoundBuffers.emplace_back();
    sf::SoundBuffer& buffer = SoundBuffers.back();
    if (!buffer.loadFromFile(file_path))
    {
        error("Failed to load " + file_path);
    }
}

void Sketch::Play_Sound()
{
    int       buffer_index = 0;
    const int random_value = random(0, 100);
    if (random_value > 90)
        buffer_index = 2;
    else if (random_value >= 45)
        buffer_index = 1;
    for (auto& sound : Sounds)
    {
        if (sound.getStatus() != sf::SoundSource::Playing)
        {
            sound.setBuffer(SoundBuffers[buffer_index]);
            sound.play();
            return;
        }
    }
    Sounds.emplace_back(SoundBuffers[buffer_index]);
    Sounds.back().play();
}
