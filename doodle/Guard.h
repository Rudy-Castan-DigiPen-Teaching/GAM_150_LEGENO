#pragma once
#include"vec2.h"
#include"Map.h"
#include"doodle/doodle.hpp"
#include "Camera.h"
struct guard_info
{
	math::ivec2 position;
	Direction direction = Direction::UP;
	bool is_okay = true;
	int movement = 0;
};
class Guard :Map
{
public:
	void setup();
	void Draw_guard(Camera& camera);
	void Draw_Sight(Camera& camera);
	vector<guard_info> guards;
	void move(int index);
	void change_sight(Map m, int index);
	void get_dogchew(Map& m,int movement);
	doodle::Image Guard_image{ "assets/Guard.png" };
};