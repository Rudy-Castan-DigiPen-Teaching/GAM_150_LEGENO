/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/

#include"Game.h"
#include"Pathfinding.h" //pathfinding logic
using namespace doodle;

void Game::Set_up()
{
	sounds.Set_up_sound();
	current_state = State::SPLASH;
}

void Game::Draw()
{
	switch (current_state)
	{
	case State::SPLASH:
	{
		doodle::push_settings();
		doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginCenter);
		doodle::set_image_mode(doodle::RectMode::Center);
		if (is_digipen_splash_done == false)
		{
			doodle::clear_background();
			doodle::draw_image(digipen_logo, 0, 0);
		}
		else if (is_digipen_splash_done == true)
		{
			doodle::clear_background();
			doodle::draw_image(game_logo, 0, 0);
		}
		doodle::pop_settings();
		break;
	}

	case State::START:
	{
		clear_background();
		doodle::draw_image(main_menu, 0, 0, Width, Height);
		switch (current_menu)
		{
			case static_cast<int>(MenuOption::START) : doodle::draw_image(start_button, 0, 0, Width, Height); break;
				case static_cast<int>(MenuOption::CREDIT) : doodle::draw_image(credit_button, 0, 0, Width, Height); break;
					case static_cast<int>(MenuOption::QUIT) : doodle::draw_image(quit_button, 0, 0, Width, Height); break;
						case static_cast<int>(MenuOption::OPTION) : doodle::draw_image(option_button, 0, 0, Width, Height); break;
		}
		break;
	}

	case State::CREDIT:
	{
		if (is_credit_done == false)
		{
			doodle::draw_image(credit_menu_1, 0, 0, Width, Height);
		}
		else if (is_credit_done == true)
		{
			doodle::draw_image(credit_menu_2, 0, 0, Width, Height);
		}
		break;
	}

	case State::OPTION:
	{
		doodle::draw_image(option_menu, 0, 0, Width, Height);
		switch (static_cast<int>(current_volume))
		{
		case 25: doodle::draw_image(sound1, 0, 0, Width, Height); break;
		case 50: doodle::draw_image(sound2, 0, 0, Width, Height); break;
		case 75: doodle::draw_image(sound3, 0, 0, Width, Height); break;
		case 100: doodle::draw_image(sound4, 0, 0, Width, Height); break;
		}
		break;
	}

	case State::LEVEL_SELECT:
	{
		doodle::draw_image(level_select, 0, 0, Width, Height);
		switch (curr_level)
		{
		case (static_cast<int>(State::TUTORIAL)): doodle::draw_image(tutorial_button, 0, 0, Width, Height);
			break;
		case (static_cast<int>(State::FLOOR_1)): doodle::draw_image(level1_button, 0, 0, Width, Height);
			break;
		case (static_cast<int>(State::FLOOR_2)): doodle::draw_image(level2_button, 0, 0, Width, Height);
			break;
		case (static_cast<int>(State::FLOOR_3)): doodle::draw_image(level3_button, 0, 0, Width, Height);
			break;
		}

		doodle::draw_image(Treasure_box, 0, 0, Width, Height);


		if(Get_treasure[0] == true && level_clear[1] == true)
		{
			doodle::draw_image(Level_select_Treasure_1, 0, 0, Width, Height);
		}

		if (Get_treasure[1] == true && level_clear[1] == true)
		{
			doodle::draw_image(Level_select_Treasure_2, 0, 0, Width, Height);
		}
		if (Get_treasure[2] == true && level_clear[2] == true)
		{
			doodle::draw_image(Level_select_Treasure_3, 0, 0, Width, Height);
		}
		if (Get_treasure[3] == true && level_clear[2] == true)
		{
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
		switch (static_cast<int>(current_volume))
		{
		case 25: doodle::draw_image(pause_sound1, 0, 0, Width, Height); break;
		case 50: doodle::draw_image(pause_sound2, 0, 0, Width, Height); break;
		case 75: doodle::draw_image(pause_sound3, 0, 0, Width, Height); break;
		case 100: doodle::draw_image(pause_sound4, 0, 0, Width, Height); break;
		}
		switch (current_menu)
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
		switch (curr_level)
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

		Ending_scene.Update();
		sounds.Stop_sound();
		sounds.music.stop();		
		doodle::draw_image(Minsoo_UPUP.image, Width/4.0,Height/4.0 , Minsoo_UPUP.frameSize.x, Minsoo_UPUP.frameSize.y, Minsoo_UPUP.GetDrawPos().x, 0);
		pop_settings();

		Minsoo_UPUP.Update();

			
		if (Ending_timer < 0)
		{
			Ending_credit_ypos -= DeltaTime*100;
			doodle::draw_image(Ending_scene.image, 0, 0, Width, Height, Ending_scene.GetDrawPos().x, 0,Ending_scene.frameSize.x, Ending_scene.frameSize.y);
			doodle::draw_image(Ending_credit, 0, Ending_credit_ypos,Width,Height);
			is_music_playing = false;
		}		

		break;
			
	}

		
	case State::GAME_OVER:
	{
		push_settings();
		clear_background();
		draw_image(GameOver_scene, 0, 0, Width, Height);// function for image movement
		pop_settings();
		break;
	}

	}
}

