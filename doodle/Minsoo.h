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
	bool check_collision(math::vec2 position);
	math::vec2 GetPosition();
private:
	math::vec2 position{ 2.5,2.5 };
	int movement{ 0 };
};