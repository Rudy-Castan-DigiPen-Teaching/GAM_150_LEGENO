#pragma once
#include<vector>
#include"vec2.h"
#include "ENUM.h"
#include "Camera.h"
#include"doodle/doodle.hpp"
using namespace std;

struct info
{
	math::ivec2 position;
	Type type;
};


class Map
{
protected:
	int block_size = 100;
public:
	doodle::Image Dog_chew{"assets/dog_chew.png"};
	doodle::Image Road{ "assets/Road.png" };

	doodle::Image Bomb{ "assets/Bomb.png" };
	doodle::Image Breakable_wall{ "assets/Breakable_wall.png" };
	doodle::Image Radar{ "assets/Radar.png" };
	int map_width = 81;
	int map_height = 27;

public:

	vector<info> map;
	void setup();
	void draw(Camera& camera);
};