void Game::Get_inputkey(doodle::KeyboardButtons doodleButton)
{
	switch (current_state)
	{
	case State::SPLASH:
	{
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			if (is_digipen_splash_done == false)
			{
				is_digipen_splash_done = !is_digipen_splash_done;
				break;
			}
			else if (is_digipen_splash_done == true)
			{
				current_state = State::START;
				break;
			}
		}
	}
	break;
	case State::START:
	{
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
			switch (current_menu)
			{
				case static_cast<int>(MenuOption::START) :
				{
					previous_state = current_state;
					current_state = State::LEVEL_SELECT;
					doodle::clear_background(0);
					sounds.music.stop();
					is_music_playing = false;
					break;
				}
				case static_cast<int>(MenuOption::CREDIT) :
				{
					previous_state = current_state;
					current_state = State::CREDIT;
					break;
				}
				case static_cast<int>(MenuOption::QUIT) :
				{
					doodle::close_window();
					break;
				}
				case static_cast<int>(MenuOption::OPTION) :
				{
					previous_state = current_state;
					current_state = State::OPTION;
					break;
				}
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (current_menu > static_cast<int>(MenuOption::START))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				current_menu--;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (current_menu < static_cast<int>(MenuOption::OPTION))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				current_menu++;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Right)
		{
			if (current_menu == static_cast<int>(MenuOption::OPTION) - 1)
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				current_menu++;
			}
			else if (current_menu == static_cast<int>(MenuOption::OPTION))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (current_menu == static_cast<int>(MenuOption::OPTION))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				current_menu--;
			}
		}
	}
	break;
	case State::OPTION:
	{
		if (doodleButton == doodle::KeyboardButtons::Right)
		{
			if (current_volume < 100)
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				current_volume += 25;
				for (sf::Sound& s : sounds.sounds)
				{
					s.setVolume(current_volume);
				}
				sounds.music.setVolume(current_volume);
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (current_volume > 0)
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				current_volume -= 25;
				for (sf::Sound& s : sounds.sounds)
				{
					s.setVolume(current_volume);
				}
				sounds.music.setVolume(current_volume);
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Enter || doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
			current_state = previous_state;
		}
	}
	break;
	case State::CREDIT:
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
			is_credit_done = false;
			current_state = previous_state;
		}
		else if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			if (is_credit_done == true)
			{
				is_credit_done = !is_credit_done;
				current_state = previous_state;
			}
			else if (is_credit_done == false)
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				is_credit_done = !is_credit_done;
			}
		}
		break;
	case State::ENDING:
	{
		current_state = State::START;
		
		break;
	}
	case State::LEVEL_SELECT:
	{

		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (curr_level > static_cast<int>(State::TUTORIAL))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				curr_level--;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (curr_level < static_cast<int>(State::FLOOR_3))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				curr_level++;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
			current_state = previous_state;
		}
		else if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.music.stop();
			is_music_playing = false;
			switch (curr_level)
			{
			case (static_cast<int>(State::TUTORIAL)):
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				Reset();
				current_state = State::TUTORIAL;
				minsoo.position = {3,2};
				break;
			}
			case (static_cast<int>(State::FLOOR_1)):
			{
				if (unlock_level >= static_cast<int>(State::FLOOR_1))
				{
					sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
					Reset();
					current_state = State::FLOOR_1;

				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
				}
				break;
			}
			case (static_cast<int>(State::FLOOR_2)):
			{
				if (unlock_level >= static_cast<int>(State::FLOOR_2))
				{
					sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));

					current_state = State::FLOOR_2;
					Reset();
				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
				}
				break;
			}

			case (static_cast<int>(State::FLOOR_3)):
			{
				//if (unlock_level >= static_cast<int>(State::LEVEL_3))
				{
					//if (Is_get_all_treasure() == true)
					//{
						sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
						Reset();
						current_state = State::FLOOR_3;

				//	}
					//else
					//{
					//	sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
					//}
				}
				//else
				//{
				//	sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
				//}
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
			is_music_playing = true;
			sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
			current_state = previous_state;
			doodle::ElapsedTime = pause_timer;
			is_paused = false;
		}
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));

			switch (current_menu)
			{
				case static_cast<int>(PauseOption::SOUND):
				{
					sounds.music.play();
					is_music_playing = true;
					sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
					current_state = previous_state;
					doodle::ElapsedTime = pause_timer;
					is_paused = false;
					break;
				}
				case static_cast<int>(PauseOption::RESTART) :
				{
					switch (curr_level)
					{
						case static_cast<int>(State::TUTORIAL) :
						{
							current_state = State::TUTORIAL;
							Reset();
							minsoo.position = { 3,2 };
							break;
						}
						case static_cast<int>(State::FLOOR_1) :
						{
							current_state = State::FLOOR_1;
							Reset();
							break;
						}
						case static_cast<int>(State::FLOOR_2) :
						{
							current_state = State::FLOOR_2;
							Reset();
							break;
						}
						case static_cast<int>(State::FLOOR_3) :
						{
							current_state = State::FLOOR_3;
							Reset();
							break;
						}
					}
					current_menu = static_cast<int>(PauseOption::SOUND);
					break;
				}
				case static_cast<int>(PauseOption::MAIN_MENU) :
				{
					current_state = State::START;
					current_menu = static_cast<int>(MenuOption::START);
					break;
				}
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (current_menu > static_cast<int>(PauseOption::SOUND))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				current_menu--;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (current_menu < static_cast<int>(PauseOption::MAIN_MENU))
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
				current_menu++;
			}
			else
			{
				sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Right)
		{
			if (current_menu == static_cast<int>(PauseOption::SOUND))
			{
				if (current_volume < 100)
				{
					sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
					current_volume += 25;
					for (sf::Sound& s : sounds.sounds)
					{
						s.setVolume(current_volume);
					}
					sounds.music.setVolume(current_volume);
				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
				}
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (current_menu == static_cast<int>(PauseOption::SOUND))
			{
				if (current_volume > 0)
				{
					sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
					current_volume -= 25;
					for (sf::Sound& s : sounds.sounds)
					{
						s.setVolume(current_volume);
					}
					sounds.music.setVolume(current_volume);
				}
				else
				{
					sounds.Play_sound(static_cast<int>(SoundType::SelectLimitEffect));
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
			sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
			current_state = State::LEVEL_SELECT;
			if (unlock_level < static_cast<int>(State::FLOOR_3))
			{
				unlock_level++;
			}
		}
		break;
	}
	case State::GAME_OVER:
	{
		if (doodleButton == doodle::KeyboardButtons::Enter || doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
			is_played_bite = false;
			curr_level = static_cast<int>(State::TUTORIAL);
			current_state = State::START;
		}
		break;
	}
	}

}

