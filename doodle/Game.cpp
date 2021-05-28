// todo : 개껌먹는상태일때도 시야첫번째칸 들어가면 죽는거 고치기

#include"Game.h"
#include"Pathfinding.h" //pathfinding logic
#include<iostream>
using namespace doodle;

void Game::Set_up()
{
	//sounds.SetUpSound();
	current_state = State::SPLASH;
	map.Set_up();
	guard.Set_up();
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
		doodle::draw_image(digipen_logo,0, 0);
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
			case static_cast<int>(MenuOption::QUIT) : doodle::draw_image(quit_button, 0, 0, Width, Height); break;
			case static_cast<int>(MenuOption::CREDIT) : doodle::draw_image(credit_button, 0, 0, Width, Height); break;
			case static_cast<int>(MenuOption::OPTION) : doodle::draw_image(option_button, 0, 0, Width, Height); break;
		}
		break;
	}

	case State::CREDIT:
	{
		doodle::draw_image(credit_menu, 0, 0, Width, Height);
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
		case 1: doodle::draw_image(level1_button, 0, 0, Width, Height);
			break;
		case 2: doodle::draw_image(level2_button, 0, 0, Width, Height);
			break;
		case 3: doodle::draw_image(level3_button, 0, 0, Width, Height);
			break;
		}
		break;
	}

	case State::IN_GAME:
	{
		doodle::clear_background(0);
		map.Draw(camera);
		guard.Draw_guard(camera);
		guard.Draw_sight(camera, map);
		minsoo.Draw_minsu(camera, camera_move);
		draw_text(std::to_string(treasure_count), 500, 80);

		push_settings();
		set_outline_width(5);
		set_outline_color(0);
		set_fill_color(255);
		draw_ellipse(200, 50, 100);
		set_outline_color(255, 0, 0);
		draw_line(200, 50, 200 + 50 * sin((PI / 50) * (100 - static_cast<double>(timer))), 50 + 50 * cos((PI) * ((static_cast<double>(timer)) / 50 - 1)));
		pop_settings();

		set_font_size(30);
#ifdef _DEBUG
		draw_text("Chew item " + std::to_string(minsoo.chew_item), 50, 200);
		doodle::draw_text("Bomb item " + std::to_string(minsoo.bomb_item), 50, 250);
#endif // DEBUG

		//Draw_radar();
		pop_settings();
		if (guard.Is_trace_sommeone() == true) // 한명이라도 따라오는애 있으면 
		{
			push_settings();
			if (timer % 2 == 0)  // 1초마다 화면 빨간색 넣기
			{
				set_fill_color(255, 0, 0, 100);
				draw_rectangle(0, 0, Width, Height);
			}
			doodle::pop_settings();
		}
		break;
	}
	case State::CLEAR:
	{
		push_settings();
		clear_background();
		set_fill_color(255, 0, 255);
		draw_image(clear_scene, 0, 0);// function for image movement
		draw_text("Level 1 Clear!", 30, 100);
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
	case State::START:
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			switch (current_menu)
			{
				case static_cast<int>(MenuOption::START) :
				{
					current_state = State::LEVEL_SELECT;
					doodle::clear_background(0);
					break;
				}
				case static_cast<int>(MenuOption::OPTION) :
				{
					current_state = State::OPTION;
					break;
				}
				case static_cast<int>(MenuOption::QUIT) : doodle::close_window(); break;
					case static_cast<int>(MenuOption::CREDIT) : current_state = State::CREDIT; break;
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (current_menu > static_cast<int>(MenuOption::START))
			{
				current_menu--;
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (current_menu < static_cast<int>(MenuOption::OPTION))
			{
				current_menu++;
			}
		}
		break;
	case State::OPTION:
	{
		if (doodleButton == doodle::KeyboardButtons::Right)
		{
			if (current_volume < 100)
			{
				current_volume += 25;
				sounds.music.setVolume(current_volume);
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Left)
		{
			if (current_volume > 0)
			{
				current_volume -= 25;
				sounds.music.setVolume(current_volume);
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			current_state = State::START;
		}
	}
	break;
	case State::CREDIT:
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			current_state = State::START;
		}
		break;

	case State::LEVEL_SELECT:  //todo 1레벨 클리어 해야지 2렙갈수있는거
	{
		if (doodleButton == doodle::KeyboardButtons::Enter)
		{
			switch (curr_level)
			{
			case 1:
			{
				Reset();
				current_state = State::IN_GAME;
				break;
			}
			case 2:
			{
				Reset();
				current_state = State::IN_GAME;
				break;
			}

			case 3:
			{
				Reset();
				current_state = State::IN_GAME;
				break;
			}
			}
		}
		//if (doodleButton == doodle::KeyboardButtons::Up)
		//{

		//}
		//else if (doodleButton == doodle::KeyboardButtons::Down)
		//{

		//}
	}
	break;

	case State::IN_GAME:
	{
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			sounds.music.stop();
			current_state = State::START;
		}
		if (doodleButton == doodle::KeyboardButtons::Z)
		{
			cheat_Z = !cheat_Z;
		}
		if (doodleButton == doodle::KeyboardButtons::A || doodleButton == doodle::KeyboardButtons::S || doodleButton == doodle::KeyboardButtons::W || doodleButton == doodle::KeyboardButtons::D)
		{
			if (Check(doodleButton) == false && camera_move != true)
			{
				if (is_minsoo_move == false)
				{
					minsoo.Set_position(doodleButton);

					is_minsoo_move = true;

					if (is_sight_changed == true)
					{
						is_sight_changed = false;
					}
				for (int i = 0; i < static_cast<int>(guard.guards.size()); i++)
				{
					while (true)
					{
						if (Check_guard(i) == false)
						{
							if (guard.guards[i].is_trace == true && guard.guards[i].is_okay == true) //시야안에 있는지없는지,개껌안먹었는지 ->있으면 페스파인딩
							{

								math::ivec2 curr_position = math::ivec2{ guard.guards[i].position.x , guard.guards[i].position.y };
								if (curr_position != minsoo.Get_position())
								{
									guard.guards[i].position = path_finding<27, 81>(map, minsoo.target_pos, curr_position).back().pos;

									curr_position -= math::ivec2{ guard.guards[i].position.x , guard.guards[i].position.y };  // 페스파인딩으로 다음 갈 곳에 대한 시야 변경
									set_direction(curr_position, i);
									curr_position = math::ivec2{ guard.guards[i].position.x , guard.guards[i].position.y };
									if (path_finding<27, 81>(map, minsoo.Get_position(), curr_position).empty() != true)
									{
										curr_position = math::ivec2{ guard.guards[i].position.x , guard.guards[i].position.y } - path_finding<27, 81>(map, minsoo.Get_position(), curr_position).back().pos;
										set_direction(curr_position, i);
									}
								}

							}

							if (guard.guards[i].is_okay == true)
							{
								guard.Set_position(i);
							}
							Sight_check(i);  // 시야가 벽을 보고있는지 확인, 벽보고있으면 시야바꾸기

							for (auto& j : guard.guards)
							{
								if (j.is_trace == true)
								{
									j.trace_movement++;
								}
							}
							break;
						}					
					   }
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
			sounds.music.stop();
			current_state = State::CLEAR;
		}
#endif
		break;
	}
	case State::CLEAR:
	{
		current_state = State::START;
		break;
	}
	case State::GAME_OVER:
	{
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
		static double splash_timer = 4;
		splash_timer -= doodle::DeltaTime;
		if (splash_timer < 0)
		{
			current_state = State::START;
		}
		break;
	}

	case State::START:
	{
		break;
	}
	case State::IN_GAME:
	{
		if (is_music_playing == false)
		{
			sounds.music.stop();
			if (is_in_guard_sight == true)
			{
				sounds.SetMusic("assets/Siren.ogg", true);
				sounds.music.play();
				is_music_playing = true;
			}
			else
			{
				sounds.SetMusic("assets/BasicBGM.ogg", true);
				sounds.music.play();
				is_music_playing = true;
			}
		}
		timer = total_time - static_cast<int>(doodle::ElapsedTime);
		score = timer * (treasure_count + 1) * 10;
		if (camera_move == false)
		{
			camera.Update(minsoo.Get_position());
			minsoo.Update_position(is_minsoo_move);
			guard.Update_position();
			guard.Set_sight();
			Collision_check();
			Change_sight();
		}
		if (camera_move == true)
		{
			Move_camera(guard.guards.back().position);
		}

		if (guard.In_guard_sight(minsoo) != -1) //따라오고있는애가 한명은있다
		{
			guard.guards[guard.In_guard_sight(minsoo)].is_trace = true;
			guard.guards[guard.In_guard_sight(minsoo)].trace_movement = 0;
			if (is_chased_state == false)
			{
				is_music_playing = false;
			}
			is_in_guard_sight = true;
			is_chased_state = true;
		}
		else // 시야에 안잡히면
		{
			if (is_chased_state == true)
			{
				is_music_playing = false;
			}
			is_in_guard_sight = false;
			is_chased_state = false;
		}
		guard.Guard_movement_update(map, minsoo.movement);
		if (timer <= 0)
		{
			sounds.music.stop();
			current_state = State::GAME_OVER;
		}

		Radar_obtain();

		break;
	}
	case State::CLEAR:

		break;
	}


}
void Game::Move_camera(math::vec2 position)
{
	math::vec2 target_pos = position;
	math::vec2 init_pos = new_pos;

	if (camera_move != true)
	{
		if (new_pos.x > target_pos.x)
		{
			new_pos.x -= doodle::DeltaTime;
			if (new_pos.x <= target_pos.x)
			{
				new_pos = minsoo.Get_position();
			}
		}
		else if (new_pos.x < target_pos.x)
		{
			new_pos.x += doodle::DeltaTime;
			if (new_pos.x >= target_pos.x)
			{
				new_pos = minsoo.Get_position();

			}
		}

		else if (new_pos.y > target_pos.y)
		{
			new_pos.y -= doodle::DeltaTime;
			if (new_pos.y <= target_pos.y)
			{
				new_pos = minsoo.Get_position();

			}
			//new_pos.y =  (target_pos.y - init_pos.y)/(target_pos.x - init_pos.x)  * (new_pos.x - init_pos.x) + init_pos.y;
		}
		else if (new_pos.y < target_pos.y)
		{
			new_pos.y += doodle::DeltaTime;
			if (new_pos.y >= target_pos.y)
			{
				new_pos = minsoo.Get_position();
			}
			//new_pos.y = (target_pos.y - init_pos.y) / (target_pos.x - init_pos.x) * (new_pos.x - init_pos.x) + init_pos.y;
		}
		//std::cout << new_pos.x << "     " << new_pos.y << std::endl;
		camera.Update(new_pos);

	}
	//루비 먹었을때
		if (camera_move == true)
		{
			if (new_pos.x > target_pos.x)
			{
				new_pos.x -= 10*doodle::DeltaTime;
			}
			if (new_pos.x < target_pos.x)
			{
				new_pos.x += 10 * doodle::DeltaTime;
			}

			if (new_pos.y > target_pos.y)
			{
				
				new_pos.y =  (target_pos.y - init_pos.y)/(target_pos.x - init_pos.x)  * (new_pos.x - init_pos.x) + init_pos.y;
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
void Game::Collision_check()
{
	for (auto& Guard : guard.guards)
	{
		if (minsoo.Get_position() == Guard.position) //가드포지션이랑 민수포지션 같으면 게임오버
		{
			sounds.music.stop();
			current_state = State::GAME_OVER;
		}
		math::vec2 pos;
		pos = minsoo.Get_position() - Guard.position;
		double difference = abs(pos.x) + abs(pos.y);
		if (difference <= 0.5)
		{
			sounds.music.stop();
			current_state = State::GAME_OVER;
		}
	}
}
void Game::Change_sight()
{
	if (is_minsoo_move == false)
	{
		if (minsoo.movement % 5 == 0 && is_sight_changed == false)
		{
			for (int i = 0; i < static_cast<int>(guard.guards.size()); i++)
			{
				guard.Change_sight(map, i);  
			}
			is_sight_changed = true;
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
	camera_move = false;
	curr_timer = 0;
	start_camera_count = false;
	is_minsoo_move = false;
	map.Set_up();
	minsoo.Set_up();
	guard.Set_up();
	minsoo.direction = Direction::DOWN;
	new_pos = minsoo.Get_position();
}

bool Game::Check(doodle::KeyboardButtons doodleButton)
{
	math::vec2 position = minsoo.Get_position();
	switch (doodleButton)
	{
	case doodle::KeyboardButtons::S:

		position.y += 1;

		break;
	case doodle::KeyboardButtons::A:
	{
		position.x -= 1;
		break;
	}
	case doodle::KeyboardButtons::D:
	{
		position.x += 1;
		break;
	}
	case doodle::KeyboardButtons::W:
	{
		position.y -= 1;
		break;
	}
	default:
		return true;
	}

	if (cheat_Z == true)
	{
		return false;
	}

	for (int i{ 0 }; i < map.map.size(); i++)
	{
		if (map.map[i].position == position && map.map[i].type == Type::WALL)
		{
			return true;
		}
		else if (map.map[i].position == position && map.map[i].type == Type::RADAR)
		{
			map.map[i].type = Type::ROAD;
			did_abtain_radar = true;
		}
		else if (map.map[i].position == position && map.map[i].type == Type::TREASURE)
		{
			map.map[i].type = Type::ROAD;
			treasure_count++;
		}
		else if (map.map[i].position == position && map.map[i].type == Type::CAN_ESCAPE)
		{
			sounds.music.stop();
			current_state = State::CLEAR;
			return true;
		}
	}
	return false;
}

void Game::Caught_by_guard_current(int index)
{
	if (minsoo.Get_position() == guard.guards[index].position) //가드포지션이랑 민수포지션 같으면 게임오버
	{
		sounds.music.stop();
		current_state = State::GAME_OVER;
	}
}

void Game::Caught_by_guard_nextmove()
{
	math::vec2 position = minsoo.Get_position();
	for (auto& i : guard.guards)
	{
		switch (i.direction)
		{
		case Direction::UP:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x && position.y == i.position.y - 1.0 && i.is_okay == true)
			{
				sounds.music.stop();
				current_state = State::GAME_OVER;
			}
		}
		break;

		case Direction::DOWN:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x && position.y == i.position.y + 1.0 && i.is_okay == true)
			{
				sounds.music.stop();
				current_state = State::GAME_OVER;
			}
		}
		break;

		case Direction::RIGHT:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x + 1.0 && position.y == i.position.y && i.is_okay == true)
			{
				sounds.music.stop();
				current_state = State::GAME_OVER;
			}
		}
		break;


		case Direction::LEFT:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x - 1.0 && position.y == i.position.y && i.is_okay == true)
			{
				sounds.music.stop();
				current_state = State::GAME_OVER;
			}
		}
		break;
		}

	}
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
	case doodle::KeyboardButtons::W:
	case doodle::KeyboardButtons::A:
	case doodle::KeyboardButtons::S:
	case doodle::KeyboardButtons::D:
		if (minsoo.explode_count == 0)
		{
			for (int i{ 0 }; i < map.map.size(); i++)
			{
				if (map.map[i].type == Type::BOMB)
				{
					if (is_exit == true)
					{
						map.map[i].type = Type::CAN_ESCAPE;
					}
					else
					{
						map.map[i].type = Type::ROAD;
					}
				}
			}
		}
		break;
	case doodle::KeyboardButtons::_1:
	{
		if (minsoo.chew_item > 0)
		{
			for (int i{ 0 }; i < map.map.size(); i++)
			{
				if (map.map[i].position == minsoo.Get_position())
				{
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


					if (map.map[i].type == Type::EXIT)
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
					item_num--;
					did_abtain_radar = false;
					radar_start = true;
					guard.guards.push_back(guard_info{ math::ivec2(20, 19), Direction::LEFT ,"Ruby" }); //minsu start pos
					camera_move = true;
				}
			}
		}
	}
}

void Game::Draw_radar()
{
	if (radar_start == true)
	{
		set_fill_color(0, 255, 0);
		draw_rectangle(100 * 9.0, 100 * 0, 100);

		math::ivec2 exit_pos;
		for (auto& m : map.map)
		{
			if (m.type == Type::EXIT)
			{
				exit_pos = m.position;
			}
		}


		if (Get_count(exit_pos) == 0)
		{
			speed = 25;
		}
		else
		{
			speed = 20. / Get_count(exit_pos);
		}

		double off_spd = offset * speed;
		draw_image(map.Radar, 100 * 9.0 + (off_spd / 2), 100 * 0 + (off_spd / 2), 100 - off_spd, 100 - off_spd);
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





double Game::Get_count(math::vec2 exit_pos)
{
	int count{ 1 };
	math::vec2 minsu_pos = minsoo.Get_position();
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

