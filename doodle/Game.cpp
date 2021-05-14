#include"Game.h"
#include"Pathfinding.h"
#include<iostream>
using namespace doodle;

void Game::setup()
{
	//sounds.SetUpSound();
	current_state = State::START;
	map.setup();
	guard.setup();
}

void Game::Draw()
{
	switch (current_state)
	{
	case State::START:
		clear_background();
		doodle::draw_image(main_menu, 0, 0, Width, Height);
		switch (current_menu)
		{
		case static_cast<int>(MenuOption::start):	doodle::draw_image(start_button, 0, 0, Width, Height); break;
		case static_cast<int>(MenuOption::quit):	doodle::draw_image(quit_button, 0, 0, Width, Height); break;
		case static_cast<int>(MenuOption::credit):	doodle::draw_image(credit_button, 0, 0, Width, Height); break;
		}
		break;
	case State::CREDIT:
		doodle::draw_image(credit_menu, 0, 0, Width, Height); break;
	case State::IN_GAME:
		doodle::clear_background(0);
		map.draw(camera);
		guard.Draw_Sight(camera,map);
		guard.Draw_guard(camera);
		minsu.Draw_minsu(camera,camera_move);
		draw_text(std::to_string(treasure_count), 500, 80);

		push_settings();
		set_outline_width(5);
		set_outline_color(0);
		set_fill_color(255);
		draw_ellipse(200, 50, 100);
		set_outline_color(255,0,0);
		draw_line(200, 50, 200 + 50 * sin((PI / 50) * (100-static_cast<double>(timer))), 50 + 50 * cos((PI) * ((static_cast<double>(timer)) / 50 - 1)));
		pop_settings();

		set_font_size(30);
		draw_text("Chew item " + std::to_string(minsu.chew_item), 50, 200);
		doodle::draw_text("Bomb item " + std::to_string(minsu.bomb_item), 50, 250);
		draw_radar();
		pop_settings();
		if (guard.warning == true)
		{
			push_settings();
			set_fill_color(255, 0, 0,100);
			draw_rectangle(0, 0, Width, Height);
			doodle::pop_settings();
		}
		break;
	case State::CLEAR:
		push_settings();
		clear_background();
		set_fill_color(255, 0, 255);
		draw_image(clear_scene, 0, 0);// function for image movement
		draw_text("Level 1 Clear!", 30, 100);
		draw_text("score= " + std::to_string(score), 100, 600);
		pop_settings();
		break;
	case State::GAME_OVER:
		push_settings();
		clear_background();
		set_fill_color(255, 255, 0);
		draw_image(GameOver_scene, 0, 0,Width,Height);// function for image movement
		pop_settings();
		break;
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
				case static_cast<int>(MenuOption::start) :
				{
					Reset();
					current_state = State::IN_GAME;
					doodle::clear_background(0);
					break;
				}
				case static_cast<int>(MenuOption::quit) : doodle::close_window(); break;
				case static_cast<int>(MenuOption::credit) : current_state = State::CREDIT; break;
			}
		}
		if (doodleButton == doodle::KeyboardButtons::Up)
		{
			if (current_menu > static_cast<int>(MenuOption::start))
			{
				current_menu--;
			}
		}
		else if (doodleButton == doodle::KeyboardButtons::Down)
		{
			if (current_menu < static_cast<int>(MenuOption::credit))
			{
				current_menu++;
			}
		}
		break;
	case State::CREDIT:
		if (doodleButton == doodle::KeyboardButtons::Escape)
		{
			current_state = State::START;
		} break;
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
			if (check(doodleButton) == false)
			{
				minsu.set_position(doodleButton);
				for (int i = 0; i < static_cast<int>(guard.guards.size()); i++)
				{
					if (minsu.GetPosition() == guard.guards[i].position) //가드포지션이랑 민수포지션 같으면 게임오버
					{
						sounds.music.stop();
						current_state = State::GAME_OVER;
					}

					while (1)
					{
						if (check_guard(i) == false)
						{
							if (guard.guards[i].is_trace == true && guard.guards[i].is_okay == true) //시야안에 있는지없는지,개껌안먹었는지 ->있으면 페스파인딩
							{
								math::ivec2 curr_position = guard.guards[i].position;

								//template arguments = map height, map width
								
								guard.guards[i].position = path_finding<27, 81>(map, minsu.GetPosition(), (guard.guards[i].position)).back().pos;
								
								curr_position -= guard.guards[i].position;
								if (curr_position.x == -1)
								{
									guard.guards[i].direction = Direction::RIGHT;
								}
								if (curr_position.x == 1)
								{
									guard.guards[i].direction = Direction::LEFT;
								}
								if (curr_position.y == -1)
								{
									guard.guards[i].direction = Direction::DOWN;
								}
								if (curr_position.y == 1)
								{
									guard.guards[i].direction = Direction::UP;

								}
								if (path_finding<27, 81>(map, minsu.GetPosition(), (guard.guards[i].position)).empty()!=true)
								{
									curr_position = guard.guards[i].position - path_finding<27, 81>(map, minsu.GetPosition(), (guard.guards[i].position)).back().pos;
									if (curr_position.x == -1)
									{
										guard.guards[i].direction = Direction::RIGHT;
									}
									if (curr_position.x == 1)
									{
										guard.guards[i].direction = Direction::LEFT;
									}
									if (curr_position.y == -1)
									{
										guard.guards[i].direction = Direction::DOWN;
									}
									if (curr_position.y == 1)
									{
										guard.guards[i].direction = Direction::UP;
									}
								}

							}
							else if(guard.guards[i].is_okay == true)
							{
								guard.move(i);
								if (minsu.movement % 5 == 0)
								{
									guard.change_sight(map, i);  //5칸 움직이면 시야 바꾸기
								}
							}
							sight_check(i);  // 시야가 벽을 보고있는지 확인, 벽보고있으면 시야바꾸기
							for (auto& j : guard.guards)
							{
								if (j.is_trace == true)
								{
									j.trace_movement++;
								}
							}

							guard.set_sight();  // 지금 방향으로 시야 늘려서 보이기
							break;
						}

					}
				}
			}
			caught_by_guard();
		}
		set_item(doodleButton);
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
	case State::START:
		
		break;
	case State::IN_GAME:
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
			camera.Update(minsu.GetPosition());
			new_pos = minsu.GetPosition();
		}
		if (camera_move == true)
		{
			Ruby_camera();
		}
		if (guard.in_guard_sight(minsu) != -1)
		{
			guard.guards[guard.in_guard_sight(minsu)].is_trace = true;
			guard.guards[guard.in_guard_sight(minsu)].trace_movement = 0;
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
		guard.Guard_movement_update(map,minsu.movement);
		if (timer <= 0)
		{
			sounds.music.stop();
			current_state = State::GAME_OVER;
		}
		
		radar_obtain();
	
		break;
	case State::CLEAR:
		
		break;
	}
	

}

