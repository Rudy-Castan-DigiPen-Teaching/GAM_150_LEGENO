/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Game.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/

#include"Game.h"
#include"Pathfinding.h" //pathfinding logic

using namespace doodle;

void Game::Set_up()
{
	sounds.Set_up_sound();
	Current_state = State::SPLASH;
}

void Game::Draw()
{

	switch (Current_state)
	{
	case State::SPLASH:
	{
		doodle::push_settings();
		doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginCenter);
		doodle::set_image_mode(doodle::RectMode::Center);
		if (Is_digipen_splash_done == false)
		{
			doodle::clear_background();
			doodle::draw_image(Digipen_logo, 0, 0);
		}
		else if (Is_digipen_splash_done == true)
		{
			doodle::clear_background();
			doodle::draw_image(Game_logo, 0, 0);
		}
		doodle::pop_settings();
		break;
	}

	case State::START:
	{
		clear_background();
		doodle::draw_image(Main_menu, 0, 0, Width, Height);
		switch (Current_menu)
		{
			case static_cast<int>(MenuOption::START) : doodle::draw_image(Start_button, 0, 0, Width, Height);
			{
				break;
			}
			case static_cast<int>(MenuOption::CREDIT) : doodle::draw_image(Credit_button, 0, 0, Width, Height);
			{
				break;
			}
			case static_cast<int>(MenuOption::QUIT) : doodle::draw_image(Quit_button, 0, 0, Width, Height);
			{
				break;
			}
			case static_cast<int>(MenuOption::OPTION) : doodle::draw_image(Option_button, 0, 0, Width, Height);
			{
				break;
			}
		}
		break;
	}

	case State::CREDIT:
	{
		if (Is_credit_done == false)
		{
			doodle::draw_image(Credit_menu_1, 0, 0, Width, Height);
		}
		else if (Is_credit_done == true)
		{
			doodle::draw_image(Credit_menu_2, 0, 0, Width, Height);
		}
		break;
	}

	case State::OPTION:
	{
		doodle::draw_image(Option_menu, 0, 0, Width, Height);
		switch (static_cast<int>(Current_volume))
		{
		case 25: doodle::draw_image(Sound1, 0, 0, Width, Height); break;
		case 50: doodle::draw_image(Sound2, 0, 0, Width, Height); break;
		case 75: doodle::draw_image(Sound3, 0, 0, Width, Height); break;
		case 100: doodle::draw_image(Sound4, 0, 0, Width, Height); break;
		}
		break;
	}

	case State::LEVEL_SELECT:
	{
		doodle::draw_image(Level_select, 0, 0, Width, Height);
		switch (Curr_level)
		{
		case (static_cast<int>(State::TUTORIAL)): doodle::draw_image(Tutorial_button, 0, 0, Width, Height);
			break;
		case (static_cast<int>(State::FLOOR_1)): doodle::draw_image(Level1_button, 0, 0, Width, Height);
			break;
		case (static_cast<int>(State::FLOOR_2)): doodle::draw_image(Level2_button, 0, 0, Width, Height);
			break;
		case (static_cast<int>(State::FLOOR_3)): doodle::draw_image(Level3_button, 0, 0, Width, Height);
			break;
		}

		doodle::draw_image(Treasure_box, 0, 0, Width, Height);


		if (Save_treasure[0] == true)
		{
			doodle::draw_image(Level_select_Treasure_1, 0, 0, Width, Height);
		}

		if (Save_treasure[1] == true)
		{
			doodle::draw_image(Level_select_Treasure_2, 0, 0, Width, Height);
		}
		if (Save_treasure[2] == true)
		{
			doodle::draw_image(Level_select_Treasure_3, 0, 0, Width, Height);
		}
		if (Save_treasure[3] == true) {

			doodle::draw_image(Level_select_Treasure_4, 0, 0, Width, Height);
		}

		break;
	}

	case State::TUTORIAL:
	case State::FLOOR_1:
	case State::FLOOR_2:
	case State::FLOOR_3:
	{
		Draw_level();
		Draw_radar();
		break;
	}
	case State::PAUSE:
	{
		doodle::draw_image(Pause_screen, 0, 0, Width, Height);
		switch (static_cast<int>(Current_volume))
		{
		case 25: doodle::draw_image(Pause_sound1, 0, 0, Width, Height); break;
		case 50: doodle::draw_image(Pause_sound2, 0, 0, Width, Height); break;
		case 75: doodle::draw_image(Pause_sound3, 0, 0, Width, Height); break;
		case 100: doodle::draw_image(Pause_sound4, 0, 0, Width, Height); break;
		}
		switch (Current_menu)
		{
			case static_cast<int>(PauseOption::RESTART) :
			{
				doodle::draw_image(Pause_Restart, 0, 0, Width, Height);
				break;
			}
			case static_cast<int>(PauseOption::MAIN_MENU) :
			{
				doodle::draw_image(Pause_Quit, 0, 0, Width, Height);
				break;
			}
		}
		break;
	}
	case State::CLEAR:
	{
		push_settings();
		clear_background();
		switch (Curr_level)
		{
			case static_cast<int>(State::TUTORIAL) :
			{
				draw_image(Clear_tutorial, 0, 0, Width, Height * 1.2);// function for image movement
				break;
			}
			case static_cast<int>(State::FLOOR_1) :
			{
				draw_image(Clear_scene1, 0, 0, Width, Height * 1.2);// function for image movement
				break;
			}
			case static_cast<int>(State::FLOOR_2) :
			{
				draw_image(Clear_scene2, 0, 0, Width, Height * 1.2);// function for image movement
				break;
			}
			case static_cast<int>(State::FLOOR_3) :
			{
				draw_image(Clear_scene3, 0, 0, Width, Height * 1.2);// function for image movement
				break;
			}
		}
		draw_image(Jump_minsoo.image, Width * 0.52, Height * 0.4, Jump_minsoo.GetFrameSize().x, Jump_minsoo.GetFrameSize().y, Jump_minsoo.GetDrawPos().x, 0);
		Jump_minsoo.Update();
		draw_image(Clear_effect.image, Width * 0.5, Height * 0.3, Clear_effect.GetFrameSize().x, Clear_effect.GetFrameSize().y, Clear_effect.GetDrawPos().x, 0);
		Clear_effect.Update();
		Draw_treasure();
		pop_settings();
		break;
	}
	case State::ENDING:
	{
		Ending_timer -= DeltaTime;
		push_settings();
		clear_background();

		doodle::draw_image(Minsoo_UPUP.image, Width / 4.0, Height / 4.0, Minsoo_UPUP.frameSize.x, Minsoo_UPUP.frameSize.y, Minsoo_UPUP.GetDrawPos().x, 0);
		pop_settings();

		if (MouseIsPressed)
		{
			Draw_hojin = true;
			Hojin_pos = { 0,-Hojin.GetHeight() * 1.0 };
		}

		if (Ending_timer < 0)
		{
			Ending_credit_ypos -= DeltaTime * 100;
			doodle::draw_image(Ending_scene.image, 0, 0, Width, Height, Ending_scene.GetDrawPos().x, 0, Ending_scene.frameSize.x, Ending_scene.frameSize.y);

			doodle::draw_image(Ending_credit, Width / 2, Ending_credit_ypos, Width / 2, Height * 2.0);

			Update_shooting_star();
			Draw_star();
		}
	}

	break;




	case State::GAME_OVER:
	{
		push_settings();
		clear_background();
		draw_image(Game_over_scene, 0, 0, Width, Height);// function for image movement
		pop_settings();
		break;
	}

	}
}

