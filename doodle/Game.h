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
	bool radar_start{  false  };
	bool make_radar_big{ false };
	double offset{ 0 };
	double speed = 10;
	int treasure_count{ 0 };
	int score{ 0 };
	bool is_exit =false;
	State current_state = State::START;
	int current_menu = static_cast<int>(MenuOption::start);
	doodle::Image clear_scene{ "assets/clear_scene.png" };
	doodle::Image main_menu{ "assets/MainMenu.png" };
	doodle::Image start_button{ "assets/StratButton.png" };
	doodle::Image quit_button{ "assets/QuitButton.png" };
	doodle::Image credit_button{ "assets/CreditButton.png" };
	Camera camera;
	int get_count(math::ivec2 exit_pos);
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
	//double move = 0;
	void radar_obtain();
	void draw_radar();
};