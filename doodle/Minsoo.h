#pragma once
#include"vec2.h"
#include"Map.h"
#include"doodle/doodle.hpp"
#include"Map.h"

class Minsoo:Map
{
public:
	void Draw_minsu();
	void set_position(doodle::KeyboardButtons button);
	void check_collision(math::vec2 position);
private:
	math::vec2 position{ 20*3 + 15,20*3 + 15};
};


class Guard :Map
{
public:
	void Draw_guard();


};