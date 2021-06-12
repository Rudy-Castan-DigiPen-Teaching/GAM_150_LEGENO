/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Guard.h
Project: GAM150
Author:Hyosang Jung
-----------------------------------------------------------------*/
#pragma once
#include"vec2.h"// vec2 struct
#include"Map.h"	// Map class
#include"doodle/doodle.hpp"	// doodle image & functions 
#include "Camera.h"	// Camera class
#include "Minsoo.h"	// Minsoo class
struct sight_info
{
	math::vec2 Position;
	bool Is_valid = true;  // if there a wall in front of their sight
};

struct guard_info
{
	math::vec2 Position;
	Direction Direction{ Direction::UP };
	const string Guard_type{ "guard" };
	math::vec2 Target_pos = Position;
	bool is_okay{ true };  //If guard eat dog chew
	bool is_trace{ false }; //Whether tracing or not
	int Trace_movement{ 0 };
	int Movement{ 0 };
	sight_info Sight_position[3]{ 0, true };
};

class Guard : Map
{
public:
	void Set_up(int level);
	void Draw_guard(Camera& camera);
	void Draw_sight(Camera& camera, Map MAP);
	void Set_position(int index);              
	void Change_sight(Map m, int index);
	void Guard_movement_update(math::ivec2 exit_pos, Map& m, int movement);
	void Set_sight();           
	void Tracing_check(Minsoo minsoo); // when minsoo is in guard sight, return what number of guard it is.		
	bool Is_trace_sommeone(); // check if there is a guard chasing minsoo                                   
	void Update_position();
	void Check_watching_wall(Map m);
	vector<guard_info> Guards;

private:
	const int Sight_size{ 3 };  //sight size
	const int How_many_trace{ 5 };// how many guard trace minsoo 
	const int How_many_craze{ 3 };//how long guard eat dog chew
	int How_many_guards_tracing{ 0 };

	doodle::Image Guard_UP_image{ "assets/GuardUp.png" };
	doodle::Image Guard_Down_image{ "assets/GuardDown.png" };
	doodle::Image Guard_Right_image{ "assets/GuardRight.png" };
	doodle::Image Guard_Left_image{ "assets/GuardLeft.png" };
	doodle::Image Guard_CHEW_image{ "assets/Chew_dog.png" }; 
	doodle::Image Ruby_CHEW_image{ "assets/Chew_ruby.png" }; 

	doodle::Image Guard_tracing_image{ "assets/Tracing_dog.png" };
	doodle::Image Ruby_image{ "assets/Ruby.png" };

	doodle::Image Sight1_up_image{ "assets/Sight1_up.png" };
	doodle::Image Sight2_up_image{ "assets/Sight2_up.png" };
	doodle::Image Sight3_up_image{ "assets/Sight3_up.png" };

	doodle::Image Sight1_down_image{ "assets/Sight1_down.png" };
	doodle::Image Sight2_down_image{ "assets/Sight2_down.png" };
	doodle::Image Sight3_down_image{ "assets/Sight3_down.png" };

	doodle::Image Sight1_right_image{ "assets/Sight1_right.png" };
	doodle::Image Sight2_right_image{ "assets/Sight2_right.png" };
	doodle::Image Sight3_right_image{ "assets/Sight3_right.png" };

	doodle::Image Sight1_left_image{ "assets/Sight1_left.png" };
	doodle::Image Sight2_left_image{ "assets/Sight2_left.png" };
	doodle::Image Sight3_left_image{ "assets/Sight3_left.png" };
};