void Game::Get_inputkey(doodle::KeyboardButtons doodleButton)
{
	switch (Current_state)
	{
	case State::SPLASH:
	{
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			if (Is_digipen_splash_done == false)
			{
				Is_digipen_splash_done = !Is_digipen_splash_done;
				break;
			}
			else if (Is_digipen_splash_done == true)
			{
				Current_state = State::START;
				break;
			}
		}
	}
	break;
	case State::START:
	{
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
			switch (Current_menu)
			{
				case static_cast<int>(MenuOption::START) :
				{
					Previous_state = Current_state;
					Current_state = State::LEVEL_SELECT;
					doodle::clear_background(0);
					sounds.music.stop();
					Is_music_playing = false;
					break;
				}
				case static_cast<int>(MenuOption::CREDIT) :
				{
					Previous_state = Current_state;
					Current_state = State::CREDIT;
					break;
				}
				case static_cast<int>(MenuOption::QUIT) :
				{
					doodle::close_window();
					break;
				}
				case static_cast<int>(MenuOption::OPTION) :
				{
					Previous_state = Current_state;
					Current_state = State::OPTION;
					break;
				}
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (Current_menu > static_cast<int>(MenuOption::START))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Current_menu--;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (Current_menu < static_cast<int>(MenuOption::OPTION))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Current_menu++;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Right)
		{
			if (Current_menu == static_cast<int>(MenuOption::OPTION) - 1)
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Current_menu++;
			}
			else if (Current_menu == static_cast<int>(MenuOption::OPTION))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (Current_menu == static_cast<int>(MenuOption::OPTION))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Current_menu--;
			}
		}
	}
	break;
	case State::OPTION:
	{
		if (doodleButton == doodle::KeyboardButtons::Right)
		{
			if (Current_volume < 100)
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Current_volume += 25;
				for (sf::Sound& s : sounds.sounds)
				{
					s.setVolume(Current_volume);
				}
				sounds.music.setVolume(Current_volume);
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (Current_volume > 0)
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Current_volume -= 25;
				for (sf::Sound& s : sounds.sounds)
				{
					s.setVolume(Current_volume);
				}
				sounds.music.setVolume(Current_volume);
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Enter || doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
			Current_state = Previous_state;
		}
	}
	break;
	case State::CREDIT:
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
			Is_credit_done = false;
			Current_state = Previous_state;
		}
		else if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			if (Is_credit_done == true)
			{
				Is_credit_done = !Is_credit_done;
				Current_state = Previous_state;
			}
			else if (Is_credit_done == false)
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Is_credit_done = !Is_credit_done;
			}
		}
		break;
	case State::ENDING:
	{
		if (Ending_timer < 0)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
			sounds.music.stop();
			Is_music_playing = false;
			Current_state = State::START;
		}
		else
		{
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
		}
		break;
	}
	case State::LEVEL_SELECT:
	{

		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (Curr_level > static_cast<int>(State::TUTORIAL))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Curr_level--;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (Curr_level < static_cast<int>(State::FLOOR_3))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Curr_level++;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
			Current_state = State::START;
		}
		else if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.music.stop();
			Is_music_playing = false;
			switch (Curr_level)
			{
			case (static_cast<int>(State::TUTORIAL)):
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Reset();
				Current_state = State::TUTORIAL;
				minsoo.position = { 3,2 };
				break;
			}
			case (static_cast<int>(State::FLOOR_1)):
			{
				if (Unlock_level >= static_cast<int>(State::FLOOR_1))
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
					Reset();
					Current_state = State::FLOOR_1;

				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
				}
				break;
			}
			case (static_cast<int>(State::FLOOR_2)):
			{
				if (Unlock_level >= static_cast<int>(State::FLOOR_2))
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));

					Current_state = State::FLOOR_2;
					Reset();
				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
				}
				break;
			}

			case (static_cast<int>(State::FLOOR_3)):
			{
				if (Unlock_level >= static_cast<int>(State::FLOOR_3))
				{
					bool Save_all_treasure = true;
					for (int i = 0; i < 4; i++)
					{
						if (Save_treasure[i] == false)
						{
							Save_all_treasure = false;
						}
					}
					if (Save_all_treasure == true)
					{
						sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
						Reset();
						Current_state = State::FLOOR_3;

					}
					else
					{
						sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
					}
				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
				}
				break;
			}
			}
		}
	}
	break;

	case State::TUTORIAL:
	case State::FLOOR_1:
	case State::FLOOR_2:
	case State::FLOOR_3:
	{
		Input_level(doodleButton);
		break;
	}
	case State::PAUSE:
	{
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.music.play();
			Is_music_playing = true;
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
			Current_state = Previous_state;
			doodle::ElapsedTime = Pause_timer;
			Is_paused = false;
		}
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));

			switch (Current_menu)
			{
				case static_cast<int>(PauseOption::SOUND) :
				{
					sounds.music.play();
					Is_music_playing = true;
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
					Current_state = Previous_state;
					doodle::ElapsedTime = Pause_timer;
					Is_paused = false;
					break;
				}
				case static_cast<int>(PauseOption::RESTART) :
				{
					switch (Curr_level)
					{
						case static_cast<int>(State::TUTORIAL) :
						{
							Current_state = State::TUTORIAL;
							Reset();
							minsoo.position = { 3,2 };
							break;
						}
						case static_cast<int>(State::FLOOR_1) :
						{
							Current_state = State::FLOOR_1;
							Reset();
							break;
						}
						case static_cast<int>(State::FLOOR_2) :
						{
							Current_state = State::FLOOR_2;
							Reset();
							break;
						}
						case static_cast<int>(State::FLOOR_3) :
						{
							Current_state = State::FLOOR_3;
							Reset();
							break;
						}
					}
					Current_menu = static_cast<int>(PauseOption::SOUND);
					break;
				}
				case static_cast<int>(PauseOption::MAIN_MENU) :
				{
					Current_state = State::START;
					Current_menu = static_cast<int>(MenuOption::START);
					break;
				}
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (Current_menu > static_cast<int>(PauseOption::SOUND))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Current_menu--;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (Current_menu < static_cast<int>(PauseOption::MAIN_MENU))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
				Current_menu++;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Right)
		{
			if (Current_menu == static_cast<int>(PauseOption::SOUND))
			{
				if (Current_volume < 100)
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
					Current_volume += 25;
					for (sf::Sound& s : sounds.sounds)
					{
						s.setVolume(Current_volume);
					}
					sounds.music.setVolume(Current_volume);
				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
				}
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (Current_menu == static_cast<int>(PauseOption::SOUND))
			{
				if (Current_volume > 0)
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
					Current_volume -= 25;
					for (sf::Sound& s : sounds.sounds)
					{
						s.setVolume(Current_volume);
					}
					sounds.music.setVolume(Current_volume);
				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SELECT_LIMIT_EFFECT));
				}
			}
		}
		break;
	}
	case State::CLEAR:
	{
		if (doodleButton == doodle::KeyboardButtons::Enter || doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Stop_sound();
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
			Current_state = State::LEVEL_SELECT;
			if (Unlock_level < static_cast<int>(State::FLOOR_3))
			{
				Unlock_level++;
			}
		}
		break;
	}
	case State::GAME_OVER:
	{
		if (doodleButton == doodle::KeyboardButtons::Enter || doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
			Is_played_bite = false;
			Curr_level = static_cast<int>(State::TUTORIAL);
			Current_state = State::START;
		}
		break;
	}
	}

}

