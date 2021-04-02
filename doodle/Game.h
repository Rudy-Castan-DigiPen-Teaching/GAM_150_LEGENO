#include"Map.h"
#include"Minsoo.h"
#include "Guard.h"
#include"doodle/doodle.hpp"

enum class State
{
	START,
	IN_GAME,
	CLEAR,
	GAME_OVER
};

class Game
{
	Map map;
	Minsoo minsu;
	Guard guard;
	int timer = 20;
	bool did_abtain_radar{ false };
	int treasure_count{ 0 };
	int score{ 0 };
	State current_state = State::START;
public:
	void setup();
	void Draw();
	void Get_inputkey(doodle::KeyboardButtons doodleButton);
	bool check(doodle::KeyboardButtons doodleButton);
	void caught_by_guard();
	void Reset();
	void Update();
	bool check_guard(int index, int direction);
};