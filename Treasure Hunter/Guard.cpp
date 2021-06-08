/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include "Guard.h"

void Guard::Set_up(int level)
{
	guards.clear();
	how_many_guards_tracing = 0;
	if (level == static_cast<int>(State::LEVEL_1))
	{
		guards.push_back(guard_info{ math::ivec2(31, 2), Direction::LEFT });
		guards.push_back(guard_info{ math::ivec2(27, 7), Direction::UP });
		guards.push_back(guard_info{ math::ivec2(14, 15), Direction::UP });
		guards.push_back(guard_info{ math::ivec2(10, 13), Direction::DOWN });
		guards.push_back(guard_info{ math::ivec2(8, 8), Direction::RIGHT });
	}
	else if (level == static_cast<int>(State::LEVEL_2))
	{
		guards.push_back(guard_info{ math::ivec2(8, 2) , Direction::DOWN });
		guards.push_back(guard_info{ math::ivec2(11, 10), Direction::UP});
		guards.push_back(guard_info{ math::ivec2(32, 13), Direction::LEFT });
		guards.push_back(guard_info{ math::ivec2(19, 14), Direction::RIGHT });
		guards.push_back(guard_info{ math::ivec2(20, 6), Direction::DOWN });

	}
	else if (level == static_cast<int>(State::LEVEL_3))
	{
		guards.push_back(guard_info{ math::ivec2(2, 11) , Direction::DOWN });
		guards.push_back(guard_info{ math::ivec2(5, 10), Direction::UP });
		guards.push_back(guard_info{ math::ivec2(10, 8), Direction::RIGHT });
		guards.push_back(guard_info{ math::ivec2(19, 12), Direction::LEFT });
		guards.push_back(guard_info{ math::ivec2(18, 17), Direction::RIGHT });
		guards.push_back(guard_info{ math::ivec2(22, 5), Direction::LEFT });
		guards.push_back(guard_info{ math::ivec2(25, 21), Direction::DOWN });
		guards.push_back(guard_info{ math::ivec2(33, 9), Direction::UP });
		guards.push_back(guard_info{ math::ivec2(34, 17), Direction::LEFT });
		guards.push_back(guard_info{ math::ivec2(39, 7), Direction::DOWN });
	}


	Set_sight();
}