void Game::Update()
{
	switch (Current_state)
	{
	case State::SPLASH:
	{
		Splash_timer -= doodle::DeltaTime;
		if (Is_digipen_splash_done == false && Splash_timer < 0)
		{
			Is_digipen_splash_done = true;
			Splash_timer = 3;
		}
		else if (Is_digipen_splash_done == true && Splash_timer < 0)
		{
			Is_digipen_splash_done = false;
			Splash_timer = 3;
			Current_state = State::START;
			Current_menu = static_cast<int>(MenuOption::START);
		}
		break;
	}

	case State::START:
	{
		if (Is_music_playing == false)
		{
			sounds.Set_music("assets/MainMenuBGM.ogg", true);
			sounds.music.play();
			Is_music_playing = true;
		}
		break;
	}
	case State::LEVEL_SELECT:
	{
		if (Is_music_playing == false)
		{
			sounds.Set_music("assets/LevelSelectMenuBGM.ogg", true);
			sounds.music.play();
			Is_music_playing = true;
		}
		break;
	}
	case State::TUTORIAL:
	case State::FLOOR_1:
	case State::FLOOR_2:
	case State::FLOOR_3:
	{
		if (Is_paused == false)
		{
			Update_level();
		}
		break;
	}
	case State::CLEAR:
	{
		//if(Level_clear[0] == true)
		//{
		//	if(Get_treasure[0] == true)
		//	{
		//		Save_treasure[0] = true;
		//	}
		//	if (Get_treasure[1] == true)
		//	{
		//		Save_treasure[1] = true;
		//	}
		//}
		//if (Level_clear[1] == true)
		//{
		//	if (Get_treasure[2] == true)
		//	{
		//		Save_treasure[2] = true;
		//	}
		//	if (Get_treasure[3] == true)
		//	{
		//		Save_treasure[3] = true;
		//	}
		//}
		break;
	}
	case State::GAME_OVER:
	{
		if (Is_played_bite == false)
		{
			sounds.Play_sound(static_cast<int>(SoundType::BITE));
			Is_played_bite = true;
		}
		break;
	}
	case State::ENDING:
	{
		if (Ending_timer < 0)
		{
			if (Is_music_playing == false)
			{
				sounds.Stop_sound();
				sounds.Set_music("assets/EndingBGM.ogg", true);
				sounds.music.play();
				Is_music_playing = true;
			}
			Ending_scene.Update();
		}
		else
		{
			if (sounds.Is_sound_playing(static_cast<int>(SoundType::LADDER)) == false)
			{
				sounds.Play_sound(static_cast<int>(SoundType::LADDER));
			}
			Minsoo_UPUP.Update();
		}
	}
	}
}

void Game::Update_level()
{
	Timer = Total_time - static_cast<int>(doodle::ElapsedTime);
	if (Camera_move == false)
	{
		camera.Update(minsoo.Get_position());
		minsoo.Update_position(Is_minsoo_move);
		guard.Update_position();
		Collision_check();
		if (Is_minsoo_move == false)  //when minsoo moving finished
		{
			guard.Check_watching_wall(map);  // if guard's direction is toward the wall
			Tile_check();
			Radar_obtain();
		}
		for (int i = 0; i < static_cast<int>(guard.Guards.size()); i++)
		{
			if (guard.Guards[i].is_trace == true && guard.Guards[i].is_okay == true)
			{
				math::ivec2 curr_position = math::ivec2{ static_cast<int>(guard.Guards[i].Position.x) ,static_cast<int>(guard.Guards[i].Position.y) };

				if (path_finding(map, minsoo.target_pos, curr_position).empty() != true)
				{
					curr_position = path_finding(map, minsoo.target_pos, curr_position).back().pos;
				}
				curr_position = math::ivec2{ static_cast<int>(guard.Guards[i].Position.x) ,static_cast<int>(guard.Guards[i].Position.y) } - curr_position;  // 페스파인딩으로 다음 갈 곳에 대한 시야 변경
				set_direction(curr_position, i);
			}
		}
		guard.Set_sight();
	}
	if (Camera_move == true)
	{
		Move_camera(guard.Guards.back().Position);
	}

	guard.Tracing_check(minsoo); //check position if it is in guard sight

	Set_ingame_music();

	guard.Guard_movement_update(Exit_pos, map, minsoo.movement);
	if (Current_state >= State::TUTORIAL && Current_state <= State::FLOOR_3)
	{
		if (Current_state != State::TUTORIAL)
		{
			if (Timer < 20 && Timer > 0)
			{
				if (sounds.Is_sound_playing(static_cast<int>(SoundType::TIMER_TIC)) == false)
				{
					sounds.Play_sound(static_cast<int>(SoundType::TIMER_TIC));
				}
			}
			else if (Timer <= 0)
			{
				sounds.Stop_sound();
				sounds.music.stop();
				Is_music_playing = false;
				sounds.Play_sound(static_cast<int>(SoundType::TIMES_UP));
				Current_state = State::GAME_OVER;
			}
		}
		if (Radar_start == true)
		{
			if (Get_count() <= 4 && sounds.Is_sound_playing(static_cast<int>(SoundType::RADAR)) == false)
			{
				sounds.Play_sound(static_cast<int>(SoundType::RADAR));
			}
		}
		for (auto i : guard.Guards)
		{
			if (i.is_okay == false)
			{
				if (sounds.Is_sound_playing(static_cast<int>(SoundType::CHEWING_GUM)) == false)
				{
					sounds.Play_sound(static_cast<int>(SoundType::CHEWING_GUM));
				}
			}

		}
	}
}

