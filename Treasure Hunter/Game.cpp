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
#include<iostream>
using namespace doodle;

void Game::Set_up()
{
	sounds.SetUpSound();
	current_state = State::SPLASH;
	map.Set_up(curr_level);
	guard.Set_up(curr_level);
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
		case (static_cast<int>(State::LEVEL_1)): doodle::draw_image(level1_button, 0, 0, Width, Height);
			break;
		case (static_cast<int>(State::LEVEL_2)): doodle::draw_image(level2_button, 0, 0, Width, Height);
			break;
		case (static_cast<int>(State::LEVEL_3)): doodle::draw_image(level3_button, 0, 0, Width, Height);
			break;
		}
		break;
	}

	case State::LEVEL_1:
	case State::LEVEL_2:
	case State::LEVEL_3:
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
		set_fill_color(255, 0, 255);
		draw_image(clear_scene, screen_pos, 0, Width , Height*1.2);// function for image movement
		draw_text(to_string(screen_pos), 30, 100);

		//draw_text("Level 1 Clear!", 30, 100);
		draw_text("score= " + std::to_string(score), 100, 600);
		pop_settings();
		break;
	}
	case State::GAME_OVER:
	{
		push_settings();
		clear_background();
		set_fill_color(255, 255, 0);
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
	case State::START:
	{
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
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
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				current_menu--;
			}
			else
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (current_menu < static_cast<int>(MenuOption::OPTION))
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				current_menu++;
			}
			else
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
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
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				current_volume += 25;
				sounds.music.setVolume(current_volume);
			}
			else
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (current_volume > 0)
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				current_volume -= 25;
				sounds.music.setVolume(current_volume);
			}
			else
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
			current_state = previous_state;
		}
	}
	break;
	case State::CREDIT:
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
			is_credit_done = false;
			current_state = previous_state;
		}
		else if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			if (is_credit_done == true)
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
			}
			else if (is_credit_done == false)
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				is_credit_done = !is_credit_done;
			}
		}
		break;
	case State::LEVEL_SELECT:  //todo 1레벨 클리어 해야지 2렙갈수있는거
	{
		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (curr_level > static_cast<int>(State::LEVEL_1))
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				curr_level--;
			}
			else
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (curr_level < static_cast<int>(State::LEVEL_3))
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				curr_level++;
			}
			else
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
			current_state = previous_state;
		}
		else if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.music.stop();
			is_music_playing = false;
			switch (curr_level)
			{
			case (static_cast<int>(State::LEVEL_1)):
			{
				if (unlock_level >= static_cast<int>(State::LEVEL_1))
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
					Reset();
					current_state = State::LEVEL_1;
				}
				else
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
				}
				break;
			}
			case (static_cast<int>(State::LEVEL_2)):
			{
				if (unlock_level >= static_cast<int>(State::LEVEL_2))
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
					Reset();
					current_state = State::LEVEL_2;
				}
				else
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
				}
				break;
			}

			case (static_cast<int>(State::LEVEL_3)):
			{
				if (unlock_level >= static_cast<int>(State::LEVEL_3))
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
					Reset();
					current_state = State::LEVEL_3;
				}
				else
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
				}
				break;
			}
			}
		}
	}
	break;

	case State::LEVEL_1:
	case State::LEVEL_2:
	case State::LEVEL_3:
	{
		Input_level(doodleButton);
		break;
	}
	case State::PAUSE:
	{
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			is_paused = false;
			current_state = previous_state;
			doodle::ElapsedTime = pause_timer;
		}
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));

			switch (current_menu)
			{
				case static_cast<int>(PauseOption::RESTART) :
				{
					switch (curr_level)
					{
						case static_cast<int>(State::LEVEL_1) :
						{
							current_state = State::LEVEL_1;
							break;
						}
						case static_cast<int>(State::LEVEL_2) :
						{
							current_state = State::LEVEL_2;
							break;
						}
						case static_cast<int>(State::LEVEL_3) :
						{
							current_state = State::LEVEL_3;
							break;
						}
					}
					Reset();
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
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				current_menu--;
			}
			else
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (current_menu < static_cast<int>(PauseOption::MAIN_MENU))
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
				current_menu++;
			}
			else
			{
				sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Right)
		{
			if (current_menu == static_cast<int>(PauseOption::SOUND))
			{
				if (current_volume < 100)
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
					current_volume += 25;
					sounds.music.setVolume(current_volume);
				}
				else
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
				}
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (current_menu == static_cast<int>(PauseOption::SOUND))
			{
				if (current_volume > 0)
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
					current_volume -= 25;
					sounds.music.setVolume(current_volume);
				}
				else
				{
					sounds.PlaySound(static_cast<int>(SoundType::SelectLimitEffect));
				}
			}
		}
		break;
	}
	case State::CLEAR:
	{
		sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
		current_state = State::START;
		if (unlock_level < static_cast<int>(State::LEVEL_3))
		{
			unlock_level++;
		}
		break;
	}
	case State::GAME_OVER:
	{
		sounds.PlaySound(static_cast<int>(SoundType::SelectEffect));
		is_played_bite = false;
		curr_level = static_cast<int>(State::LEVEL_1);
		current_state = State::START;
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
			sounds.SetMusic("assets/MainMenuBGM.ogg", true);
			sounds.music.play();
			is_music_playing = true;
		}
		break;
	}
	case State::LEVEL_SELECT:
	{
		if (is_music_playing == false)
		{
			sounds.SetMusic("assets/LevelSelectMenuBGM.ogg", true);
			sounds.music.play();
			is_music_playing = true;
		}
		break;
	}
	case State::LEVEL_1:
	case State::LEVEL_2:
	case State::LEVEL_3:
	{
		if (is_paused == false)
		{
			Update_level();
		}
		break;
	}
	case State::CLEAR:
	{
		screen_pos -= 500 * doodle::DeltaTime;
		if (screen_pos < 0)
		{
			screen_pos = 0;
		}
		break;
	}
	case State::GAME_OVER:
	{
		if (is_played_bite == false)
		{
			sounds.PlaySound(static_cast<int>(SoundType::Bite));
			is_played_bite = true;
		}
		break;
	}
	}
}

