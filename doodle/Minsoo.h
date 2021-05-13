#pragma once
#include"vec2.h"
#include"Map.h"
#include"doodle/doodle.hpp"

class Minsoo: public Map
{
public:
	void Draw_minsu(Camera camera);
	void set_position(doodle::KeyboardButtons button);
	math::ivec2 GetPosition();
	void setup();
	int movement{ 0 };
	int chew_item{ 3 };
	int bomb_item{ 1 };
	int explode_count{ -1 };
	doodle::Image Minsoo_left{ "assets/Minsoo_left.png" };
	doodle::Image Minsoo_right{ "assets/Minsoo_right.png" };
	doodle::Image Minsoo_Up{ "assets/Minsoo_up.png" };
	doodle::Image Minsoo_Down{ "assets/Minsoo_down.png" };
	Direction direction = Direction::DOWN;
private:
	math::ivec2 position{ 2,2 };

};