void Game::Tile_check()
{
	for (int i{ 0 }; i < map.map.size(); i++)
	{
		if (map.map[i].Type == Type::BOMB)
		{
			if (minsoo.explode_count == 0)
			{
				sounds.Play_sound(static_cast<int>(SoundType::EXPLOSION));
				if (Is_exit == true)
				{
					if (Current_state != State::FLOOR_3)
					{
						map.map[i].Type = Type::CAN_ESCAPE;
					}
					else
					{
						map.map[i].Type = Type::LADDER;
					}
				}
				else
				{
					map.map[i].Type = Type::BOMB_TO_ROAD;
				}
			}
			else
			{
				if (sounds.Is_sound_playing(static_cast<int>(SoundType::BOMB_FUSE)) == false)
				{
					sounds.Play_sound(static_cast<int>(SoundType::BOMB_FUSE));
				}
			}
		}

		if (map.map[i].Position == minsoo.Get_position() && map.map[i].Type == Type::CAN_ESCAPE)
		{
			sounds.Stop_sound();
			sounds.music.stop();

			if (Current_state != State::TUTORIAL)
			{
				if (Get_treasure[0] == true)
				{
					Save_treasure[0] = true;
				}
				if (Get_treasure[1] == true)
				{
					Save_treasure[1] = true;
				}

				if (Get_treasure[2] == true)
				{
					Save_treasure[2] = true;
				}
				if (Get_treasure[3] == true)
				{
					Save_treasure[3] = true;
				}
			}

			Reset();
			Is_music_playing = false;
			sounds.Play_sound(static_cast<int>(SoundType::WIN));
			Current_state = State::CLEAR;
		}

		if (map.map[i].Position == minsoo.Get_position() && map.map[i].Type == Type::LADDER)
		{
			sounds.Stop_sound();
			sounds.music.stop();
			Is_music_playing = false;
			Current_state = State::ENDING;
			Ending_credit_ypos = Height;
			Generate_shooting_star();
		}

		else if (map.map[i].Position == minsoo.Get_position() && map.map[i].Type == Type::RADAR)
		{
			map.map[i].Type = Type::ROAD;
			Is_radar_obtained = true;
		}
		else if (map.map[i].Position == minsoo.Get_position() && map.map[i].Type == Type::NEXT)
		{
			sounds.Play_sound(static_cast<int>(SoundType::PASS));
			map.map[i].Type = Type::ROAD;
			minsoo.position += math::vec2{ 0,5 };
			guard.Guards.clear();
		}
		else if (map.map[i].Position == minsoo.Get_position() && map.map[i].Type == Type::TREASURE_CROWN)
		{
			sounds.Play_sound(static_cast<int>(SoundType::GET_TREASURE));
			map.map[i].Type = Type::ROAD;
			Get_treasure[0] = true;
		}
		else if (map.map[i].Position == minsoo.Get_position() && map.map[i].Type == Type::TREASURE_KEY)
		{
			sounds.Play_sound(static_cast<int>(SoundType::GET_TREASURE));
			map.map[i].Type = Type::ROAD;
			Get_treasure[1] = true;
		}
		else if (map.map[i].Position == minsoo.Get_position() && map.map[i].Type == Type::TREASURE_COIN)
		{
			sounds.Play_sound(static_cast<int>(SoundType::GET_TREASURE));
			map.map[i].Type = Type::ROAD;
			Get_treasure[2] = true;
		}
		else if (map.map[i].Position == minsoo.Get_position() && map.map[i].Type == Type::TREASURE_DIA)
		{
			sounds.Play_sound(static_cast<int>(SoundType::GET_TREASURE));
			map.map[i].Type = Type::ROAD;
			Get_treasure[3] = true;
		}
	}
	if (Current_state == State::TUTORIAL)
	{
		if (minsoo.position == map.map[485].Position || minsoo.position == map.map[528].Position || minsoo.position == map.map[571].Position)
		{
			if (guard.Guards.empty())
			{
				guard.Guards.push_back(guard_info{ math::ivec2(12, 10), Direction::DOWN });
			}
		}
		else if (minsoo.position == map.map[495].Position || minsoo.position == map.map[538].Position || minsoo.position == map.map[581].Position)
		{
			if (guard.Guards.size() == 1)
			{
				guard.Guards.push_back(guard_info{ math::ivec2(22, 14), Direction::UP });
			}
		}
	}
}

void Game::Draw_treasure()
{
	for (int i = 0; i < 4; i++)
	{
		if (Current_state != State::CLEAR)
		{
			if (Get_treasure[i] == true)
			{
				switch (i)
				{
				case 0:
				{
					draw_image(Treasure_1_UI, 10, 0, Width, Height);
					break;
				}

				case 1:
				{
					draw_image(Treasure_2_UI, 10, 0, Width, Height);
					break;
				}

				case 2:
				{
					draw_image(Treasure_3_UI, 10, 0, Width, Height);
					break;
				}

				case 3:
				{
					draw_image(Treasure_4_UI, 10, 0, Width, Height);
					break;
				}
				}
			}
		}
			else
			{
			if (Save_treasure[i] == true)
			{
				switch (i)
				{
				case 0:
				{
					draw_image(Clear_Treasure_1, 4, 5, Width, Height * 1.2);
					break;
				}

				case 1:
				{
					draw_image(Clear_Treasure_2, 8, 30, Width, Height);
					break;
				}

				case 2:
				{
					draw_image(Clear_Treasure_3, 0, 25, Width, Height);
					break;
				}

				case 3:
				{
					draw_image(Clear_Treasure_4, 5, 25, Width, Height);
					break;

				}
				}
			}
		}
	}
}

