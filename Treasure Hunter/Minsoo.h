/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#pragma once
#include"vec2.h"	//	vec2 struct
#include"Map.h"		// Map class
#include"doodle/doodle.hpp"	// doodle image & Draw functions 
#include"Sprite.h"
class Minsoo: public Map
{
public:
	void Draw_minsu(Camera camera, bool camera_move);
	void Set_position(doodle::KeyboardButtons button);
	void Update_position(bool& is_move);
	math::vec2 Get_position();
	void Set_up();

	bool is_dead{ false };
	int movement{ 0 };
	int chew_item{ 3 };
	int bomb_item{ 1 };
	int explode_count{ -1 };
	Direction direction{ Direction::DOWN };
	math::vec2 target_pos;

	Sprite Minsoo_left  { "assets/Minsoo_left.png",5 ,0.05};
	Sprite Minsoo_Up	{ "assets/Minsoo_up.png",5 ,0.05 };
	Sprite Minsoo_right { "assets/Minsoo_right.png",5 ,0.05 };
	Sprite Minsoo_Down  { "assets/Minsoo_down.png",5 ,0.05 };
private:
	math::vec2 position{ 2,2 };
};