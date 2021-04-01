#include "Sketch.h"
#include <doodle/window.hpp>
#include <exception>
#include <iostream>
#include "Map.h"
#include "Minsoo.h"
#include "doodle/doodle.hpp"
#include"Game.h"


Game game;
int main(void)
try
{
    doodle::create_window(800, 600);
    doodle::set_frame_of_reference(doodle::FrameOfReference::LeftHanded_OriginTopLeft);
    game.setup();
    while (!doodle::is_window_closed())
    {
        doodle::update_window();
        game.Draw();
    }
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << "\n";
    return -1;
}
void on_key_pressed(doodle::KeyboardButtons doodleButton)
{
    if (doodleButton == doodle::KeyboardButtons::S)
    {
       game.set_position(doodleButton);
    }
    if (doodleButton == doodle::KeyboardButtons::W)
    {
        game.set_position(doodleButton);
    }
    if (doodleButton == doodle::KeyboardButtons::D)
    {
        game.set_position(doodleButton);
    }
    if (doodleButton == doodle::KeyboardButtons::A)
    {
        game.set_position(doodleButton);
    }

}