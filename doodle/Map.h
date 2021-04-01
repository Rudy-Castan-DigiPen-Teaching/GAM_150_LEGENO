#pragma once
#include<vector>
#include"vec2.h"
using namespace std;

enum class Type
{
	wall,
	road,
	radar,
	exit
};
struct info
{
	math::ivec2 position;
	Type type;
};


class Map
{
protected:
	int map_width = 32;
	int map_height = 22;
	int block_size = 30;
public:
	vector<info> map;
	void setup();
	void draw();
};
