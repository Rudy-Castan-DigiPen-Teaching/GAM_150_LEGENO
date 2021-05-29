/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
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
	int map_width{ 43 };
	int map_height{ 25 };

public:
	void Set_up(int level);
	void Draw(Camera& camera);
	vector<info> map;
};
