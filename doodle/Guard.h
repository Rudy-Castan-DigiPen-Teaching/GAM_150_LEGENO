#pragma once
#include"vec2.h"
#include"Map.h"
#include"doodle/doodle.hpp"

struct guard_info
{
	math::ivec2 position;
	Direction direction = Direction::UP;
};
class Guard :Map
{
public:
	void setup();
	void Draw_guard();
	void Draw_Sight();
	vector<guard_info> guards;
	void move(int index);
	void change_sight(Map m, int index);
};