void Game::Reset()
{
	timer = total_time;
	doodle::ElapsedTime = 0;
	treasure_count = 0;
	offset = 0 ;
	speed = 10;
	is_exit = false;
	radar_start = false;
	make_radar_big = false;
	is_in_guard_sight = false;
	is_music_playing = false;
	is_chased_state = false;
	map.setup();
	minsu.setup();
	guard.setup();
	minsu.direction = Direction::DOWN;
	
}

bool Game::check(doodle::KeyboardButtons doodleButton)
{
	math::vec2 position = minsu.GetPosition();
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

	if(cheat_Z==true)
	{
		return false;
	}
	
	for (int i{ 0 };i<map.map.size();i++)
	{
		if (map.map[i].position == position && map.map[i].type == Type::wall)
		{
			return true;
		}
		else if (map.map[i].position == position && map.map[i].type == Type::radar)
		{
			map.map[i].type = Type::road;
			did_abtain_radar = true;
		}
		else if (map.map[i].position == position && map.map[i].type == Type::treasure)
		{
			map.map[i].type = Type::road;
			treasure_count++;
		}
		else if (map.map[i].position == position && map.map[i].type == Type::can_escape)
		{
			sounds.music.stop();
			current_state= State::CLEAR;
			return true;
		}
	}
	return false;
}

void Game::caught_by_guard()
{
	math::vec2 position = minsu.GetPosition() ;
	for (auto& i : guard.guards)
	{
		switch (i.direction)
		{
		case Direction::UP:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x && position.y == i.position.y -1.0)
			{
				sounds.music.stop();
				current_state = State::GAME_OVER;
			}
		}
		break;

		case Direction::DOWN:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x && position.y == i.position.y + 1.0)
			{
				sounds.music.stop();
				current_state = State::GAME_OVER;
			}
		}
		break;

		case Direction::RIGHT:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x + 1.0 && position.y == i.position.y )
			{
				sounds.music.stop();
				current_state = State::GAME_OVER;
			}
		}
		break;


		case Direction::LEFT:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x -1.0 && position.y == i.position.y)
			{
				sounds.music.stop();
				current_state = State::GAME_OVER;
			}
		}
		break;
		}

	}
}

