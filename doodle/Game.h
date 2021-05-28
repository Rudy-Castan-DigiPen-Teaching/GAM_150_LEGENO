#include "doodle/doodle.hpp" // doodle image & functions 
#include "ENUM.h"	//	enum classes
#include "Map.h"	//	Map class
#include "Minsoo.h" //	Minsoo class
#include "Guard.h"	//	Guard class
#include "Sound.h"	//	Sound class
#include "Camera.h"	//	Camera class
#include<cmath>    //abs
class Game
{
	Sound sounds;
	Map map;
	Minsoo minsoo;
	Guard guard;
	Camera camera;

	int timer{ 100 };
	const int total_time{ 100 };
	bool did_abtain_radar{ false };
	bool radar_start{ false };
	bool make_radar_big{ false };
	double offset{ 0 };
	double speed{ 10 };
	int treasure_count{ 0 };
	int score{ 0 };

	bool is_exit{ false };
	bool is_in_guard_sight{ false };
	bool is_music_playing{ false };
	bool is_chased_state{ false };

	State current_state{ State::SPLASH };
	int current_menu{ static_cast<int>(MenuOption::START) };
	int curr_level{ 1 };

	bool camera_move{ false };
	bool cheat_Z{ false };
	float current_volume{ 100 };

	bool is_minsoo_move = false;

	bool is_guard_move = false;

	bool is_sight_changed = false;
	doodle::Image digipen_logo{ "assets/DigiPen_BLACK_1024px.png" };
	doodle::Image clear_scene{ "assets/Clear_scene.png" };
	doodle::Image main_menu{ "assets/MainMenu.png" };
	doodle::Image level_select{ "assets/Level_select.png" };
	doodle::Image start_button{ "assets/StratButton.png" };
	doodle::Image quit_button{ "assets/QuitButton.png" };
	doodle::Image credit_button{ "assets/CreditButton.png" };
	doodle::Image GameOver_scene{ "assets/GameOver.png" };
	doodle::Image credit_menu{ "assets/Credit.png" };
	doodle::Image option_button{ "assets/Option_button.png" };
	doodle::Image level1_button{ "assets/Level1_button.png" };
	doodle::Image level2_button{ "assets/Level2_button.png" };
	doodle::Image level3_button{ "assets/Level3_button.png" };
	doodle::Image option_menu{ "assets/Option.png" };
	doodle::Image sound1{ "assets/Sound1.png" };
	doodle::Image sound2{ "assets/Sound2.png" };
	doodle::Image sound3{ "assets/Sound3.png" };
	doodle::Image sound4{ "assets/Sound4.png" };

	double Get_count(math::vec2 exit_pos);
public:
	void Set_up();
	void Draw();
	void Get_inputkey(doodle::KeyboardButtons doodleButton);
	bool Check(doodle::KeyboardButtons doodleButton); // check blocks around minsoo
	void Caught_by_guard_current(int index);
	void Caught_by_guard_nextmove();   // if minsoo caught by guard, change state to Game Over
	void Reset();
	void Update();
	bool Check_guard(int index);  // when a guard is looking a wall, change the direction
	void Sight_check(int index);  // when a minsoo is looking a wall, change the direction
	void Set_item(doodle::KeyboardButtons button);	// put items on the map
	void Radar_obtain();	//when minsoo gets radar, add Exit, add Ruby, ready to show Ruby 
	void Draw_radar();
	void Move_camera(math::vec2 position); // camera shows Ruby for a while
	void Collision_check();
	void Change_sight();
	void set_direction(math::vec2 position, int index);
	math::vec2 new_pos{ minsoo.Get_position() };
	double curr_timer{ 0 };
	bool start_camera_count{ false };
};