void Game::Update()
{
	switch (current_state)
	{
	case State::SPLASH:
	{
		splash_timer -= doodle::DeltaTime;
		if (is_digipen_splash_done == false && splash_timer < 0)
		{
			is_digipen_splash_done = true;
			splash_timer = 3;
		}
		else if (is_digipen_splash_done == true && splash_timer < 0)
		{
			is_digipen_splash_done = false;
			splash_timer = 3;
			current_state = State::START;
			current_menu = static_cast<int>(MenuOption::START);
		}
		break;
	}

	case State::START:
	{
		if (is_music_playing == false)
		{
			sounds.Set_music("assets/MainMenuBGM.ogg", true);
			sounds.music.play();
			is_music_playing = true;
		}
		break;
	}
	case State::LEVEL_SELECT:
	{
		if (is_music_playing == false)
		{
			sounds.Set_music("assets/LevelSelectMenuBGM.ogg", true);
			sounds.music.play();
			is_music_playing = true;
		}
		break;
	}
	case State::TUTORIAL:
	case State::FLOOR_1:
	case State::FLOOR_2:
	case State::FLOOR_3:
	{
		if (is_paused == false)
		{
			Update_level();
		}
		break;
	}
	case State::CLEAR:
	{
		break;
	}
	case State::GAME_OVER:
	{
		if (is_played_bite == false)
		{
			sounds.Play_sound(static_cast<int>(SoundType::Bite));
			is_played_bite = true;
		}
		break;
	}
	}
}

void Game::Update_level()
{
	timer = total_time - static_cast<int>(doodle::ElapsedTime);
	if (camera_move == false)
	{
		camera.Update(minsoo.Get_position());
		minsoo.Update_position(is_minsoo_move);
		guard.Update_position();
		Collision_check();
		if (is_minsoo_move == false)  //when minsoo moving finished
		{
			guard.Check_watching_wall(map);  // if guard's direction is toward the wall
			Radar_obtain();
			Tile_check();
		}
		for (int i = 0; i < static_cast<int>(guard.guards.size()); i++)
		{
			if (guard.guards[i].is_trace == true && guard.guards[i].is_okay == true)
			{
				math::ivec2 curr_position = math::ivec2{ static_cast<int>(guard.guards[i].position.x) ,static_cast<int>(guard.guards[i].position.y) };

				if (path_finding<25, 43>(map, minsoo.target_pos, curr_position).empty() != true)
				{
					curr_position = path_finding<25, 43>(map, minsoo.target_pos, curr_position).back().pos;
				}
				curr_position = math::ivec2{ static_cast<int>(guard.guards[i].position.x) ,static_cast<int>(guard.guards[i].position.y) } - curr_position;  // 페스파인딩으로 다음 갈 곳에 대한 시야 변경
				set_direction(curr_position, i);
			}
		}                                            
		guard.Set_sight();
	}
	if (camera_move == true)
	{
		Move_camera(guard.guards.back().position);
	}

	guard.Tracing_check(minsoo); //check position if it is in guard sight

	Set_ingame_music();

	guard.Guard_movement_update(exit_pos, map, minsoo.movement);
	if (current_state != State::TUTORIAL && current_state != State::CLEAR && current_state != State::GAME_OVER)
	{
		if (timer < 20 && timer > 0)
		{
			if (sounds.Is_sound_playing(static_cast<int>(SoundType::TimerTic)) == false)
			{
				sounds.Play_sound(static_cast<int>(SoundType::TimerTic));
			}
		}
		else if (timer <= 0)
		{
			sounds.Stop_sound();
			sounds.music.stop();
			is_music_playing = false;
			sounds.Play_sound(static_cast<int>(SoundType::TimesUp));
			current_state = State::GAME_OVER;
		}
	}
	if (radar_start == true)
	{
		if (Get_count() <= 4 && sounds.Is_sound_playing(static_cast<int>(SoundType::Radar)) == false)
		{
			sounds.Play_sound(static_cast<int>(SoundType::Radar));
		}
	}
	for (auto i : guard.guards)
	{
		if (i.is_okay == false)
		{
			if (sounds.Is_sound_playing(static_cast<int>(SoundType::ChewingGum)) == false)
			{
				sounds.Play_sound(static_cast<int>(SoundType::ChewingGum));
			}
		}

	}
}

