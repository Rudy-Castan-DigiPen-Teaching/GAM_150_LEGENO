#include"Game.h"
#include<iostream>
void Game::setup()
{
	current_state = State::START;
	map.setup();
	guard.setup();
}

void Game::Draw()
{
	using namespace doodle;
	switch (current_state)
	{
	case State::START:
		push_settings();
		clear_background();
		set_fill_color(255, 255, 0);
		draw_text("Press S to start", 80, 150);
		draw_text("Press Q to quit", 80, 250);
		pop_settings();
		break;
	case State::IN_GAME:
		map.draw();
		guard.Draw_Sight();
		guard.Draw_guard();
		minsu.Draw_minsu();
		draw_text(std::to_string(timer), 80, 80);
		doodle::draw_text(std::to_string(treasure_count), 500, 80);
		break;
	case State::CLEAR:
		push_settings();
		clear_background();
		set_fill_color(255, 255, 0);
		//draw_image(clear_scene, 0, 0);
		draw_text("Level1 Clear!", 30, 30);
		draw_text("score= " + std::to_string(treasure_count), 30, 100);
		pop_settings();
		break;
	case State::GAME_OVER:
		push_settings();
		clear_background();
		set_fill_color(255, 255, 0);
		draw_text("You lose!", 30, 250);
		pop_settings();
		break;
	}
}

void Game::Get_inputkey(doodle::KeyboardButtons doodleButton)
{
	switch (current_state)
	{
	case State::START:
		if (doodleButton == doodle::KeyboardButtons::S)
		{
			Reset();
			current_state = State::IN_GAME;
		}
		if (doodleButton == doodle::KeyboardButtons::Q)
		{
			doodle::close_window();
		}
		break;
	case State::IN_GAME:
	{
		if (doodleButton == doodle::KeyboardButtons::A || doodleButton == doodle::KeyboardButtons::S || doodleButton == doodle::KeyboardButtons::W || doodleButton == doodle::KeyboardButtons::D)
		{
			if (check(doodleButton) == false)
			{
				minsu.set_position(doodleButton);
		
				for (int i = 0; i < static_cast<int>(guard.guards.size()); i++)
				{
					if (minsu.GetPosition() == guard.guards[i].position)
					{
						current_state = State::GAME_OVER;
					}

					while (1)
					{
						if (check_guard(i) == false)
						{
							guard.move(i);
							if (minsu.movement % 3 == 0)
							{
								
									guard.change_sight(map, i);
								
							}
							sight_check(i);
							break;
						}
						
					}
				}
			}
			caught_by_guard();
		}
		if (doodleButton == doodle::KeyboardButtons::R)
		{
			Reset();
		}
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
		timer = total_time - static_cast<int>(doodle::ElapsedTime);
		score = timer * (treasure_count + 1) * 100;

		if (timer <= 0)
		{
			current_state = State::GAME_OVER;
		}
		if (did_abtain_radar == true)
		{
			int item_num = 1;
			while (item_num > 0)
			{
				math::ivec2 pos(doodle::random(0, 30), doodle::random(0, 20));
				for (auto& p : map.map)
				{
					if (p.position == pos && p.type == Type::road)
					{
						p.type = Type::exit;
						item_num--;
						did_abtain_radar = false;
					}
				}
			}
		}
		
		break;
	case State::CLEAR:
		
		break;
	}
	

}

void Game::Reset()
{
	timer = total_time;
	doodle::ElapsedTime = 0;
	map.setup();
	minsu.setup();
	guard.setup();
}

bool Game::check(doodle::KeyboardButtons doodleButton)
{
	math::ivec2 position = minsu.GetPosition();
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
		else if (map.map[i].position == position && map.map[i].type == Type::exit)
		{
			current_state= State::CLEAR;
			return true;
		}
	}
	return false;
}

void Game::caught_by_guard()
{
	math::ivec2 position = minsu.GetPosition() ;
	for (auto& i : guard.guards)
	{
		switch (i.direction)
		{
		case Direction::UP:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x && position.y == i.position.y -1)
			{
				current_state = State::GAME_OVER;
			}
		}
		break;

		case Direction::DOWN:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x && position.y == i.position.y + 1)
			{
				current_state = State::GAME_OVER;
			}
		}
		break;

		case Direction::RIGHT:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x + 1 && position.y == i.position.y )
			{
				current_state = State::GAME_OVER;
			}
		}
		break;


		case Direction::LEFT:
		{
			if (position.x == i.position.x && position.y == i.position.y || position.x == i.position.x -1 && position.y == i.position.y)
			{
				current_state = State::GAME_OVER;
			}
		}
		break;
		}

	}
}

bool Game::check_guard(int index)
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
