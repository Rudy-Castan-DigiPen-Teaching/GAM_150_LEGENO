#pragma once
#include"vec2.h"
#include"Map.h"
#include"doodle/doodle.hpp"
#include"Map.h"


class Guard :Map
{
public:
	void setup();
	void Draw_guard();
	vector<math::ivec2> guards;
	void move(int index, int direction);

};