void Game::Tile_check()
{
	for (int i{ 0 }; i < map.map.size(); i++)
	{
		if (map.map[i].type == Type::BOMB)
		{
			if (minsoo.explode_count == 0)
			{
				sounds.Play_sound(static_cast<int>(SoundType::Explosion));
				if (is_exit == true)
				{
					if (current_state != State::FLOOR_3)
					{
						map.map[i].type = Type::CAN_ESCAPE;
					}
					else
					{
						map.map[i].type = Type::Lader;
					}
				}
				else
				{
					map.map[i].type = Type::BOMB_TO_ROAD;
				}
			}
			else
			{
				if (sounds.Is_sound_playing(static_cast<int>(SoundType::BombFuse)) == false)
				{
					sounds.Play_sound(static_cast<int>(SoundType::BombFuse));
				}
			}
		}

		if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::CAN_ESCAPE)
		{
			sounds.Stop_sound();
			sounds.music.stop();
			level_clear[static_cast<int>(current_state) - static_cast<int>(State::TUTORIAL)] = true;
			Reset();
			is_music_playing = false;
			sounds.Play_sound(static_cast<int>(SoundType::Win));
			current_state = State::CLEAR;
		}

		if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::Lader)
		{
			current_state = State::ENDING;
			Ending_credit_ypos = Height;
		}

		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::RADAR)
		{
			map.map[i].type = Type::ROAD;
			is_radar_obtained = true;
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::NEXT)
		{
			map.map[i].type = Type::ROAD;
			minsoo.position += math::vec2{ 0,5 };
			guard.guards.clear();
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::TREASURE_crown)
		{
			sounds.Play_sound(static_cast<int>(SoundType::GetTreasure));
			map.map[i].type = Type::ROAD;
			Get_treasure[0] = true;
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::TREASURE_key)
		{
			sounds.Play_sound(static_cast<int>(SoundType::GetTreasure));
			map.map[i].type = Type::ROAD;
			Get_treasure[1] = true;
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::TREASURE_coin)
		{
			sounds.Play_sound(static_cast<int>(SoundType::GetTreasure));
			map.map[i].type = Type::ROAD;
			Get_treasure[2] = true;
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::TREASURE_dia)
		{
			sounds.Play_sound(static_cast<int>(SoundType::GetTreasure));
			map.map[i].type = Type::ROAD;
			Get_treasure[3] = true;
		}
	}
	if (current_state == State::TUTORIAL)
	{
		if (minsoo.position == map.map[485].position || minsoo.position == map.map[528].position || minsoo.position == map.map[571].position)
		{
			if (guard.guards.empty())
			{
				guard.guards.push_back(guard_info{ math::ivec2(12, 10), Direction::DOWN });
			}
		}
		else if (minsoo.position == map.map[495].position || minsoo.position == map.map[538].position || minsoo.position == map.map[581].position)
		{
			if (guard.guards.size() == 1)
			{
				guard.guards.push_back(guard_info{ math::ivec2(22, 14), Direction::UP });
			}
		}
	}
}

