#pragma once
#include"vec2.h"	//	vec2 struct
#include"Map.h"		// Map class
#include"doodle/doodle.hpp"	// doodle image & Draw functions 

class Minsoo: public Map
{
public:
	void Draw_minsu(Camera camera, bool camera_move);
	void Set_position(doodle::KeyboardButtons button);
	void Update_position(bool& is_move);
	math::vec2 Get_position();
	void Set_up();

	int movement{ 0 };
	int chew_item{ 3 };
	int bomb_item{ 1 };
	int explode_count{ -1 };
	Direction direction{ Direction::DOWN };
	doodle::Image Minsoo_left{ "assets/Minsoo_left.png" };
	doodle::Image Minsoo_right{ "assets/Minsoo_right.png" };
	doodle::Image Minsoo_Up{ "assets/Minsoo_up.png" };
	doodle::Image Minsoo_Down{ "assets/Minsoo_down.png" };
private:
	math::vec2 position{ 2,2 };
	math::vec2 target_pos;
};