bool Game::check_guard(int index)  // 가드가 벽을 보고있을때 시야방향 바꾸기
{

	switch (guard.guards[index].direction)
	{
	case Direction::UP:   //move up
	{
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].position.x && i.position.y == guard.guards[index].position.y - 1 && i.type == Type::wall)
			{
				guard.change_sight(map, index);
				return true;
			}
		}
	}
	break;
	case Direction::DOWN:   //move down
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].position.x && i.position.y == guard.guards[index].position.y + 1 && i.type == Type::wall)
			{
				guard.change_sight(map, index);
				return true;
			}
		}
		break;
	case Direction::RIGHT:   //move right
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].position.x + 1 && i.position.y == guard.guards[index].position.y && i.type == Type::wall)
			{
				guard.change_sight(map, index);
				return true;
			}
		}
		break;
	case Direction::LEFT:   //move left
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].position.x - 1 && i.position.y == guard.guards[index].position.y && i.type == Type::wall)
			{
				guard.change_sight(map, index);
				return true;
			}
		}
		break;
	}

	return false;
}

void Game::sight_check(int index)
{
	switch (guard.guards[index].direction)
	{
	case Direction::UP:
	{
		for (auto& j : map.map)
		{ 
			if (guard.guards[index].position.x == j.position.x && guard.guards[index].position.y - 1 == j.position.y && j.type == Type::wall)
			{
				guard.change_sight(map,index);
			}
		}
	}
	break;
	case Direction::DOWN:
	{
		for (auto& j : map.map)
		{
			if (guard.guards[index].position.x == j.position.x && guard.guards[index].position.y + 1 == j.position.y && j.type == Type::wall)
			{
				guard.change_sight(map, index);
			}
		}
	}
	break;
	case Direction::RIGHT:
	{
		for (auto& j : map.map)
		{
			if (guard.guards[index].position.x + 1 == j.position.x && guard.guards[index].position.y == j.position.y && j.type == Type::wall)
			{
				guard.change_sight(map, index);
			}
		}
	}
	break;
	case Direction::LEFT:
	{
		for (auto& j : map.map)
		{
			if (guard.guards[index].position.x - 1 == j.position.x && guard.guards[index].position.y == j.position.y && j.type == Type::wall)
			{
				guard.change_sight(map, index);
			}
		}
	}
	break;

	}
}

void Game::set_item(doodle::KeyboardButtons button)
{
	switch (button)
	{
	case doodle::KeyboardButtons::W:
	case doodle::KeyboardButtons::A:
	case doodle::KeyboardButtons::S:
	case doodle::KeyboardButtons::D:
	if (minsu.explode_count == 0)
	{
		for (int i{ 0 }; i < map.map.size(); i++)
		{
			if (map.map[i].type == Type::bomb)
			{
				if (is_exit == true)
				{
					map.map[i].type = Type::can_escape;
				}
				else
				{
					map.map[i].type = Type::road;
				}
			}
		}
	}
	break;
	case doodle::KeyboardButtons::_1:
	{
		if (minsu.chew_item > 0)
		{
			for (int i{ 0 }; i < map.map.size(); i++)
			{
				if (map.map[i].position == minsu.GetPosition())
				{
					map.map[i].type = Type::dog_chew;
					minsu.chew_item--;
				}
			}
		}
	}
	break;
	case doodle::KeyboardButtons::_2:
	{
		if (minsu.bomb_item > 0)
		{
			for (int i{ 0 }; i < map.map.size(); i++)
			{
				if (map.map[i].position == minsu.GetPosition())
				{
				
					
						if (map.map[i].type == Type::exit)
						{
							is_exit = true;
						}
						minsu.explode_count = 3;
						map.map[i].type = Type::bomb;
						minsu.bomb_item--;
					
				}
			}
		}
	}
	break;

	}
}