void Game::Draw_treasure()
{
	for (int i = 0; i < 4; i++)
	{
		if (Get_treasure[i] == true)
		{
			if (current_state != State::CLEAR)
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
			else
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
		if (guard.Is_trace_sommeone() == true && is_music_playing == false)
		{
			is_music_playing = true;
			is_chased_state = true;
			sounds.Set_music("assets/Siren.ogg", true);
			sounds.music.play();
		}
		if (guard.Is_trace_sommeone() == false && is_chased_state == true)
		{
			is_music_playing = false;
			is_chased_state = false;
		}

		if (guard.Is_trace_sommeone() == true && is_chased_state == false)
		{
			is_music_playing = false;
			is_chased_state = true;
		}

		if (guard.Is_trace_sommeone() == false && is_music_playing == false)
		{
			if (current_state >= State::TUTORIAL && current_state <= State::FLOOR_3)
			{
				is_music_playing = true;
				sounds.Set_music("assets/BasicBGM.ogg", true);
				sounds.music.play();
			}
		}
	}
}

void Game::Move_camera(math::vec2 position)
{
	math::vec2 target_pos = position;
	math::vec2 init_pos = new_pos;
	if (camera_move == true)
	{
		if (new_pos.x > target_pos.x)
		{
			new_pos.x -= 10 * doodle::DeltaTime;
		}
		if (new_pos.x < target_pos.x)
		{
			new_pos.x += 10 * doodle::DeltaTime;
		}

		if (new_pos.y > target_pos.y)
		{

			new_pos.y = (target_pos.y - init_pos.y) / (target_pos.x - init_pos.x) * (new_pos.x - init_pos.x) + init_pos.y;
		}
		if (new_pos.y < target_pos.y)
		{

			new_pos.y = (target_pos.y - init_pos.y) / (target_pos.x - init_pos.x) * (new_pos.x - init_pos.x) + init_pos.y;
		}
		camera.Update(new_pos);
		if (new_pos.x >= target_pos.x && new_pos.y >= target_pos.y)
		{
			if (start_camera_count == false)
			{
				curr_timer = timer;
				start_camera_count = true;
			}
			double Target_time = 2;
			if (curr_timer - timer > Target_time)
			{
				camera_move = false;
				new_pos = minsoo.Get_position();
				camera.Update(new_pos);
			}
		}
	}
}

void Game::Reset()
{
	timer = total_time;
	doodle::ElapsedTime = 0;
	offset = 0;
	speed = 10;
	is_exit = false;
	radar_start = false;
	make_radar_big = false;
	is_in_guard_sight = false;
	is_music_playing = false;
	is_chased_state = false;
	is_played_bite = false;
	is_paused = false;
	camera_move = false;
	curr_timer = 0;
	start_camera_count = false;
	is_minsoo_move = false;
	map.Set_up(curr_level);
	minsoo.Set_up();
	guard.Set_up(curr_level);
	Ending_timer = Minsoo_UPUP.target_time * 6;//dkqQKqkqh apfhd
	Ending_credit_ypos = doodle::Height;
	if (level_clear[1] == false)
	{
		Get_treasure[0] = false;
		Get_treasure[1] = false;
	}
	
	
	if (level_clear[2] == false)
	{
		Get_treasure[2] = false;
		Get_treasure[3] = false;
	}


	minsoo.direction = Direction::DOWN;
	for (int i = 0; i < map.map.size(); i++)
	{
		if (map.map[i].type == Type::RADAR)
		{
			new_pos = map.map[i].position;
		}
	}
}

bool Game::Check(doodle::KeyboardButtons doodleButton) // get keyboard key and check whether the direction minsoo want to go is wall or road
{
	math::vec2 position = minsoo.Get_position();
	switch (doodleButton)
	{
	case doodle::KeyboardButtons::Down:
		position.y += 1;
		break;
	case doodle::KeyboardButtons::Left:
	{
		position.x -= 1;
		break;
	}
	case doodle::KeyboardButtons::Right:
	{
		position.x += 1;
		break;
	}
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
		if (map.map[i].position == position && map.map[i].type == Type::WALL)
		{
			sounds.Play_sound(static_cast<int>(SoundType::CrashWall));
			return true;
		}
	}
	if (cheat_Z == true)
	{
		return false;
	}

	return false;
}

bool Game::Check_guard(int index)  // change sight if guard direction is toward the wall
{

	switch (guard.guards[index].direction)
	{
	case Direction::UP:   //move up
	{
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].position.x && i.position.y == guard.guards[index].position.y - 1 && i.type == Type::WALL)
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
			if (i.position.x == guard.guards[index].position.x && i.position.y == guard.guards[index].position.y + 1 && i.type == Type::WALL)
			{
				guard.Change_sight(map, index);
				return true;
			}
		}
		break;
	case Direction::RIGHT:   //move right
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].position.x + 1 && i.position.y == guard.guards[index].position.y && i.type == Type::WALL)
			{
				guard.Change_sight(map, index);
				return true;
			}
		}
		break;
	case Direction::LEFT:   //move left
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].position.x - 1 && i.position.y == guard.guards[index].position.y && i.type == Type::WALL)
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
	for (auto& Guard : guard.guards)
	{
		math::vec2 pos;
		pos = minsoo.Get_position() - Guard.position;
		double difference = abs(pos.x) + abs(pos.y);
		if (difference <= 0.5)
		{
			sounds.Stop_sound();
			sounds.music.stop();
			is_music_playing = false;
			sounds.Play_sound(static_cast<int>(SoundType::Meow));
			minsoo.is_dead = true;
			current_state = State::GAME_OVER;
		}
	}
}

void Game::Sight_check(int index)
{
	switch (guard.guards[index].direction)
	{
	case Direction::UP:
	{
		for (auto& j : map.map)
		{
			if (guard.guards[index].position.x == j.position.x && guard.guards[index].position.y - 1 == j.position.y && j.type == Type::WALL)
			{
				guard.Change_sight(map, index);
			}
		}
	}
	break;
	case Direction::DOWN:
	{
		for (auto& j : map.map)
		{
			if (guard.guards[index].position.x == j.position.x && guard.guards[index].position.y + 1 == j.position.y && j.type == Type::WALL)
			{
				guard.Change_sight(map, index);
			}
		}
	}
	break;
	case Direction::RIGHT:
	{
		for (auto& j : map.map)
		{
			if (guard.guards[index].position.x + 1 == j.position.x && guard.guards[index].position.y == j.position.y && j.type == Type::WALL)
			{
				guard.Change_sight(map, index);
			}
		}
	}
	break;
	case Direction::LEFT:
	{
		for (auto& j : map.map)
		{
			if (guard.guards[index].position.x - 1 == j.position.x && guard.guards[index].position.y == j.position.y && j.type == Type::WALL)
			{
				guard.Change_sight(map, index);
			}
		}
	}
	break;

	}
}