void Game::Update_level()
{
	timer = total_time - static_cast<int>(doodle::ElapsedTime);
	score = timer * (treasure_count + 1) * 10;
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

				if (path_finding<27, 81>(map, minsoo.target_pos, curr_position).empty() != true)
				{
					curr_position = path_finding<27, 81>(map, minsoo.target_pos, curr_position).back().pos;
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

	Set_Ingame_Music();

	guard.Guard_movement_update(exit_pos, map, minsoo.movement);
	if (timer < 20 && timer > 0)
	{
		if (Is_sound_playing() == false)
		{
			sounds.PlaySound(static_cast<int>(SoundType::TimerTic));
		}
	}
	else if (timer <= 0)
	{
		sounds.StopSound();
		sounds.PlaySound(static_cast<int>(SoundType::TimesUp));
		sounds.music.stop();
		is_music_playing = false;
		current_state = State::GAME_OVER;
	}
	if (radar_start == true)
	{
		if (Is_sound_playing() == false)
		{
			sounds.PlaySound(static_cast<int>(SoundType::Radar));
		}
	}
	for (auto i : guard.guards)
	{
		if (i.is_okay == false)
		{
			if (Is_sound_playing() == false)
			{
				sounds.PlaySound(static_cast<int>(SoundType::ChewingGum));
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
				sounds.PlaySound(static_cast<int>(SoundType::Explosion));
				if (is_exit == true)
				{
					map.map[i].type = Type::CAN_ESCAPE;
				}
				else
				{
					map.map[i].type = Type::BOMB_TO_ROAD;
				}
			}
			else
			{
				if (Is_sound_playing() == false)
				{
					sounds.PlaySound(static_cast<int>(SoundType::BombFuse));
				}
			}
		}

		if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::CAN_ESCAPE)
		{

			sounds.PlaySound(static_cast<int>(SoundType::Win));
			sounds.music.stop();
			current_state = State::CLEAR;
		}

		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::RADAR)
		{
			map.map[i].type = Type::ROAD;
			did_abtain_radar = true;
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::TREASURE_crown)
		{
			sounds.PlaySound(static_cast<int>(SoundType::GetTreasure));
			map.map[i].type = Type::ROAD;
			Get_treasure[0] = true;
			treasure_count++;
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::TREASURE_key)
		{
			sounds.PlaySound(static_cast<int>(SoundType::GetTreasure));
			map.map[i].type = Type::ROAD;
			Get_treasure[1] = true;
			treasure_count++;
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::TREASURE_coin)
		{
			sounds.PlaySound(static_cast<int>(SoundType::GetTreasure));
			map.map[i].type = Type::ROAD;
			Get_treasure[2] = true;
			treasure_count++;
		}
		else if (map.map[i].position == minsoo.Get_position() && map.map[i].type == Type::TREASURE_dia)
		{
			sounds.PlaySound(static_cast<int>(SoundType::GetTreasure));
			map.map[i].type = Type::ROAD;
			Get_treasure[3] = true;
			treasure_count++;
		}
	}
}

