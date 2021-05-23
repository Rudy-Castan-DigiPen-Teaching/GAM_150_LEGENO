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
    doodle::create_window(1200,1200);
    doodle::set_frame_of_reference(doodle::FrameOfReference::LeftHanded_OriginTopLeft);
    game.Set_up();
    while (!doodle::is_window_closed())
    {
        doodle::update_window();
        game.Update();
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
        game.Get_inputkey(doodleButton);
        doodleButton = doodle::KeyboardButtons::None;
}

