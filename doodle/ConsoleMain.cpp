#include "Sketch.h"
#include <doodle/window.hpp>
#include <exception>
#include <iostream>

int main(void)
try
{
    Sketch sketch;
    sketch.setup();
    while (!doodle::is_window_closed())
    {
        doodle::update_window();
        sketch.draw();
    }
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << "\n";
    return -1;
}
