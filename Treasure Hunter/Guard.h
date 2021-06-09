/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#pragma once
#include"vec2.h"// vec2 struct
#include"Map.h"	// Map class
#include"doodle/doodle.hpp"	// doodle image & functions 
#include "Camera.h"	// Camera class
#include "Minsoo.h"	// Minsoo class
struct sight_info
{
	math::vec2 position;
	bool is_valid = true;  // 시야가 벽에 가려있나 안가려있나
};

struct guard_info
{
	math::vec2 position;
	Direction direction{ Direction::UP };
	const string guard_type{ "guard" };
	math::vec2 target_pos = position;
	bool is_okay{ true };  //개껌먹었는지 안먹었는지
	bool is_trace{ false }; //민수가 시야에 들어왔는지 안들어왔는지
	int trace_movement{ 0 };
	int movement{ 0 };
	sight_info sight_position[3]{ 0, true };
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
	void Tracing_check(Minsoo minsoo); // when minsoo is in guard sight, return what number of guard it is.가드 시야에 있을때 몇번째 인덱스 가드인지 리턴			
	bool Is_trace_sommeone(); // check if there is a guard chasing minsoo 따라오는새끼 하나라도있는지                                      
	void Update_position();
	void Check_watching_wall(Map m);
	vector<guard_info> guards;

private:
	const int sight_size{ 3 };  //시야 몇칸보이는지
	const int how_many_trace{ 5 };// 몇칸동안 따라오는지
	const int how_many_craze{ 3 };//얼마동안 개껌먹고 미쳐있는지
	int how_many_guards_tracing{ 0 };

	doodle::Image GuardUP_image{ "assets/GuardUp.png" };
	doodle::Image GuardDown_image{ "assets/GuardDown.png" };
	doodle::Image GuardRight_image{ "assets/GuardRight.png" };
	doodle::Image GuardLeft_image{ "assets/GuardLeft.png" };
	doodle::Image Guard_CHEW_image{ "assets/Chew_dog.png" }; //껌먹는개
	doodle::Image Ruby_CHEW_image{ "assets/Chew_ruby.png" }; //껌먹는개
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