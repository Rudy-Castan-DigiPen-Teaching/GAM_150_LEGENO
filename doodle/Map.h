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
	int map_width = 81;
	int map_height = 27;
	int block_size = 100;
	doodle::Image Dog_chew{"assets/dog_chew.png"};

public:
	vector<info> map;
	void setup();
	void draw(Camera& camera);
};