void Guard::Draw_guard(Camera& camera)
{
	doodle::set_fill_color(255, 0, 0);
	for (auto& p : guards)
	{

		if (p.is_okay == true)
		{
			if (p.guard_type == "guard")
			{
				if (p.is_trace == true)
				{
					doodle::draw_image(Guard_tracing_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
				}
				else
				{
					switch (p.direction)
					{
					case Direction::UP:
						doodle::draw_image(GuardUP_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
						break;
					case Direction::DOWN:
						doodle::draw_image(GuardDown_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
						break;
					case Direction::RIGHT:
						doodle::draw_image(GuardRight_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
						break;
					case Direction::LEFT:
						doodle::draw_image(GuardLeft_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
						break;
					}
				}
			}
			else if (p.guard_type == "Ruby")
			{
				p.is_trace = true;
				switch (p.direction)
				{
				case Direction::UP:
					doodle::draw_image(Ruby_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
					break;
				case Direction::DOWN:
					doodle::draw_image(Ruby_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
					break;
				case Direction::RIGHT:
					doodle::draw_image(Ruby_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
					break;
				case Direction::LEFT:
					doodle::draw_image(Ruby_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
					break;
				}
			}
		}
		else if (p.is_okay == false)
		{
			doodle::draw_image(Guard_CHEW_image, (p.position.x + camera.Get_position().x) * block_size, (p.position.y + camera.Get_position().y) * block_size, block_size + 10.0, block_size + 10.0);
		}

	}
}

void Guard::Draw_sight(Camera& camera, Map MAP)
{

	for (auto& guard : guards)
	{
		for (int i = 0; i < sight_size; i++)
		{
			for (auto& m : MAP.map)
			{
				if (static_cast<int>(guard.sight_position[i].position.x) == m.position.x && static_cast<int>(guard.sight_position[i].position.y) == m.position.y && guard.sight_position[i].is_valid == true)
				{
					if (m.type != Type::WALL)
					{
						switch (guard.direction)
						{
						case Direction::UP:
						{
							switch (i)
							{
							case 0:
								doodle::draw_image(Sight1_up_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							case 1:
								doodle::draw_image(Sight2_up_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							case 2:
								doodle::draw_image(Sight3_up_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							}
						}
						break;
						case Direction::DOWN:
						{
							switch (i)
							{
							case 0:
								doodle::draw_image(Sight1_down_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							case 1:
								doodle::draw_image(Sight2_down_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							case 2:
								doodle::draw_image(Sight3_down_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							}
						}
						break;

						case Direction::RIGHT:
						{
							switch (i)
							{
							case 0:
								doodle::draw_image(Sight1_right_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							case 1:
								doodle::draw_image(Sight2_right_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							case 2:
								doodle::draw_image(Sight3_right_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							}
						}
						break;

						case Direction::LEFT:
						{
							switch (i)
							{
							case 0:
								doodle::draw_image(Sight1_left_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							case 1:
								doodle::draw_image(Sight2_left_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							case 2:
								doodle::draw_image(Sight3_left_image, (guard.sight_position[i].position.x + camera.Get_position().x) * block_size, (guard.sight_position[i].position.y + camera.Get_position().y) * block_size, block_size, block_size);
								break;
							}
						}
						break;
						}
					}

					if (m.type == Type::WALL)
					{
						while (i < sight_size)
						{
							guard.sight_position[i++].is_valid = false;
						}
					}
				}
			}
		}
	}
}


void Guard::Set_position(int index)
{
	switch (guards[index].direction)
	{
	case Direction::UP:
		//move up
		if (guards[index].is_okay == true)
		{
			guards[index].target_pos = guards[index].position;
			guards[index].target_pos.y--;
		}
		break;

	case Direction::DOWN:   //move down
		if (guards[index].is_okay == true)
		{
			guards[index].target_pos = guards[index].position;
			guards[index].target_pos.y++;
		}
		break;

	case Direction::RIGHT:  //move right
		if (guards[index].is_okay == true)
		{
			guards[index].target_pos = guards[index].position;
			guards[index].target_pos.x++;
		}
		break;

	case Direction::LEFT:   //move left
		if (guards[index].is_okay == true)
		{
			guards[index].target_pos = guards[index].position;
			guards[index].target_pos.x--;
		}
		break;
	}
}

void Guard::Change_sight(Map m, int index)
{
	Direction dir;
	bool is_change = false;
	if (guards[index].is_okay == true)
	{
		while (is_change == false)
		{
			dir = static_cast<Direction>(doodle::random(0, 4));
			while (dir == guards[index].direction)
			{
				dir = static_cast<Direction>(doodle::random(0, 4));
			}
			switch (dir)
			{
			case Direction::UP:
			{
				for (auto& j : m.map)
				{
					if (guards[index].position.x == j.position.x && guards[index].position.y - 1 == j.position.y && (j.type != Type::WALL))
					{
						guards[index].direction = Direction::UP;
						is_change = true;
					}
				}
			}
			break;
			case Direction::DOWN:
			{
				for (auto& j : m.map)
				{
					if (guards[index].position.x == j.position.x && guards[index].position.y + 1 == j.position.y && (j.type != Type::WALL))
					{
						guards[index].direction = Direction::DOWN;
						is_change = true;
					}
				}
			}
			break;
			case Direction::RIGHT:
			{
				for (auto& j : m.map)
				{
					if (guards[index].position.x + 1 == j.position.x && guards[index].position.y == j.position.y && (j.type != Type::WALL))
					{
						guards[index].direction = Direction::RIGHT;
						is_change = true;
					}
				}
			}
			break;
			case Direction::LEFT:
			{
				for (auto& j : m.map)
				{
					if (guards[index].position.x - 1 == j.position.x && guards[index].position.y == j.position.y && (j.type != Type::WALL))
					{
						guards[index].direction = Direction::LEFT;
						is_change = true;
					}
				}
			}
			break;

			}
		}
	}

}

void Guard::Guard_movement_update(math::ivec2 exit_pos, Map& m, int movement) 
{
	for (auto& i : guards)
	{
		for (auto& j : m.map)
		{
			if (i.position == j.position && j.type == Type::DOG_CHEW)
			{
				i.is_okay = false;
				i.movement = movement;
				if (i.position == exit_pos)
				{
					j.type = Type::EXIT;
				}
				else
				{
					j.type = Type::ROAD;
				}
			}
		}
	}

	for (auto& i : guards)
	{

		if (i.is_okay == false)
		{
			if (movement - i.movement == how_many_craze)
			{
				i.is_okay = true;
			}
		}
		if (i.trace_movement == how_many_trace)
		{
			i.is_trace = false;
		}

	}

}

void Guard::Set_sight()
{
	for (auto& guard : guards)
	{
		for (int i = 0; i < sight_size; i++)
		{
			guard.sight_position[i].is_valid = true;
		}
		switch (guard.direction)
		{
		case Direction::UP:
		{
			for (int i = 0; i < sight_size; i++)
			{
				guard.sight_position[i].position = math::vec2{ guard.position.x,guard.position.y - (i + 1.0) };
			}
		}
		break;
		case Direction::DOWN:
		{
			for (int i = 0; i < sight_size; i++)
			{
				guard.sight_position[i].position = math::vec2{ guard.position.x,guard.position.y + (i + 1.0) };
			}
		}
		break;
		case Direction::RIGHT:
		{
			for (int i = 0; i < sight_size; i++)
			{
				guard.sight_position[i].position = math::vec2{ guard.position.x + (i + 1.0),guard.position.y };
			}
		}
		break;
		case Direction::LEFT:
		{
			for (int i = 0; i < sight_size; i++)
			{
				guard.sight_position[i].position = math::vec2{ guard.position.x - (i + 1.0),guard.position.y };
			}
		}
		break;
		}
	}
}

void Guard::Tracing_check(Minsoo minsoo)
{
	for (int i = 0; i < static_cast<int>(guards.size()); i++)
	{
		for (int j = 0; j < sight_size; j++)
		{
			if (minsoo.Get_position() == guards[i].sight_position[j].position && guards[i].sight_position[j].is_valid == true && guards[i].is_okay == true)
			{
				guards[i].is_trace = true;
			}
		}
	}
}

bool Guard::Is_trace_sommeone() 
{
	how_many_guards_tracing = 0;
	for (auto& i : guards)
	{
		if (i.is_trace == true && i.is_okay == false) //
		{
			i.is_trace = false;
		}
	}
	for (auto& i : guards)
	{
		if (i.is_trace == true)
		{
			how_many_guards_tracing++;
		}
	}

	if (how_many_guards_tracing > 0)
	{
		return true;
	}

	return false;
}

void Guard::Update_position()
{
		for (auto& guard : guards)
		{
			if (guard.position.x > guard.target_pos.x)
			{
				guard.position.x -= doodle::DeltaTime * 2;
				if (guard.position.x <= guard.target_pos.x)
				{
					guard.position.x = guard.target_pos.x;
				}
			}
			else if (guard.position.x < guard.target_pos.x)
			{
				guard.position.x += doodle::DeltaTime * 2;
				if (guard.position.x >= guard.target_pos.x)
				{
					guard.position.x = guard.target_pos.x;
				}
			}

			else if (guard.position.y > guard.target_pos.y)
			{
				guard.position.y -= doodle::DeltaTime * 2;
				if (guard.position.y <= guard.target_pos.y)
				{
					guard.position.y = guard.target_pos.y;
				}
			}
			else if (guard.position.y < guard.target_pos.y)
			{
				guard.position.y += doodle::DeltaTime * 2;
				if (guard.position.y >= guard.target_pos.y)
				{
					guard.position.y = guard.target_pos.y;
				}
			}
		}
}



void Guard::Check_watching_wall(Map m)
{
	for (int index = 0; index < guards.size(); index++)
	{
		switch (guards[index].direction)
		{
		case Direction::UP:   //move up
		{
			for (auto& i : m.map)
			{
				if (i.position.x == guards[index].position.x && i.position.y == guards[index].position.y - 1 && i.type == Type::WALL)
				{
					Change_sight(m, index);

				}
			}
		}
		break;
		case Direction::DOWN:   //move down
			for (auto& i : m.map)
			{
				if (i.position.x == guards[index].position.x && i.position.y == guards[index].position.y + 1 && i.type == Type::WALL)
				{
					Change_sight(m, index);

				}
			}
			break;
		case Direction::RIGHT:   //move right
			for (auto& i : m.map)
			{
				if (i.position.x == guards[index].position.x + 1 && i.position.y == guards[index].position.y && i.type == Type::WALL)
				{
					Change_sight(m, index);;

				}
			}
			break;
		case Direction::LEFT:   //move left
			for (auto& i : m.map)
			{
				if (i.position.x == guards[index].position.x - 1 && i.position.y == guards[index].position.y && i.type == Type::WALL)
				{
					Change_sight(m, index);

				}
			}
			break;
		}
	}

}