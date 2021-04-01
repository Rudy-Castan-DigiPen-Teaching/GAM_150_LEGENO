#include"Map.h"
#include"Minsoo.h"
#include "Guard.h"
#include"doodle/doodle.hpp"

class Game
{
	Map map;
	Minsoo minsu;
	Guard guard;
	int timer = 20;
	bool did_abtain_radar{ false };
public:
	void setup();
	void Draw();
	void set_position(doodle::KeyboardButtons doodleButton);
	bool check(doodle::KeyboardButtons doodleButton);
	void caught_by_guard();
	void Reset();
	void Update();
	bool check_guard(int index, int direction);
};