void Game::Set_ingame_music()
{
	if (minsoo.is_dead == false)
	{
		if (Current_state >= State::TUTORIAL && Current_state <= State::FLOOR_3)
		{
			if (guard.Is_trace_sommeone() == true && Is_music_playing == false)
			{
				Is_music_playing = true;
				Is_chased_state = true;
				sounds.Set_music("assets/Siren.ogg", true);
				sounds.music.play();
			}
			if (guard.Is_trace_sommeone() == false && Is_chased_state == true)
			{
				Is_music_playing = false;
				Is_chased_state = false;
			}

			if (guard.Is_trace_sommeone() == true && Is_chased_state == false)
			{
				Is_music_playing = false;
				Is_chased_state = true;
			}

			if (guard.Is_trace_sommeone() == false && Is_music_playing == false)
			{
				Is_music_playing = true;
				sounds.Set_music("assets/BasicBGM.ogg", true);
				sounds.music.play();
			}
		}
	}
}

void Game::Generate_shooting_star()
{
	Star_pos.x = doodle::random(0, Width);
	Star_pos.y = -(Star.GetHeight() + 1000);
}

void Game::Update_shooting_star()
{
	Star_anim.Update();

	Star_pos.y += doodle::DeltaTime * 1500;
	if (Draw_hojin == true)
	{
		Hojin_pos += doodle::DeltaTime * 1500;
		if (Hojin_pos.x > Width || Hojin_pos.y > Height)
		{
			if (Draw_hojin == true)
			{
				Draw_hojin = false;
			}
		}
	}
	if (Star_pos.y > -Star.GetHeight())
	{
		Star_pos.x += doodle::DeltaTime * 1500;
	}
	if (Star_pos.x > Width || Star_pos.y > Height)
	{
		Star_pos.x = doodle::random(0, Width);
		Star_pos.y = -(Star.GetHeight() + 4000);
		if (Draw_hojin == true)
		{
			Draw_hojin = false;
		}
	}
}


void Game::Draw_star()
{
	if (Draw_hojin == false)
	{
		draw_image(Star_anim.image, Star_pos.x, Star_pos.y, Star_anim.frameSize.x, Star_anim.frameSize.y, Star_anim.GetDrawPos().x, 0);
	}
	else
	{
		draw_image(Hojin, Hojin_pos.x, Hojin_pos.y);
	}
}

void Game::Move_camera(math::vec2 position)
{
	math::vec2 target_pos = position;
	math::vec2 init_pos = New_pos;
	if (Camera_move == true)
	{
		if (New_pos.x > target_pos.x)
		{
			New_pos.x -= 10 * doodle::DeltaTime;
		}
		if (New_pos.x < target_pos.x)
		{
			New_pos.x += 10 * doodle::DeltaTime;
		}

		if (New_pos.y > target_pos.y)
		{

			New_pos.y = (target_pos.y - init_pos.y) / (target_pos.x - init_pos.x) * (New_pos.x - init_pos.x) + init_pos.y;
		}
		if (New_pos.y < target_pos.y)
		{

			New_pos.y = (target_pos.y - init_pos.y) / (target_pos.x - init_pos.x) * (New_pos.x - init_pos.x) + init_pos.y;
		}
		camera.Update(New_pos);
		if (New_pos.x >= target_pos.x && New_pos.y >= target_pos.y)
		{
			if (Start_camera_count == false)
			{
				Curr_timer = Timer;
				Start_camera_count = true;
			}
			double Target_time = 2;
			if (Curr_timer - Timer > Target_time)
			{
				Camera_move = false;
				New_pos = minsoo.Get_position();
				camera.Update(New_pos);
			}
		}
	}
}

void Game::Reset()
{
	Timer = Total_time;
	doodle::ElapsedTime = 0;
	Offset = 0;
	Speed = 10;
	Is_bomb_set = false;
	Is_exit = false;
	Radar_start = false;
	Make_radar_big = false;
	Is_in_guard_sight = false;
	Is_music_playing = false;
	Is_chased_state = false;
	Is_played_bite = false;
	Is_paused = false;
	Camera_move = false;
	Curr_timer = 0;
	Start_camera_count = false;
	Is_minsoo_move = false;
	map.Set_up(Curr_level);
	minsoo.Set_up();
	guard.Set_up(Curr_level);
	Ending_timer = Minsoo_UPUP.target_time * 6;
	Ending_credit_ypos = doodle::Height;


	if (Save_treasure[0] == false)
	{
		Get_treasure[0] = false;
	}
	if (Save_treasure[1] == false)
	{
		Get_treasure[1] = false;
	}


	if (Save_treasure[2] == false)
	{
		Get_treasure[2] = false;
	}
	if (Save_treasure[3] == false)
	{
		Get_treasure[3] = false;
	}



	minsoo.direction = Direction::DOWN;
	for (int i = 0; i < map.map.size(); i++)
	{
		if (map.map[i].Type == Type::RADAR)
		{
			New_pos = map.map[i].Position;
		}
	}
}

bool Game::Check(doodle::KeyboardButtons doodleButton) // get keyboard key and check whether the direction minsoo want to go is wall or road
{
	math::vec2 position = minsoo.Get_position();
	switch (doodleButton)
	{
	case doodle::KeyboardButtons::S:
	case doodle::KeyboardButtons::Down:
		position.y += 1;
		break;
	case doodle::KeyboardButtons::A:
	case doodle::KeyboardButtons::Left:
	{
		position.x -= 1;
		break;
	}
	case doodle::KeyboardButtons::D:
	case doodle::KeyboardButtons::Right:
	{
		position.x += 1;
		break;
	}
	case doodle::KeyboardButtons::W:
	case doodle::KeyboardButtons::Up:
	{
		position.y -= 1;
		break;
	}
	default:
		return true;
	}
	for (int i = 0; i < map.map.size(); i++)
	{
		if (map.map[i].Position == position && map.map[i].Type == Type::WALL)
		{
			sounds.Play_sound(static_cast<int>(SoundType::CRASH_WALL));
			return true;
		}
	}


	return false;
}

bool Game::Check_guard(int index)  // change sight if guard direction is toward the wall
{

	switch (guard.Guards[index].Direction)
	{
	case Direction::UP:   //move up
	{
		for (auto& i : map.map)
		{
			if (i.Position.x == guard.Guards[index].Position.x && i.Position.y == guard.Guards[index].Position.y - 1 && i.Type == Type::WALL)
			{
				guard.Change_sight(map, index);
				return true;
			}
		}
	}
	break;
	case Direction::DOWN:   //move down
		for (auto& i : map.map)
		{
			if (i.Position.x == guard.Guards[index].Position.x && i.Position.y == guard.Guards[index].Position.y + 1 && i.Type == Type::WALL)
			{
				guard.Change_sight(map, index);
				return true;
			}
		}
		break;
	case Direction::RIGHT:   //move right
		for (auto& i : map.map)
		{
			if (i.Position.x == guard.Guards[index].Position.x + 1 && i.Position.y == guard.Guards[index].Position.y && i.Type == Type::WALL)
			{
				guard.Change_sight(map, index);
				return true;
			}
		}
		break;
	case Direction::LEFT:   //move left
		for (auto& i : map.map)
		{
			if (i.Position.x == guard.Guards[index].Position.x - 1 && i.Position.y == guard.Guards[index].Position.y && i.Type == Type::WALL)
			{
				guard.Change_sight(map, index);
				return true;
			}
		}
		break;
	}
	return false;
}

