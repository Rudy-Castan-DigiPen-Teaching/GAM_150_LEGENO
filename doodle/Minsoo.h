#pragma once
#include"vec2.h"
#include"Map.h"
#include"doodle/doodle.hpp"
#include"Map.h"

class Minsoo: public Map
{
public:
	void Draw_minsu(Camera camera);
	void set_position(doodle::KeyboardButtons button);
	math::vec2 GetPosition();
	void setup();
	int movement{ 0 };
	doodle::Image Minsoo_left{ "assets/Minsoo_left.png" };
	doodle::Image Minsoo_right{ "assets/Minsoo_right.png" };
	doodle::Image Minsoo_Up{ "assets/Minsoo_up.png" };
	doodle::Image Minsoo_Down{ "assets/Minsoo_down.png" };
private:
	math::vec2 position{ 2,2 };
	Direction direction = Direction::DOWN;
	int chew_item = 3;
};