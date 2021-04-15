#include"Map.h"
#include"Minsoo.h"
#include "Guard.h"
#include"doodle/doodle.hpp"
#include "ENUM.h"

class Game
{
	Map map;
	Minsoo minsu;
	Guard guard;
	int timer = 100;
	const int total_time{ 100 };
	bool did_abtain_radar{ false };
	int treasure_count{ 0 };
	int score{ 0 };
	State current_state = State::START;
	doodle::Image clear_scene{ "assets/clear_scene.png" };
public:
	void setup();
	void Draw();
	void Get_inputkey(doodle::KeyboardButtons doodleButton);
	bool check(doodle::KeyboardButtons doodleButton);
	void caught_by_guard();
	void Reset();
	void Update();
	bool check_guard(int index);
	void sight_check(int index);
};