void Game::radar_obtain()
{
	if (did_abtain_radar == true)
	{
		int item_num = 1;
		while (item_num > 0)
		{
			math::ivec2 pos(doodle::random(0, 10), doodle::random(0, 10));
			for (auto& m : map.map)
			{
				if (m.position == pos && m.type == Type::road)
				{
					m.type = Type::exit;
					item_num--;
					did_abtain_radar = false;
					radar_start = true;
					guard.guards.push_back(guard_info{ math::ivec2(20, 19), Direction::LEFT ,"Ruby"}); //minsu start pos
					camera_move = true;
				}
			}
		}
	}
}

void Game::draw_radar()
{
	if (radar_start == true)
	{
		set_fill_color(0, 255, 0);
		draw_rectangle(100 * 9, 100 * 0, 100);

		math::ivec2 exit_pos;
		for (auto& m : map.map)
		{
			if (m.type == Type::exit)
			{
				exit_pos = m.position;
			}
		}
		
		
		if (get_count(exit_pos) == 0)
		{
			speed = 25;
		}
		else
		{
			speed = 20. / get_count(exit_pos);
		}

		double off_spd = offset * speed;
		draw_image(map.Radar, 100 * 9 + (off_spd / 2), 100 * 0 + (off_spd / 2), 100 - off_spd, 100 - off_spd);
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

void Game::Ruby_camera()
{
	if (camera_move == true)
	{
		if (new_pos.x > guard.guards.back().position.x)
		{
			new_pos.x -= 0.1;
		}
		if (new_pos.x < guard.guards.back().position.x)
		{
			new_pos.x += 0.1;
		}
		if (new_pos.y > guard.guards.back().position.y)
		{
			new_pos.y -= 0.1;
		}
		if (new_pos.y < guard.guards.back().position.y)
		{
			new_pos.y += 0.1;
		}
		camera.Update(new_pos);
	}
	if (new_pos.x >= guard.guards.back().position.x && new_pos.y >= guard.guards.back().position.y)
	{
		if (start_camera_count == false)
		{
			curr_timer = timer;
			start_camera_count = true;
		}
		double Target_time = 2;
		if ( curr_timer - timer  > Target_time)
		{
			camera_move = false;
		}
	}
}


int Game::get_count(math::ivec2 exit_pos)
{
	int count{ 1 };
	math::ivec2 minsu_pos = minsu.GetPosition();
	math::ivec2 exit_minsu = exit_pos - minsu_pos;

	if (exit_minsu.x == 0 && exit_minsu.y == 0)//exit
	{
		return 0;
	}
	else if (exit_minsu.x == 0 || exit_minsu.y == 0)//same x or y
	{
		int result = exit_minsu.y == 0 ? exit_minsu.x : exit_minsu.y;
		return abs(result);
	}
	else if (exit_minsu.x > 0 && exit_minsu.y > 0)//left top
	{
		while (1)
		{
			if (count >= exit_minsu.x)
			{
				for (int column = exit_minsu.x, row = 0; row < exit_minsu.x; row++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (int column = count, row = 0; row < count; row++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}

			if (count >= exit_minsu.y)
			{
				for (int column = 0, row = exit_minsu.y; column <= exit_minsu.y; column++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x + column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (int column = 0, row = count; column <= count; column++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x + column ,minsu_pos.y + row })
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
				for (int column = exit_minsu.x, row = 0; row < exit_minsu.x; row++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (int column = count, row = 0; row < count; row++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			if (count >= -exit_minsu.y)
			{
				for (int column = 0, row = -exit_minsu.y; column <= -exit_minsu.y; column++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x + column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (int column = 0, row = count; column <= count; column++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x + column ,minsu_pos.y - row })
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
				for (int column = -exit_minsu.x, row = 0; row < -exit_minsu.x; row++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (int column = count, row = 0; row < count; row++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			if (count >= exit_minsu.y)
			{
				for (int column = 0, row = exit_minsu.y; column <= exit_minsu.y; column++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x - column ,minsu_pos.y + row })
					{
						return count;
					}
				}
			}
			else
			{
				for (int column = 0, row = count; column <= count; column++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x - column ,minsu_pos.y + row })
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
				for (int column = -exit_minsu.x, row = 0; row < -exit_minsu.x; row++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (int column = count, row = 0; row < count; row++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			if (count >= -exit_minsu.y)
			{
				for (int column = 0, row = -exit_minsu.y; column <= -exit_minsu.y; column++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x - column ,minsu_pos.y - row })
					{
						return count;
					}
				}
			}
			else
			{
				for (int column = 0, row = count; column <= count; column++)
				{
					if (exit_pos == math::ivec2{ minsu_pos.x - column ,minsu_pos.y - row })
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