void Game::Collision_check()
{
	for (auto& Guard : guard.Guards)
	{
		math::vec2 pos;
		pos = minsoo.Get_position() - Guard.Position;
		double difference = abs(pos.x) + abs(pos.y);
		if (difference <= 0.5)
		{
			sounds.Stop_sound();
			sounds.music.stop();
			Is_music_playing = false;
			sounds.Play_sound(static_cast<int>(SoundType::MEOW));
			minsoo.is_dead = true;
			Current_state = State::GAME_OVER;
		}
	}
}


void Game::set_direction(math::vec2 position, int index)
{
	if (position.x == -1)
	{
		guard.Guards[index].Direction = Direction::RIGHT;
	}
	if (position.x == 1)
	{
		guard.Guards[index].Direction = Direction::LEFT;
	}
	if (position.y == -1)
	{
		guard.Guards[index].Direction = Direction::DOWN;
	}
	if (position.y == 1)
	{
		guard.Guards[index].Direction = Direction::UP;
	}
}

void Game::Set_item(doodle::KeyboardButtons button)
{
	switch (button)
	{

	case doodle::KeyboardButtons::_1:
	{
		if (minsoo.chew_item > 0)
		{
			for (int i{ 0 }; i < map.map.size(); i++)
			{
				if (map.map[i].Position == minsoo.Get_position())
				{
					sounds.Play_sound(static_cast<int>(SoundType::PUT_ITEM));
					map.map[i].Type = Type::DOG_CHEW;
					minsoo.chew_item--;
				}
			}
		}
	}
	break;
	case doodle::KeyboardButtons::_2:
	{
		if (minsoo.bomb_item > 0)
		{
			for (int i{ 0 }; i < map.map.size(); i++)
			{
				if (map.map[i].Position == minsoo.Get_position())
				{
					sounds.Play_sound(static_cast<int>(SoundType::PUT_ITEM));
					if (map.map[i].Position == Exit_pos)
					{
						Is_exit = true;
					}
					minsoo.explode_count = 3;
					map.map[i].Type = Type::BOMB;
					minsoo.bomb_item--;

				}
			}
		}
	}
	break;

	}
}

void Game::Radar_obtain()
{
	if (Is_radar_obtained == true)
	{
		if (Current_state == State::TUTORIAL)
		{
			map.map[826].Type = Type::EXIT;
			Exit_pos = map.map[826].Position;
			Is_radar_obtained = false;
			Radar_start = true;
			guard.Guards.push_back(guard_info{ math::ivec2(30, 19), Direction::LEFT ,"Ruby" }); //minsu start pos
			Camera_move = true;
		}
		else
		{
			int item_num = 1;
			math::ivec2 pos(0, 0);
			int random_num = 0;

			while (item_num > 0)
			{
				switch (Curr_level)
				{
					case static_cast<int>(State::FLOOR_1) :
						case static_cast<int>(State::FLOOR_2) :
					{
						pos = math::ivec2(static_cast<int>(minsoo.position.x), static_cast<int>(minsoo.position.y));
						random_num = doodle::random(0, 20) - 10;
						pos.x += random_num;
						random_num = doodle::random(0, 10) - 5;
						pos.y += random_num;

						break;
					}
					case static_cast<int>(State::FLOOR_3) :
					{
						pos = math::ivec2(doodle::random(0, 10), 0);
						if (pos.x < 5)
						{
							pos = math::ivec2(2, 22);
						}
						else
						{
							pos = math::ivec2(40, 2);
						}
						break;
					}
				}
				for (auto& m : map.map)
				{
					if (m.Position == pos && m.Type == Type::ROAD)
					{
						m.Type = Type::EXIT;
						Exit_pos = m.Position;
						item_num--;
						Is_radar_obtained = false;
						Radar_start = true;
						switch (Curr_level)
						{
							case static_cast<int>(State::FLOOR_1) :
							{
								guard.Guards.push_back(guard_info{ math::ivec2(30, 14), Direction::LEFT ,"Ruby" }); //ruby start pos
								break;
							}
							case static_cast<int>(State::FLOOR_2) :
							{
								guard.Guards.push_back(guard_info{ math::ivec2(30, 12), Direction::LEFT ,"Ruby" }); //ruby start pos
								break;
							}
							case static_cast<int>(State::FLOOR_3) :
							{
								guard.Guards.push_back(guard_info{ math::ivec2(39, 21), Direction::LEFT ,"Ruby" }); //ruby start pos
								break;
							}
						}
						Camera_move = true;
					}
				}
			}
		}
	}
}

void Game::Draw_radar()
{
	if (Radar_start == true && Is_exit == false)
	{
		if (Get_count() == 0)
		{
			Speed = 25;
		}
		else
		{
			Speed = 20. / Get_count();
		}

		double off_spd = Offset * Speed;
		draw_image(map.Radar, Width * 0.035 + (off_spd / 2), Height * 0.80625 + (off_spd / 2), doodle::Width * 0.083 - off_spd, doodle::Height * 0.125 - off_spd);
		if (Make_radar_big == false)
		{
			off_spd = ++Offset * Speed;
			if (off_spd > 50)
			{
				Offset = 50 / Speed;
				Make_radar_big = true;
			}
		}
		else if (Make_radar_big == true)
		{
			off_spd = --Offset * Speed;
			if (off_spd < 0)
			{
				Offset = 0;
				Make_radar_big = false;
			}
		}
	}
}

