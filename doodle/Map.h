#pragma once
#include<vector>	// std::vector
#include"vec2.h"	// vec2 struct
#include "ENUM.h"	// enum classes
#include "Camera.h"	// Camera class
#include"doodle/doodle.hpp" // doodle image & draw functions 
using namespace std;

struct info
{
	math::ivec2 position{ 0,0 };
	Type type{ Type::WALL };
};


class Map
{
protected:
	int block_size{ 100 };
public:
	doodle::Image Dog_chew{ "assets/Dog_chew.png" };
	doodle::Image Road{ "assets/Road.png" };
	doodle::Image Wall{ "assets/Wall.png" };
	doodle::Image Bomb{ "assets/Bomb.png" };
	doodle::Image Breakable_wall{ "assets/Breakable_wall.png" };
	doodle::Image Radar{ "assets/Radar.png" };
	int map_width{ 81 };
	int map_height{ 27 };

public:
	void Set_up();
	void Draw(Camera& camera);
	vector<info> map;
};
