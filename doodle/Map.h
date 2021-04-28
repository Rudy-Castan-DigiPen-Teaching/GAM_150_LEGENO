#pragma once
#include<vector>
#include"vec2.h"
#include "ENUM.h"
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
	int block_size = 30;
public:
	vector<info> map;
	void setup();
	void draw();
};