void Game::Draw_treasure()
{
	for(int i=0; i<4; i++)
	{
		if(Get_treasure[i] == true)
		{
			switch(i)
			{
			case 0:
				{
					draw_image(Treasure_1_UI, 10,0, Width,Height);
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
}
//740 40
void Game::Set_Ingame_Music()
{
	if (minsoo.is_dead == false)
	{
		if (guard.Is_trace_sommeone() == true && is_music_playing == false)
		{
			is_music_playing = true;
			is_chased_state = true;
			sounds.SetMusic("assets/Siren.ogg", true);
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
			is_music_playing = true;
			sounds.SetMusic("assets/BasicBGM.ogg", true);
			sounds.music.play();
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
	treasure_count = 0;
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
	screen_pos = doodle::Width;
	start_camera_count = false;
	is_minsoo_move = false;
	map.Set_up(curr_level);
	minsoo.Set_up();
	guard.Set_up(curr_level);

	for(int i=0; i<4; i++)
	{
		Get_treasure[i] = false;
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

bool Game::Check(doodle::KeyboardButtons doodleButton)
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
			sounds.PlaySound(static_cast<int>(SoundType::CrashWall));
			return true;
		}
	}
	if (cheat_Z == true)
	{
		return false;
	}

	return false;
}

bool Game::Check_guard(int index)  // 가드가 벽을 보고있을때 시야방향 바꾸기
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
			sounds.PlaySound(static_cast<int>(SoundType::Meow));
			sounds.music.stop();
			is_music_playing = false;
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
					sounds.PlaySound(static_cast<int>(SoundType::PutItem));
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
					sounds.PlaySound(static_cast<int>(SoundType::PutItem));
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

// 레이더 빨라지는게 어딘지는 모르겠는데 sounds.sounds[static_cast<int>(SoundType::Radar)].setVolume() 이런식으로 조정하면 될듯
void Game::Radar_obtain()
{
	if (did_abtain_radar == true)
	{
		int item_num = 1;
		while (item_num > 0)
		{
			math::ivec2 pos(doodle::random(0, 10), doodle::random(0, 10));
			for (auto& m : map.map)
			{
				if (m.position == pos && m.type == Type::ROAD)
				{
					m.type = Type::EXIT;
					exit_pos = m.position;
					item_num--;
					did_abtain_radar = false;
					radar_start = true;
					guard.guards.push_back(guard_info{ math::ivec2(39, 21), Direction::LEFT ,"Ruby" }); //minsu start pos
					camera_move = true;
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
	doodle::draw_image(Sight_limit, (minsoo.Get_position().x + camera.Get_position().x-1), (minsoo.Get_position().y + camera.Get_position().y-20),doodle::Width,doodle::Height);
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

	push_settings();
	set_outline_width(5);
	set_outline_color(0);
	set_fill_color(255);
	
	set_outline_color(255, 0, 0);
	draw_line(doodle::Width* 0.07, doodle::Height * 0.12, Width *0.07 + Width*0.05 * sin((PI / 50) * (100 - static_cast<double>(timer))), doodle::Height * 0.12 + Height*0.075 * cos((PI) * ((static_cast<double>(timer)) / 50 - 1)));

	set_font_size(30);
	pop_settings();

	if (guard.Is_trace_sommeone() == true) // 한명이라도 따라오는애 있으면 
	{
		draw_image(Siren_sprite.image, Width/2,0, Siren_sprite.GetFrameSize().x, Siren_sprite.GetFrameSize().y, Siren_sprite.GetDrawPos().x, 0);
		Siren_sprite.Update();
	}


	Draw_treasure();
}

//void Game::Draw_level2()
//{
//	doodle::clear_background(0);
//	map.Draw(camera);
//	guard.Draw_guard(camera);
//	guard.Draw_sight(camera, map);
//	minsoo.Draw_minsu(camera, camera_move);
//	draw_text(std::to_string(treasure_count), 500, 80);
//
//	push_settings();
//	set_outline_width(5);
//	set_outline_color(0);
//	set_fill_color(255);
//	draw_ellipse(200, 50, 100);
//	set_outline_color(255, 0, 0);
//	draw_line(200, 50, 200 + 50 * sin((PI / 50) * (100 - static_cast<double>(timer))), 50 + 50 * cos((PI) * ((static_cast<double>(timer)) / 50 - 1)));
//
//	set_font_size(30);
//
//	pop_settings();
//	if (guard.Is_trace_sommeone() == true) // 한명이라도 따라오는애 있으면 
//	{
//		push_settings();
//		if (timer % 2 == 0)  // 1초마다 화면 빨간색 넣기
//		{
//			set_fill_color(255, 0, 0, 100);
//			draw_rectangle(0, 0, Width, Height);
//		}
//		doodle::pop_settings();
//	}
//}
//
//void Game::Draw_level3()
//{
//	doodle::clear_background(0);
//	map.Draw(camera);
//	guard.Draw_guard(camera);
//	guard.Draw_sight(camera, map);
//	minsoo.Draw_minsu(camera, camera_move);
//	draw_text(std::to_string(treasure_count), 500, 80);
//
//	push_settings();
//	set_outline_width(5);
//	set_outline_color(0);
//	set_fill_color(255);
//	draw_ellipse(200, 50, 100);
//	set_outline_color(255, 0, 0);
//	draw_line(200, 50, 200 + 50 * sin((PI / 50) * (100 - static_cast<double>(timer))), 50 + 50 * cos((PI) * ((static_cast<double>(timer)) / 50 - 1)));
//
//	set_font_size(30);
//
//
//	//Draw_radar();
//	pop_settings();
//	if (guard.Is_trace_sommeone() == true) // 한명이라도 따라오는애 있으면 
//	{
//		push_settings();
//		if (timer % 2 == 0)  // 1초마다 화면 빨간색 넣기
//		{
//			set_fill_color(255, 0, 0, 100);
//			draw_rectangle(0, 0, Width, Height);
//		}
//		doodle::pop_settings();
//	}
//}

void Game::Input_level(doodle::KeyboardButtons doodleButton)
{
	if (doodleButton == doodle::KeyboardButtons::Escape)
	{	
		sounds.StopSound();
		sounds.music.stop();
		is_music_playing = false;
		previous_state = current_state;
		current_state = State::PAUSE;
		current_menu = static_cast<int>(PauseOption::SOUND);
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
				sounds.PlaySound(static_cast<int>(SoundType::FootStep));
				minsoo.Set_position(doodleButton);

				is_minsoo_move = true;

				for (int i = 0; i < static_cast<int>(guard.guards.size()); i++)
				{
					if (guard.guards[i].is_trace == true && guard.guards[i].is_okay == true)
					{
						math::ivec2 curr_position = math::ivec2{ static_cast<int>(guard.guards[i].position.x) ,static_cast<int>(guard.guards[i].position.y) };

						if (path_finding<27, 81>(map, minsoo.target_pos, curr_position).empty() != true)
						{
							curr_position = path_finding<27, 81>(map, minsoo.target_pos, curr_position).back().pos;
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
		sounds.PlaySound(static_cast<int>(SoundType::Win));
		sounds.StopSound();
		sounds.music.stop();
		current_state = State::CLEAR;
		is_music_playing = false;
	}
#endif
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

bool Game::Is_sound_playing()
{
	for (auto& s : sounds.sounds)
	{
		if (s.getStatus() == sf::SoundSource::Playing)
		{
			return true;
		}
	}
	return false;
}