void Game::set_direction(math::vec2 position, int index)
{
	if (position.x == -1)
	{
		guard.guards[index].direction = Direction::RIGHT;
	}
	if (position.x == 1)
	{
		guard.guards[index].direction = Direction::LEFT;
	}
	if (position.y == -1)
	{
		guard.guards[index].direction = Direction::DOWN;
	}
	if (position.y == 1)
	{
		guard.guards[index].direction = Direction::UP;
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
				if (map.map[i].position == minsoo.Get_position())
				{
					sounds.Play_sound(static_cast<int>(SoundType::PutItem));
					map.map[i].type = Type::DOG_CHEW;
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
				if (map.map[i].position == minsoo.Get_position())
				{
					sounds.Play_sound(static_cast<int>(SoundType::PutItem));
					if (map.map[i].position == exit_pos)
					{
						is_exit = true;
					}
					minsoo.explode_count = 3;
					map.map[i].type = Type::BOMB;
					minsoo.bomb_item--;

				}
			}
		}
	}
	break;

	}
}

void Game::Radar_obtain()	//What is this??????? Why int item num=1?
{
	if (is_radar_obtained == true)
	{
		if (current_state == State::TUTORIAL)
		{
			map.map[826].type = Type::EXIT;
			exit_pos = map.map[826].position;
			is_radar_obtained = false;
			radar_start = true;
			guard.guards.push_back(guard_info{ math::ivec2(30, 19), Direction::LEFT ,"Ruby" }); //minsu start pos
			camera_move = true;
		}
		else
		{
			int item_num = 1;
			math::ivec2 pos(0, 0);
			for (auto& m : map.map)
			{
				if (m.type == Type::RADAR)
				{
					pos = m.position;
				}
			}
			while (item_num > 0)
			{
				switch (curr_level)
				{
					case static_cast<int>(State::FLOOR_1) :
						case static_cast<int>(State::FLOOR_2) :
					{
						pos = math::ivec2(doodle::random(pos.x - 10, pos.x + 10), doodle::random(pos.y - 5, pos.y + 5));
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
					if (m.position == pos && m.type == Type::ROAD)
					{
						m.type = Type::EXIT;
						exit_pos = m.position;
						item_num--;
						is_radar_obtained = false;
						radar_start = true;
						switch (curr_level)
						{
							case static_cast<int>(State::FLOOR_1) :
							{
								guard.guards.push_back(guard_info{ math::ivec2(30, 14), Direction::LEFT ,"Ruby" }); //ruby start pos
								break;
							}
							case static_cast<int>(State::FLOOR_2) :
							{
								guard.guards.push_back(guard_info{ math::ivec2(30, 12), Direction::LEFT ,"Ruby" }); //ruby start pos
								break;
							}
							case static_cast<int>(State::FLOOR_3) :
							{
								guard.guards.push_back(guard_info{ math::ivec2(39, 21), Direction::LEFT ,"Ruby" }); //ruby start pos
								break;
							}
						}
						camera_move = true;
					}
				}
			}
		}
	}
}

void Game::Draw_radar()
{
	if (radar_start == true && is_exit == false)
	{
		if (Get_count() == 0)
		{
			speed = 25;
		}
		else
		{
			speed = 20. / Get_count();
		}

		double off_spd = offset * speed;
		draw_image(map.Radar, Width * 0.035 + (off_spd / 2), Height * 0.80625 + (off_spd / 2), doodle::Width * 0.083 - off_spd, doodle::Height * 0.125 - off_spd);
		if (make_radar_big == false)
		{
			off_spd = ++offset * speed;
			if (off_spd > 50)
			{
				offset = 50 / speed;
				make_radar_big = true;
			}
		}
		else if (make_radar_big == true)
		{
			off_spd = --offset * speed;
			if (off_spd < 0)
			{
				offset = 0;
				make_radar_big = false;
			}
		}
	}
}

double Game::Get_count()
{
	int count{ 1 };
	math::vec2 minsu_pos = minsoo.target_pos;
	math::vec2 exit_minsu = exit_pos - minsu_pos;

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
					if (exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = count, row = 0; row < count; row++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}

			if (count >= exit_minsu.y)
			{
				for (double column = 0, row = exit_minsu.y; column <= exit_minsu.y; column++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = 0, row = count; column <= count; column++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y + row })
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
					if (exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = count, row = 0; row < count; row++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			if (count >= -exit_minsu.y)
			{
				for (double column = 0, row = -exit_minsu.y; column <= -exit_minsu.y; column++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = 0, row = count; column <= count; column++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x + column ,minsu_pos.y - row })
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
					if (exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = count, row = 0; row < count; row++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			if (count >= exit_minsu.y)
			{
				for (double column = 0, row = exit_minsu.y; column <= exit_minsu.y; column++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = 0, row = count; column <= count; column++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y + row })
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
					if (exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = count, row = 0; row < count; row++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			if (count >= -exit_minsu.y)
			{
				for (double column = 0, row = -exit_minsu.y; column <= -exit_minsu.y; column++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (double column = 0, row = count; column <= count; column++)
				{
					if (exit_pos == math::vec2{ minsu_pos.x - column ,minsu_pos.y - row })
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
	minsoo.Draw_minsu(camera, camera_move);
	if (current_state != State::TUTORIAL)
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

	if (current_state != State::TUTORIAL)
	{
		push_settings();
		set_outline_width(7);
		set_outline_color(0);
		draw_line(doodle::Width * 0.075, doodle::Height * 0.12, Width * 0.075 + Width * 0.05 * sin((PI / 50) * (100 - static_cast<double>(timer))), doodle::Height * 0.12 + Height * 0.075 * cos((PI) * ((static_cast<double>(timer)) / 50 - 1)));
		set_outline_width(3);
		set_outline_color(255, 0, 0);
		draw_line(doodle::Width * 0.075, doodle::Height * 0.12, Width * 0.075 + Width * 0.05 * sin((PI / 50) * (100 - static_cast<double>(timer))), doodle::Height * 0.12 + Height * 0.075 * cos((PI) * ((static_cast<double>(timer)) / 50 - 1)));

		set_font_size(30);
		pop_settings();
	}

	if (guard.Is_trace_sommeone() == true) // 한명이라도 따라오는애 있으면 
	{
		draw_image(Siren_sprite.image, Width / 2, 0, Siren_sprite.GetFrameSize().x, Siren_sprite.GetFrameSize().y, Siren_sprite.GetDrawPos().x, 0);
		Siren_sprite.Update();
	}


	Draw_treasure();
	if (current_state == State::TUTORIAL)
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
		is_music_playing = false;
		sounds.Play_sound(static_cast<int>(SoundType::SelectEffect));
		previous_state = current_state;
		current_state = State::PAUSE;
		pause_timer = doodle::ElapsedTime;
		is_paused = true;
	}

#ifdef DEBUG
	if (doodleButton == doodle::KeyboardButtons::Z)
	{
		cheat_Z = !cheat_Z;
	}
#else
#endif // DEBUG

	if (doodleButton == doodle::KeyboardButtons::Left || doodleButton == doodle::KeyboardButtons::Down || doodleButton == doodle::KeyboardButtons::Up || doodleButton == doodle::KeyboardButtons::Right)
	{
		if (Check(doodleButton) == false && camera_move != true)
		{
			if (is_minsoo_move == false)
			{
				sounds.Play_sound(static_cast<int>(SoundType::FootStep));
				minsoo.Set_position(doodleButton);

				is_minsoo_move = true;

				for (int i = 0; i < static_cast<int>(guard.guards.size()); i++)
				{
					if (guard.guards[i].is_trace == true && guard.guards[i].is_okay == true)
					{
						math::ivec2 curr_position = math::ivec2{ static_cast<int>(guard.guards[i].position.x) ,static_cast<int>(guard.guards[i].position.y) };

						if (path_finding<25, 43>(map, minsoo.target_pos, curr_position).empty() != true)
						{
							curr_position = path_finding<25, 43>(map, minsoo.target_pos, curr_position).back().pos;
						}

						curr_position = math::ivec2{ static_cast<int>(guard.guards[i].position.x) ,static_cast<int>(guard.guards[i].position.y) } - curr_position;  // 페스파인딩으로 다음 갈 곳에 대한 시야 변경
						set_direction(curr_position, i);
					}

					else
					{
						if (guard.guards[i].is_okay == true)
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
		is_music_playing = false;
		sounds.Play_sound(static_cast<int>(SoundType::Win));
		current_state = State::CLEAR;
		level_clear[0] = true;
		level_clear[1] = true;

		Get_treasure[0] = true;
		Get_treasure[1] = true;
		Get_treasure[2] = true;
		Get_treasure[3] = true;
	}
#endif
	if (doodleButton == doodle::KeyboardButtons::L)
	{
		current_state = State::ENDING;
	}
}


void Game::Change_sight()
{
	if (is_minsoo_move == false)
	{
		for (int i = 0; i < static_cast<int>(guard.guards.size()); i++)
		{
			if (Check_guard(i) == false)
			{
				if (minsoo.movement % 5 == 0 && is_sight_changed == false)
				{
					if (guard.guards[i].is_trace == false && guard.guards[i].is_okay == true)
					{
						guard.Change_sight(map, i);
					}
				}
			}
		}
		is_sight_changed = true;
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
	if ((minsoo.position.x >= 3 && minsoo.position.x <= 7) && (minsoo.position.y >= 2 && minsoo.position.y <= 6))
	{
		if (Is_get_all_treasure() == true)
		{
			map.map[265].type = Type::NEXT;
		}
		else
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255);
			set_font_size(30);
			draw_text("Move With Keyboard Arrows.\nCollect " + to_string(4 - Treasure_count()) + " More Treasures!", Width * 0.2, Height * 0.15);
			pop_settings();
		}
	}
	else if (minsoo.position.y >= 9 && minsoo.position.y <= 15)
	{
		if (minsoo.position.x >= 7 && minsoo.position.x <= 10)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255);
			set_font_size(30);
			draw_text("Guards Will Chase If\nMinsoo Is In Sight.", Width * 0.2, Height * 0.15);
			pop_settings();
		}
		else if (minsoo.position.x >= 12 && minsoo.position.x <= 14)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255, 0, 0);
			set_font_size(30);
			draw_text("Run!", Width * 0.45, Height * 0.3);
			pop_settings();
		}
		else if (minsoo.position.x > 14 && minsoo.position.x < 18 && minsoo.chew_item >= 3)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255, 255, 0);
			set_font_size(30);
			draw_text("Use The Dog Chew!\nPress: 1", Width * 0.3, Height * 0.3);
			pop_settings();
		}
		else if (minsoo.position.x >= 18 && minsoo.position.x < 21)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255);
			set_font_size(30);
			draw_text("After 3 Steps, The Guards Will\nStart Roaming Around.", Width * 0.2, Height * 0.15);
			pop_settings();
		}
		else if (minsoo.position.x >= 22 && minsoo.position.x <= 24)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255, 0, 0);
			set_font_size(30);
			draw_text("Run!", Width * 0.45, Height * 0.3);
			pop_settings();
		}
		else if (minsoo.position.x > 24 && minsoo.position.x <= 27 && minsoo.chew_item >= 2)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255, 255, 0);
			set_font_size(30);
			draw_text("Now You Know What To Do.\nPress: 1", Width * 0.3, Height * 0.3);
			pop_settings();
		}
		else if (minsoo.position.x > 27 && minsoo.position.x <= 31)
		{
			switch (minsoo.chew_item)
			{
			case 3:
			case 2:
			{
				push_settings();
				set_outline_width(3);
				set_outline_color(0);
				set_font_fade_out_interval(0.45, 0.55);
				set_font_backdrop_fade_out_interval(0.6, 1.0);
				set_fill_color(255);
				set_font_size(30);
				draw_text("Use " + to_string(minsoo.chew_item - 1) + " More Dog Chew!\nPress: 1", Width * 0.2, Height * 0.15);
				pop_settings();
				break;
			}
			default: map.map[590].type = Type::NEXT; break;
			}
		}
	}
	else if (minsoo.position.y >= 18 && minsoo.position.y <= 20)
	{
		if (is_bomb_set == true && minsoo.explode_count != 0)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255);
			set_font_size(30);
			draw_text(to_string(minsoo.explode_count) + " More Moves\nUntil The Bomb Exploads!", Width * 0.2, Height * 0.15);
			pop_settings();
		}
		else if (minsoo.explode_count == 0)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255, 255, 0);
			set_font_size(30);
			draw_text("Go Down The Stairs!", Width * 0.2, Height * 0.15);
			pop_settings();
		}
		else if (minsoo.position.x > 26 && minsoo.position.x <= 31)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255);
			set_font_size(30);
			draw_text("If The Radar Item Is Obtained,\nRuby Will Chase.", Width * 0.2, Height * 0.15);
			pop_settings();
		}
		else if (minsoo.position.x >= 21 && minsoo.position.x <= 25 && minsoo.chew_item >= 1)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255, 255, 0);
			set_font_size(30);
			draw_text("Use The Last Dog Chew!\nPress: 1", Width * 0.2, Height * 0.15);
			pop_settings();
		}
		else if (minsoo.position.x > 13 && minsoo.position.x <= 20)
		{
			push_settings();
			set_outline_width(3);
			set_outline_color(0);
			set_font_fade_out_interval(0.45, 0.55);
			set_font_backdrop_fade_out_interval(0.6, 1.0);
			set_fill_color(255);
			set_font_size(30);
			draw_text("The Radar Will Expand And Shrink\nFaster As The Hidden Exit Gets Near.", Width * 0.2, Height * 0.15);
			pop_settings();
		}
		else if (minsoo.position.x >= 8 && minsoo.position.x <= 13)
		{
			if ((minsoo.position.x > 8 && minsoo.position.x < 10) && minsoo.position.y > 18 && minsoo.position.y < 20)
			{
				push_settings();
				set_outline_width(3);
				set_outline_color(0);
				set_font_fade_out_interval(0.45, 0.55);
				set_font_backdrop_fade_out_interval(0.6, 1.0);
				set_fill_color(255, 255, 0);
				set_font_size(30);
				draw_text("Use The Bomb To Reveal The Exit!\nPress: 2\n", Width * 0.2, Height * 0.15);
				pop_settings();
				if (minsoo.bomb_item == 0)
				{
					is_bomb_set = true;
				}
			}
			else
			{
				push_settings();
				set_outline_width(3);
				set_outline_color(0);
				set_font_fade_out_interval(0.45, 0.55);
				set_font_backdrop_fade_out_interval(0.6, 1.0);
				set_fill_color(255);
				set_font_size(30);
				draw_text("The Radar Will Make Sound\nIf The Exit Is Near Enough.", Width * 0.2, Height * 0.15);
				pop_settings();
			}
		}
	}
}
//(3, 2)
//1111111111111111111111111111111111111111111
//1111111111111111111111111111111111111111111
//1110000311111111111111111111111111111111111
//1110000011111111111111111111111111111111111
//1113000011111111111111111111111111111111111
//1110000311111111111111111111111111111111111
//1113000411111111111111111111111111111111111
//1111111111111111111111111111111111111111111
//1111111111111111111111111111111111111111111
//1111111111100111111111111111111111111111111
//1111111111100111111111111111111111111111111
//1111111000000001110000000000000011111111111
//1111111000000001110000001110000011111111111
//1111111000000000000000001110000411111111111
//1111111111111111111100111111111111111111111
//1111111111111111111100111111111111111111111
//1111111111111111111111111111111111111111111
//1111111111111111111111111111111111111111111
//1111111100000110000001100020000011111111111
//1111111100000110011001100110000011111111111
//1111111100000000011000000110000011111111111
//1111111111111111111111111111111111111111111
//1111111111111111111111111111111111111111111
//1111111111111111111111111111111111111111111
//1111111111111111111111111111111111111111111