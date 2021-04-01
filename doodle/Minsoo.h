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
	math::ivec2 GetPosition();
	void setup();
private:
	math::ivec2 position{ 2,2 };
	int movement{ 0 };
};