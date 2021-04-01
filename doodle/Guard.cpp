#include "Map.h"
#include <fstream>
#include "doodle/doodle.hpp"
#include "Guard.h"


void Guard::setup()
{
	guards.push_back(math::vec2(130, 100));
	guards.push_back(math::vec2(230, 150));
	guards.push_back(math::vec2(280, 140));
	guards.push_back(math::vec2(340, 200));
	guards.push_back(math::vec2(530, 100));
	guards.push_back(math::vec2(700, 100));
	guards.push_back(math::vec2(130, 400));
	guards.push_back(math::vec2(230, 370));
	guards.push_back(math::vec2(280, 370));
	guards.push_back(math::vec2(340, 400));
	guards.push_back(math::vec2(530, 400));
	guards.push_back(math::vec2(700, 370));
}

void Guard::Draw_guard()
{
	doodle::set_fill_color(255, 0, 0);
	for (auto p : guards)
	{
		doodle::draw_ellipse(p.x, p.y, 20);
	}


}