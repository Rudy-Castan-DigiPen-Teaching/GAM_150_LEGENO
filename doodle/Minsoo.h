#pragma once
#include"vec2.h"
#include"Map.h"
#include"doodle/doodle.hpp"
#include"Map.h"

class Minsoo: public Map
{
public:
	void Draw_minsu();
	void set_position(doodle::KeyboardButtons button);
	math::vec2 GetPosition();
	void setup();
	int movement{ 0 };
	doodle::Image Minsoo_left{ "assets/Minsoo_left.png" };
private:
	math::vec2 position{ 2,2 };
};