#include "Map.h"
#include <fstream>
#include "doodle/doodle.hpp"
#include "Guard.h"


void Guard::setup()
{
	guards.clear();
	//guards.push_back(math::ivec2(4, 4));
	//guards.push_back(math::ivec2(9, 4));
	//guards.push_back(math::ivec2(15, 4));
	//guards.push_back(math::ivec2(6, 8));
	//guards.push_back(math::ivec2(11,8));
	//guards.push_back(math::ivec2(14, 8));
	//guards.push_back(math::ivec2(4, 15));
	//guards.push_back(math::ivec2(7, 16));
	//guards.push_back(math::ivec2(15, 17));
	//guards.push_back(math::ivec2(20, 9));
	//guards.push_back(math::ivec2(25, 9));
	//guards.push_back(math::ivec2(26, 11));
}

void Guard::Draw_guard()
{
	doodle::set_fill_color(255, 0, 0);
	for (auto p : guards)
	{
		doodle::draw_ellipse((p.x + 0.5) * 30  , (p.y + 0.5 ) * 30 , 20);
	}
}

void Guard::move(int index, int direction)
{
	switch (direction)
	{
	case 1:   //move up
		guards[index].y--;
		break;
	case 2:   //move down
		guards[index].y++;
		break;
	case 3:   //move right
		guards[index].x++;
		break;
	case 4:   //move left
		guards[index].x--;
		break;
	}
}