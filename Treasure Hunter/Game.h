/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include "doodle/doodle.hpp" // doodle image & functions 
#include "ENUM.h"	//	enum classes
#include "Map.h"	//	Map class
#include "Minsoo.h" //	Minsoo class
#include "Guard.h"	//	Guard class
#include "Sound.h"	//	Sound class
#include "Camera.h"	//	Camera class
#include<cmath>    //abs
#include"Sprite.h" //animation
class Game
{
	Sound sounds;
	Map map;
	Minsoo minsoo;
	Guard guard;
	Camera camera;

	int timer{ 100 };
	double pause_timer{ 0 };
	const int total_time{ 100 };
	bool did_abtain_radar{ false };
	bool radar_start{ false };
	bool make_radar_big{ false };
	double offset{ 0 };
	double speed{ 10 };
	int treasure_count{ 0 };
	int score{ 0 };
	double splash_timer{ 3 };
	math::ivec2 exit_pos{ 0 };

	bool is_exit{ false };
	bool is_in_guard_sight{ false };
	bool is_music_playing{ false };
	bool is_chased_state{ false };
	bool is_digipen_splash_done{ false };
	bool is_paused{ false };
	bool is_credit_done{ false };

	State current_state{ State::SPLASH };
	State previous_state{ State::SPLASH };
	int current_menu{ static_cast<int>(MenuOption::START) };
	int curr_level{ static_cast<int>(State::TUTORIAL) };
	int unlock_level{ static_cast<int>(State::LEVEL_1) };

	bool camera_move{ false };
	bool cheat_Z{ false };
	float current_volume{ 100 };

	bool is_minsoo_move = false;

	bool is_guard_move = false;

	bool is_sight_changed = false;

	bool is_played_bite = false;

	bool Get_treasure[4] = { false, };
	
	doodle::Image digipen_logo{ "assets/DigiPen_BLACK_1024px.png" };
	doodle::Image game_logo{ "assets/Treasure_Hunter_Logo.jpg" };
	doodle::Image main_menu{ "assets/MainMenu.png" };
	doodle::Image level_select{ "assets/Level_select.png" };
	doodle::Image start_button{ "assets/StratButton.png" };
	doodle::Image credit_button{ "assets/CreditButton.png" };
	doodle::Image quit_button{ "assets/QuitButton.png" };
	doodle::Image GameOver_scene{ "assets/GameOver.png" };
	doodle::Image credit_menu_1{ "assets/Credit_1.png" };
	doodle::Image credit_menu_2{ "assets/Credit_2.png" };
	doodle::Image option_button{ "assets/Option_button.png" };
	doodle::Image tutorial_button{ "assets/tutorial_button.png" };
	doodle::Image level1_button{ "assets/Level1_button.png" };
	doodle::Image level2_button{ "assets/Level2_button.png" };
	doodle::Image level3_button{ "assets/Level3_button.png" };
	
	doodle::Image option_menu{ "assets/Option.png" };
	doodle::Image sound1{ "assets/Sound1.png" };
	doodle::Image sound2{ "assets/Sound2.png" };
	doodle::Image sound3{ "assets/Sound3.png" };
	doodle::Image sound4{ "assets/Sound4.png" };
	doodle::Image pause_sound1{ "assets/pause_volume1.png" };
	doodle::Image pause_sound2{ "assets/pause_volume2.png" };
	doodle::Image pause_sound3{ "assets/pause_volume3.png" };
	doodle::Image pause_sound4{ "assets/pause_volume4.png" };
	doodle::Image UI{ "assets/UI.png" };
	doodle::Image Pause_screen{ "assets/Pause_screen.png" };
	doodle::Image Pause_Restart{ "assets/Pause_Restart.png" };
	doodle::Image Pause_Quit{ "assets/Pause_Quit.png" };

	doodle::Image Chew_num1{ "assets/chew_num1.png" };
	doodle::Image Chew_num2{ "assets/chew_num2.png" };
	doodle::Image Chew_num3{ "assets/chew_num3.png" };

	doodle::Image Bomb_num1{ "assets/bomb_num1.png" };
	doodle::Image Bomb_num2{ "assets/bomb_num2.png" };
	doodle::Image Bomb_num3{ "assets/bomb_num3.png" };
	doodle::Image Sight_limit{ "assets/Sight_limit.png" };

	doodle::Image Treasure_1_UI{ "assets/Treasure_1_UI.png" };
	doodle::Image Treasure_2_UI{ "assets/Treasure_2_UI.png" };
	doodle::Image Treasure_3_UI{ "assets/Treasure_3_UI.png" };
	doodle::Image Treasure_4_UI{ "assets/Treasure_4_UI.png" };


	doodle::Image Clear_Treasure_1{ "assets/Clear_Treasure_1.png" };
	doodle::Image Clear_Treasure_2{ "assets/Clear_Treasure_2.png" };
	doodle::Image Clear_Treasure_3{ "assets/Clear_Treasure_3.png" };
	doodle::Image Clear_Treasure_4{ "assets/Clear_Treasure_4.png" };
	
	doodle::Image Clear_scene1{ "assets/Level1_clear.png" };
	doodle::Image Clear_scene2{ "assets/Level2_clear.png" };
	doodle::Image Clear_scene3{ "assets/Level3_clear.png" };

	doodle::Image Level_select_Treasure_1{ "assets/level_select_Treasure1.png" };
	doodle::Image Level_select_Treasure_2{ "assets/level_select_Treasure2.png" };
	doodle::Image Level_select_Treasure_3{ "assets/level_select_Treasure3.png" };
	doodle::Image Level_select_Treasure_4{ "assets/level_select_Treasure4.png" };
	doodle::Image Treasure_box{ "assets/treasure_box.png" };


	Sprite Siren_sprite{ "assets/siren_sprite.png",9,0.05 };
	
	Sprite Clear_effect{ "assets/clear_effect.png",8,0.1 };
	
	Sprite Jump_minsoo{ "assets/Jump_minsoo.png",7,0.1 };

	
	double Get_count();
public:
	void Set_up();
	void Draw();
	void Get_inputkey(doodle::KeyboardButtons doodleButton);
	bool Check(doodle::KeyboardButtons doodleButton); // check blocks around minsoo
	void Reset();
	void Update();
	bool Check_guard(int index);  // when a guard is looking a wall, change the direction
	void Sight_check(int index);  // when a minsoo is looking a wall, change the direction
	void Set_item(doodle::KeyboardButtons button);	// put items on the map
	void Radar_obtain();	//when minsoo gets radar, add Exit, add Ruby, ready to show Ruby 
	void Draw_radar();
	void Move_camera(math::vec2 position); // camera shows Ruby for a while
	bool Is_get_all_treasure();
	void set_direction(math::vec2 position, int index);
	void Collision_check();
	void Change_sight();

	void Draw_level();
	void Input_level(doodle::KeyboardButtons doodleButton);
	void Update_level();

	void Tile_check(); //3blockss move --> pung~  Check_bomb() -> Tile_check()
	void Draw_treasure();
	bool Is_sound_playing();
	void Set_Ingame_Music();
	math::vec2 new_pos{ minsoo.Get_position() };
	double curr_timer{ 0 };
	bool start_camera_count{ false };
	bool level_clear[3] = { false, };
};