double Game::Get_count()
{
	int count{ 1 };
	math::vec2 minsu_pos = minsoo.target_pos;
	math::vec2 exit_minsu = Exit_pos - minsu_pos;

	if (exit_minsu.x == 0 && exit_minsu.y == 0)//exit
	{
		return 0;
	}
	else if (exit_minsu.x == 0 || exit_minsu.y == 0)//same x or y
	{
		double result = exit_minsu.y == 0 ? exit_minsu.x : exit_minsu.y;
		return abs(result);
	}
	else if (exit_minsu.x > 0 && exit_minsu.y > 0)//left top
	{
		while (1)
		{
			if (count >= exit_minsu.x)
			{
				for (double column = exit_minsu.x, row = 0; row < exit_minsu.x; row++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = count, row = 0; row < count; row++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}

			if (count >= exit_minsu.y)
			{
				for (double column = 0, row = exit_minsu.y; column <= exit_minsu.y; column++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = 0, row = count; column <= count; column++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			count++;
		}
	}
	else if (exit_minsu.x > 0 && exit_minsu.y < 0)//left bottom
	{
		while (1)
		{
			if (count >= exit_minsu.x)
			{
				for (double column = exit_minsu.x, row = 0; row < exit_minsu.x; row++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = count, row = 0; row < count; row++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			if (count >= -exit_minsu.y)
			{
				for (double column = 0, row = -exit_minsu.y; column <= -exit_minsu.y; column++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = 0, row = count; column <= count; column++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			count++;
		}
	}
	else if (exit_minsu.x < 0 && exit_minsu.y > 0)//right top
	{
		while (1)
		{
			if (count >= -exit_minsu.x)
			{
				for (double column = -exit_minsu.x, row = 0; row < -exit_minsu.x; row++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = count, row = 0; row < count; row++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			if (count >= exit_minsu.y)
			{
				for (double column = 0, row = exit_minsu.y; column <= exit_minsu.y; column++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = 0, row = count; column <= count; column++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			count++;
		}
	}
	else if (exit_minsu.x < 0 && exit_minsu.y < 0)//right bottom
	{
		while (1)
		{
			if (count >= -exit_minsu.x)
			{
				for (double column = -exit_minsu.x, row = 0; row < -exit_minsu.x; row++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = count, row = 0; row < count; row++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			if (count >= -exit_minsu.y)
			{
				for (double column = 0, row = -exit_minsu.y; column <= -exit_minsu.y; column++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = 0, row = count; column <= count; column++)
				{
					if (Exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			count++;
		}
	}

	return -1;
}

void Game::Draw_level()
{
	doodle::clear_background(0);
	map.Draw(camera);
	guard.Draw_guard(camera);
	guard.Draw_sight(camera, map);
	minsoo.Draw_minsu(camera);
	if (Current_state != State::TUTORIAL)
	{
		doodle::draw_image(Sight_limit, (minsoo.Get_position().x + camera.Get_position().x - 1), (minsoo.Get_position().y + camera.Get_position().y - 20), doodle::Width, doodle::Height);
	}
	draw_image(UI, 0, 0, doodle::Width, doodle::Height);

	switch (minsoo.chew_item)
	{
	case 1:
	{
		draw_image(Chew_num1, 0, 0, doodle::Width, doodle::Height);
		break;
	}
	case 2:
	{
		draw_image(Chew_num2, 0, 0, doodle::Width, doodle::Height);
		break;
	}
	case 3:
	{
		draw_image(Chew_num3, 0, 0, doodle::Width, doodle::Height);
		break;
	}
	default:
		break;
	}

	switch (minsoo.bomb_item)
	{
	case 1:
	{
		draw_image(Bomb_num1, 0, 0, doodle::Width, doodle::Height);
		break;
	}
	case 2:
	{
		draw_image(Bomb_num2, 0, 0, doodle::Width, doodle::Height);
		break;
	}
	case 3:
	{
		draw_image(Bomb_num3, 0, 0, doodle::Width, doodle::Height);
		break;
	}
	default:
		break;
	}

	if (Current_state != State::TUTORIAL)
	{
		push_settings();
		set_outline_width(7);
		set_outline_color(0);
		draw_line(doodle::Width * 0.075, doodle::Height * 0.12, Width * 0.075 + Width * 0.05 * sin((PI / 50) * (100 - static_cast<double>(Timer))), doodle::Height * 0.12 + Height * 0.075 * cos((PI) * ((static_cast<double>(Timer)) / 50 - 1)));
		set_outline_width(3);
		set_outline_color(255, 0, 0);
		draw_line(doodle::Width * 0.075, doodle::Height * 0.12, Width * 0.075 + Width * 0.05 * sin((PI / 50) * (100 - static_cast<double>(Timer))), doodle::Height * 0.12 + Height * 0.075 * cos((PI) * ((static_cast<double>(Timer)) / 50 - 1)));

		set_font_size(30);
		pop_settings();
	}

	if (guard.Is_trace_sommeone() == true) // if someone trace
	{
		draw_image(Siren_sprite.image, Width / 2.5, 0, Siren_sprite.GetFrameSize().x, Siren_sprite.GetFrameSize().y, Siren_sprite.GetDrawPos().x, 0);
		Siren_sprite.Update();
	}


	Draw_treasure();
	if (Current_state == State::TUTORIAL)
	{
		Draw_information();
	}
}


void Game::Input_level(doodle::KeyboardButtons doodleButton)
{
	if (doodleButton == doodle::KeyboardButtons::Escape)
	{
		sounds.Stop_sound();
		sounds.music.pause();
		Is_music_playing = false;
		sounds.Play_sound(static_cast<int>(SoundType::SELECT_EFFECT));
		Previous_state = Current_state;
		Current_state = State::PAUSE;
		Pause_timer = doodle::ElapsedTime;
		Is_paused = true;
	}


	if (doodleButton == doodle::KeyboardButtons::Left || doodleButton == doodle::KeyboardButtons::Down || doodleButton == doodle::KeyboardButtons::Up || doodleButton == doodle::KeyboardButtons::Right ||
		doodleButton == doodle::KeyboardButtons::A || doodleButton == doodle::KeyboardButtons::S || doodleButton == doodle::KeyboardButtons::W || doodleButton == doodle::KeyboardButtons::D)
	{
		if (Check(doodleButton) == false && Camera_move != true)
		{
			if (Is_minsoo_move == false)
			{
				sounds.Play_sound(static_cast<int>(SoundType::FOOT_STEP));
				minsoo.Set_position(doodleButton);

				Is_minsoo_move = true;

				for (int i = 0; i < static_cast<int>(guard.Guards.size()); i++)
				{
					if (guard.Guards[i].is_trace == true && guard.Guards[i].is_okay == true)
					{
						math::ivec2 curr_position = math::ivec2{ static_cast<int>(guard.Guards[i].Position.x) ,static_cast<int>(guard.Guards[i].Position.y) };

						if (path_finding(map, minsoo.target_pos, curr_position).empty() != true)
						{
							curr_position = path_finding(map, minsoo.target_pos, curr_position).back().pos;
						}

						curr_position = math::ivec2{ static_cast<int>(guard.Guards[i].Position.x) ,static_cast<int>(guard.Guards[i].Position.y) } - curr_position;  // 페스파인딩으로 다음 갈 곳에 대한 시야 변경
						set_direction(curr_position, i);
					}

					else
					{
						if (guard.Guards[i].is_okay == true)
						{
							if (minsoo.movement % 5 == 0)
							{
								guard.Change_sight(map, i);
							}
							else
							{
								guard.Check_watching_wall(map);
							}
						}
					}
					guard.Set_position(i);

				}
			}
		}
	}
	Set_item(doodleButton);
#ifdef _DEBUG
	if (doodleButton == doodle::KeyboardButtons::R)
	{
		Reset();
	}
	if (doodleButton == doodle::KeyboardButtons::K)
	{
		sounds.Stop_sound();
		sounds.music.stop();
		Is_music_playing = false;
		sounds.Play_sound(static_cast<int>(SoundType::WIN));
		if (Current_state == State::FLOOR_1)
		{
			Save_treasure[0] = true;
			Save_treasure[1] = true;
		}
		if (Current_state == State::FLOOR_2)
		{
			Save_treasure[2] = true;
			Save_treasure[3] = true;
		}

		Current_state = State::CLEAR;

	}
	if (doodleButton == doodle::KeyboardButtons::L)
	{
		Current_state = State::ENDING;
		Generate_shooting_star();
		sounds.Stop_sound();
		sounds.music.stop();
		Is_music_playing = false;
	}
#endif
}


void Game::Change_sight()
{
	if (Is_minsoo_move == false)
	{
		for (int i = 0; i < static_cast<int>(guard.Guards.size()); i++)
		{
			if (Check_guard(i) == false)
			{
				if (minsoo.movement % 5 == 0 && Is_sight_changed == false)
				{
					if (guard.Guards[i].is_trace == false && guard.Guards[i].is_okay == true)
					{
						guard.Change_sight(map, i);
					}
				}
			}
		}
		Is_sight_changed = true;
	}
}

bool Game::Is_get_all_treasure()
{
	for (int i = 0; i < 4; i++)
	{
		if (Get_treasure[i] == false)
		{
			return false;
		}
	}
	return true;
}

int Game::Treasure_count()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (Get_treasure[i] == true)
		{
			count++;
		}
	}
	return count;
}
void Game::Draw_information()
{
	push_settings();
	set_outline_width(3);
	set_outline_color(0);
	set_font_fade_out_interval(0.45, 0.55);
	set_font_backdrop_fade_out_interval(0.6, 1.0);
	if ((minsoo.position.x >= 3 && minsoo.position.x <= 7) && (minsoo.position.y >= 2 && minsoo.position.y <= 6))
	{
		if (Is_get_all_treasure() == true)
		{
			map.map[265].Type = Type::NEXT;
		}
		else
		{
			set_fill_color(255);
			set_font_size(30);
			draw_text("Move With Keyboard Arrows.\nCollect " + to_string(4 - Treasure_count()) + " More Treasures!", Width * 0.2, Height * 0.15);
		}
	}
	else if (minsoo.position.y >= 9 && minsoo.position.y <= 15)
	{
		if (minsoo.position.x >= 7 && minsoo.position.x <= 10)
		{
			set_fill_color(255);
			set_font_size(30);
			draw_text("Guards Will Chase If\nMinsoo Is In Sight.", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.position.x >= 12 && minsoo.position.x <= 14)
		{
			set_fill_color(255, 0, 0);
			set_font_size(80);
			draw_text("Run!", Width * 0.4, Height * 0.3);
		}
		else if (minsoo.position.x > 14 && minsoo.position.x < 18 && minsoo.chew_item >= 3)
		{
			set_fill_color(255, 255, 0);
			set_font_size(30);
			draw_text("Use The Dog Chew!\nPress: 1", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.position.x >= 18 && minsoo.position.x < 21)
		{
			set_fill_color(255);
			set_font_size(30);
			draw_text("After 3 Steps, The Guards Will\nStart Roaming Around.", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.position.x >= 22 && minsoo.position.x <= 24)
		{
			set_fill_color(255, 0, 0);
			set_font_size(80);
			draw_text("Run!", Width * 0.4, Height * 0.3);
		}
		else if (minsoo.position.x > 24 && minsoo.position.x <= 27 && minsoo.chew_item >= 2)
		{
			set_fill_color(255, 255, 0);
			set_font_size(30);
			draw_text("Now You Know What To Do.\nPress: 1", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.position.x > 27 && minsoo.position.x <= 31)
		{
			switch (minsoo.chew_item)
			{
			case 3:
			case 2:
			{
				set_fill_color(255);
				set_font_size(30);
				draw_text("Use " + to_string(minsoo.chew_item - 1) + " More Dog Chew!\nPress: 1", Width * 0.2, Height * 0.15);
				break;
			}
			default: map.map[590].Type = Type::NEXT; break;
			}
		}
	}
	else if (minsoo.position.y >= 18 && minsoo.position.y <= 20)
	{
		if (Is_bomb_set == true && minsoo.explode_count != 0)
		{
			set_fill_color(255);
			set_font_size(30);
			draw_text(to_string(minsoo.explode_count) + " More Moves\nUntil Bomb Exploads!", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.explode_count == 0)
		{
			set_fill_color(255, 255, 0);
			set_font_size(30);
			draw_text("Go Down The Stairs!", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.position.x > 26 && minsoo.position.x <= 31)
		{
			set_fill_color(255);
			set_font_size(30);
			draw_text("If Radar Item Is Obtained,\nRuby Will Chase.", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.position.x >= 21 && minsoo.position.x <= 25 && minsoo.chew_item >= 1)
		{
			set_fill_color(255, 255, 0);
			set_font_size(30);
			draw_text("Use The Last Dog Chew!\nPress: 1", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.position.x > 13 && minsoo.position.x <= 20)
		{
			set_fill_color(255);
			set_font_size(30);
			draw_text("Radar Will Expand And Shrink\nFaster As The Hidden Exit Gets Near.", Width * 0.2, Height * 0.15);
		}
		else if (minsoo.position.x >= 8 && minsoo.position.x <= 13)
		{
			if ((minsoo.position.x > 8 && minsoo.position.x < 10) && minsoo.position.y > 18 && minsoo.position.y < 20)
			{
				set_fill_color(255, 255, 0);
				set_font_size(30);
				draw_text("Use Bomb To Reveal The Exit!\nPress: 2\n", Width * 0.2, Height * 0.15);
				if (minsoo.bomb_item == 0)
				{
					Is_bomb_set = true;
				}
			}
			else
			{
				set_fill_color(255);
				set_font_size(30);
				draw_text("Radar Will Make Sound\nIf The Exit Is Near Enough.", Width * 0.2, Height * 0.15);
			}
		}
	}
	pop_settings();
}