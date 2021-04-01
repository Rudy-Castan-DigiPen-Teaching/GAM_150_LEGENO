#pragma once
#include<vector>
#include"vec2.h"
using namespace std;

enum Type
{
	wall,
	road
};
struct info
{
	math::vec2 position;
	Type type;
};


class Map
{
protected:
	vector<info> map;
	double map_width = 32;
	double map_height = 22;
	double block_size = 30;
public:
	void setup();
	void draw();
};
