/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Game.h
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

	int Timer{ 100 };
	double Pause_timer{ 0 };
	const int Total_time{ 100 };
	bool Radar_start{ false };
	bool Make_radar_big{ false };
	double Offset{ 0 };
	double Speed{ 10 };
	double Splash_timer{ 3 };
	math::ivec2 Exit_pos{ 0 };

	bool Is_radar_obtained{ false };
	bool Is_exit{ false };
	bool Is_in_guard_sight{ false };
	bool Is_music_playing{ false };
	bool Is_chased_state{ false };
	bool Is_digipen_splash_done{ false };
	bool Is_paused{ false };
	bool Is_credit_done{ false };
	bool Is_bomb_set{ false };

	State Current_state{ State::SPLASH };
	State Previous_state{ State::SPLASH };
	int Current_menu{ static_cast<int>(MenuOption::START) };
	int Curr_level{ static_cast<int>(State::TUTORIAL) };
	int Unlock_level{ static_cast<int>(State::FLOOR_1) };

	bool Camera_move{ false };
	float Current_volume{ 50 };

	bool Is_minsoo_move = false;

	bool Is_guard_move = false;

	bool Is_sight_changed = false;

	bool Is_played_bite = false;

	bool Get_treasure[4] = { false, };
	bool Save_treasure[4] = { false, };

	bool Draw_hojin = false;
	doodle::Image Digipen_logo{ "assets/DigiPen_BLACK_1024px.png" };
	doodle::Image Game_logo{ "assets/Treasure_Hunter_Logo.jpg" };
	doodle::Image Main_menu{ "assets/MainMenu.png" };
	doodle::Image Level_select{ "assets/Level_select.png" };
	doodle::Image Start_button{ "assets/StratButton.png" };
	doodle::Image Credit_button{ "assets/CreditButton.png" };
	doodle::Image Quit_button{ "assets/QuitButton.png" };
	doodle::Image Game_over_scene{ "assets/GameOver.png" };
	doodle::Image Credit_menu_1{ "assets/Credit_1.png" };
	doodle::Image Credit_menu_2{ "assets/Credit_2.png" };
	doodle::Image Option_button{ "assets/Option_button.png" };
	doodle::Image Tutorial_button{ "assets/tutorial_button.png" };
	doodle::Image Level1_button{ "assets/Level1_button.png" };
	doodle::Image Level2_button{ "assets/Level2_button.png" };
	doodle::Image Level3_button{ "assets/Level3_button.png" };
	
	doodle::Image Option_menu{ "assets/Option.png" };
	doodle::Image Sound1{ "assets/Sound1.png" };
	doodle::Image Sound2{ "assets/Sound2.png" };
	doodle::Image Sound3{ "assets/Sound3.png" };
	doodle::Image Sound4{ "assets/Sound4.png" };
	doodle::Image Pause_sound1{ "assets/pause_volume1.png" };
	doodle::Image Pause_sound2{ "assets/pause_volume2.png" };
	doodle::Image Pause_sound3{ "assets/pause_volume3.png" };
	doodle::Image Pause_sound4{ "assets/pause_volume4.png" };
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
	
	doodle::Image Clear_tutorial{ "assets/Tutorial_clear.png" };
	doodle::Image Clear_scene1{ "assets/Level1_clear.png" };
	doodle::Image Clear_scene2{ "assets/Level2_clear.png" };
	
	doodle::Image Level_select_Treasure_1{ "assets/level_select_Treasure1.png" };
	doodle::Image Level_select_Treasure_2{ "assets/level_select_Treasure2.png" };
	doodle::Image Level_select_Treasure_3{ "assets/level_select_Treasure3.png" };
	doodle::Image Level_select_Treasure_4{ "assets/level_select_Treasure4.png" };
	doodle::Image Treasure_box{ "assets/treasure_box.png" };
	doodle::Image Ending_credit{ "assets/Ending_credit.png" };
	doodle::Image Hojin{ "assets/Hojin.png" };

	Sprite Siren_sprite{ "assets/siren_sprite.png",9,0.05 };
	
	Sprite Clear_effect{ "assets/clear_effect.png",8,0.1 };
	
	Sprite Jump_minsoo{ "assets/Jump_minsoo.png",7,0.1 };

	Sprite Minsoo_UPUP{ "assets/Minsoo_upup.png",3 ,0.5 };

	Sprite Ending_scene{ "assets/Ending_scene.png",17 ,0.25 };

	Sprite Star_anim{ "assets/star_anim.png",10 ,0.1 };
	double Get_count();
public:
	void Set_up();
	void Draw();
	void Get_inputkey(doodle::KeyboardButtons doodleButton);
	bool Check(doodle::KeyboardButtons doodleButton); // check blocks around minsoo
	void Reset();
	void Update();
	bool Check_guard(int index);  // when a guard is looking a wall, change the direction
	void Set_item(doodle::KeyboardButtons button);	// put items on the map
	void Radar_obtain();	//when minsoo gets radar, add Exit, add Ruby, ready to show Ruby 
	void Draw_radar();
	void Move_camera(math::vec2 position); // camera shows Ruby for a while
	bool Is_get_all_treasure();
	int	 Treasure_count();
	void set_direction(math::vec2 position, int index);
	void Collision_check();
	void Change_sight();
	void Draw_information();

	void Draw_level();
	void Input_level(doodle::KeyboardButtons doodleButton);
	void Update_level();

	void Tile_check(); //3blockss move --> pung~  Check_bomb() -> Tile_check()
	void Draw_treasure();
	void Set_ingame_music();
	void Generate_shooting_star();
	void Update_shooting_star();
	void Draw_star();
	math::vec2 New_pos{ minsoo.Get_position() };
	double Curr_timer{ 0 };
	double Ending_timer = Minsoo_UPUP.target_time * 6;
	double Ending_credit_ypos;
	bool Start_camera_count{ false };
	

	math::vec2 Star_pos;
	math::vec2 Hojin_pos;
};

