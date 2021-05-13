#pragma once
#include"vec2.h"
#include"Map.h"
#include"doodle/doodle.hpp"
#include "Camera.h"
#include "Minsoo.h"
struct sight_info 
{
	math::ivec2 position;
	bool is_valid = true;  // 시야가 벽에 가려있나 안가려있나
};

struct guard_info
{
	math::ivec2 position;
	Direction direction = Direction::UP;
	string guard_type = "guard";
	bool is_okay = true;  //개껌먹었는지 안먹었는지
	bool is_trace = false; //민수가 시야에 들어왔는지 안들어왔는지
	int trace_movement = 0;
	int movement = 0;
	sight_info sight_position[3] = { {0,true} };
	
};
class Guard :Map
{
public:
	void setup();
	void Draw_guard(Camera& camera);
	void Draw_Sight(Camera& camera,Map MAP);
	vector<guard_info> guards;
	void move(int index);
	void change_sight(Map m, int index);
	void Guard_movement_update(Map& m,int movement);
	void set_sight();
	int in_guard_sight(Minsoo minsoo); // 가드 시야에 있을때 몇번째 인덱스 가드인지 리턴
	bool warning = false;
private:
	int sight_size = 3;  //시야 몇칸보이는지
	int how_many_trace = 5;// 몇칸동안 따라오는지
	int how_many_craze = 3;//얼마동안 개껌먹고 미쳐있는지
	doodle::Image GuardUP_image{ "assets/GuardUp.png" };
	doodle::Image GuardDown_image{ "assets/GuardDown.png" };
	doodle::Image GuardRight_image{ "assets/GuardRight.png" };
	doodle::Image GuardLeft_image{ "assets/GuardLeft.png" };
	doodle::Image Guard_CHEW_image{ "assets/chew_dog.png" }; //껌먹는개

	doodle::Image Guard_tracing_image{ "assets/tracing_dog.png" };

	doodle::Image Ruby_image{ "assets/tracing_dog.png" };
};