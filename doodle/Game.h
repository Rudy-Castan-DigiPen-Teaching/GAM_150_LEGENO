#include"Map.h"
#include"Minsoo.h"
#include "Guard.h"
#include"doodle/doodle.hpp"
#include "ENUM.h"
#include "Sound.h"
#include "Camera.h"

class Game
{
	Sound sounds;
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
	bool is_in_guard_sight = false;
	bool is_music_playing = false;
	bool is_chased_state = false;


	State current_state = State::Splash;
	int current_menu = static_cast<int>(MenuOption::start);
	int curr_level = 1;

	doodle::Image digipen_logo{ "assets/DigiPen_BLACK_1024px.png" };
	doodle::Image clear_scene{ "assets/clear_scene.png" };
	doodle::Image main_menu{ "assets/MainMenu.png" };
	doodle::Image level_select{ "assets/Level_select.png" };
	doodle::Image start_button{ "assets/StratButton.png" };
	doodle::Image quit_button{ "assets/QuitButton.png" };
	doodle::Image credit_button{ "assets/CreditButton.png" };
	doodle::Image GameOver_scene{ "assets/GameOver.png" };
	doodle::Image credit_menu{ "assets/Credit.png" };
	doodle::Image option_button{ "assets/option_button.png" };
	doodle::Image level1_button{ "assets/Level1_button.png" };
	doodle::Image level2_button{ "assets/Level2_button.png" };
	doodle::Image level3_button{ "assets/Level3_button.png" };
	doodle::Image option_menu{ "assets/option.png" };
	doodle::Image sound1{ "assets/sound1.png" };
	doodle::Image sound2{ "assets/sound2.png" };
	doodle::Image sound3{ "assets/sound3.png" };
	doodle::Image sound4{ "assets/sound4.png" };

	Camera camera;
	int get_count(math::ivec2 exit_pos);
	bool camera_move = false;
	bool cheat_Z = false;

	float current_volume = 100;
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
	double curr_timer = 0;
	bool start_camera_count = false;
	void radar_obtain();
	void draw_radar();
	void Ruby_camera();
	math::vec2 new_pos = minsu.GetPosition();
};