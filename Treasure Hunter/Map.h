/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Collision.cpp
Project: GAM150
Author:Hyun Kang
-----------------------------------------------------------------*/
#pragma once
#include<vector>	// std::vector
#include"vec2.h"	// vec2 struct
#include "ENUM.h"	// enum classes
#include "Camera.h"	// Camera class
#include"doodle/doodle.hpp" // doodle image & draw functions 
#include"Sprite.h"
#define MAP_WIDTH 25
#define MAP_HEIGHT 43

using namespace std;
struct info
{
	math::ivec2 Position{ 0,0 };
	Type Type{ Type::WALL };
	int Random_num;
};


class Map
{

public:
	int Block_size{ 100 };
	doodle::Image Dog_chew{ "assets/Dog_chew.png" };
	doodle::Image Road1{ "assets/Road1.png" };
	doodle::Image Road2{ "assets/Road2.png" };
	doodle::Image Road3{ "assets/Road3.png" };
	doodle::Image Bomb{ "assets/Bomb.png" };
	doodle::Image Breakable_wall{ "assets/Breakable_wall.png" };
	doodle::Image Escape{ "assets/Escape.png" };
	doodle::Image Radar{ "assets/Radar.png" };
	doodle::Image Next{ "assets/Next.png" };
	doodle::Image Ladder{ "assets/Lader.png" };
	
	doodle::Image Treasure_1{ "assets/Treasure_1.png" };
	doodle::Image Treasure_2{ "assets/Treasure_2.png" };
	doodle::Image Treasure_3{ "assets/Treasure_3.png" };
	doodle::Image Treasure_4{ "assets/Treasure_4.png" };
	
	doodle::Image WallWall{ "assets/wallwall.png" };
	doodle::Image Wall_Side_Up{ "assets/Wall_Side_Up.png" };
	doodle::Image Wall_Side_Down{ "assets/Wall_Side_Down.png" };
	doodle::Image Wall_Side_Left{ "assets/Wall_Side_Left.png" };
	doodle::Image Wall_Side_Right{ "assets/Wall_Side_Right.png" };

	doodle::Image Wall_Edge_1{ "assets/Wall_Edge_1.png" };
	doodle::Image Wall_Edge_2{ "assets/Wall_Edge_2.png" };
	doodle::Image Wall_Edge_3{ "assets/Wall_Edge_3.png" };
	doodle::Image Wall_Edge_4{ "assets/Wall_Edge_4.png" };

	doodle::Image Wall_Corner_1{ "assets/Wall_Corner_1.png" };
	doodle::Image Wall_Corner_2{ "assets/Wall_Corner_2.png" };
	doodle::Image Wall_Corner_3{ "assets/Wall_Corner_3.png" };
	doodle::Image Wall_Corner_4{ "assets/Wall_Corner_4.png" };


	Sprite Explode{ "assets/hit.png",4,0.01 };

	int Map_width{ 43 };
	int Map_height{ 25 };
	double Bomb_target_time = 2;
public:
	void Set_up(int level);
	void Draw(Camera& camera);
	std::vector<info> map;
	doodle::Image& Set_wall(info& value);
	int Treasure_num = 4;

};



