#include"Map.h"
#include"Minsoo.h"
#include "Guard.h"
#include"doodle/doodle.hpp"
#include "ENUM.h"

#include "Camera.h"

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
	int chew_item{ 3 };
	State current_state = State::START;
	doodle::Image clear_scene{ "assets/clear_scene.png" };
	Camera camera;
public:
	void setup();
	void Draw();
	void Get_inputkey(doodle::KeyboardButtons doodleButton);
	bool check(doodle::KeyboardButtons doodleButton);
	void caught_by_guard();   // 민수 포지션 == 가드포지션  -> 게임오버
	void Reset();
	void Update();
	bool check_guard(int index);  // 가드가 벽을 보고있을때 시야방향 바꾸기
	void sight_check(int index);
	void set_item(doodle::KeyboardButtons button);
	double move = 0;
};