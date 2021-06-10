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
	Guards.clear();
	How_many_guards_tracing = 0;
	if (level == static_cast<int>(State::FLOOR_1))
	{
		Guards.push_back(guard_info{ math::ivec2(31, 2), Direction::LEFT });
		Guards.push_back(guard_info{ math::ivec2(27, 7), Direction::UP });
		Guards.push_back(guard_info{ math::ivec2(14, 15), Direction::UP });
		Guards.push_back(guard_info{ math::ivec2(10, 13), Direction::DOWN });
		Guards.push_back(guard_info{ math::ivec2(8, 8), Direction::RIGHT });
	}
	else if (level == static_cast<int>(State::FLOOR_2))
	{
		Guards.push_back(guard_info{ math::ivec2(8, 2) , Direction::DOWN });
		Guards.push_back(guard_info{ math::ivec2(11, 10), Direction::UP});
		Guards.push_back(guard_info{ math::ivec2(32, 13), Direction::LEFT });
		Guards.push_back(guard_info{ math::ivec2(19, 14), Direction::RIGHT });
		Guards.push_back(guard_info{ math::ivec2(20, 6), Direction::DOWN });

	}
	else if (level == static_cast<int>(State::FLOOR_3))
	{
		Guards.push_back(guard_info{ math::ivec2(13, 2) , Direction::LEFT });
		Guards.push_back(guard_info{ math::ivec2(35, 2), Direction::DOWN });
		Guards.push_back(guard_info{ math::ivec2(22, 5), Direction::RIGHT });
		Guards.push_back(guard_info{ math::ivec2(10, 6), Direction::DOWN });
		Guards.push_back(guard_info{ math::ivec2(27, 14), Direction::LEFT });
		Guards.push_back(guard_info{ math::ivec2(2, 22), Direction::UP });
		Guards.push_back(guard_info{ math::ivec2(7, 19), Direction::UP });
		Guards.push_back(guard_info{ math::ivec2(15, 22), Direction::LEFT });
		Guards.push_back(guard_info{ math::ivec2(18, 21), Direction::RIGHT });
		Guards.push_back(guard_info{ math::ivec2(40, 22), Direction::UP });
	}


	Set_sight();
}

void Guard::Draw_guard(Camera& camera)
{
	doodle::set_fill_color(255, 0, 0);
	for (auto& p : Guards)
	{

		if (p.Is_okay == true)
		{
			if (p.Guard_type == "guard")
			{
				if (p.Is_trace == true)
				{
					doodle::draw_image(Guard_tracing_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
				}
				else
				{
					switch (p.Direction)
					{
					case Direction::UP:
						doodle::draw_image(Guard_UP_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
						break;
					case Direction::DOWN:
						doodle::draw_image(Guard_Down_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
						break;
					case Direction::RIGHT:
						doodle::draw_image(Guard_Right_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
						break;
					case Direction::LEFT:
						doodle::draw_image(Guard_Left_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
						break;
					}
				}
			}
			else if (p.Guard_type == "Ruby")
			{
				p.Is_trace = true;
				switch (p.Direction)
				{
				case Direction::UP:
					doodle::draw_image(Ruby_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
					break;
				case Direction::DOWN:
					doodle::draw_image(Ruby_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
					break;
				case Direction::RIGHT:
					doodle::draw_image(Ruby_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
					break;
				case Direction::LEFT:
					doodle::draw_image(Ruby_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
					break;
				}
			}
		}
		else if (p.Is_okay == false)
		{
			if (p.Guard_type == "guard")
			{
				doodle::draw_image(Guard_CHEW_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
			}
			else if (p.Guard_type == "Ruby")
			{
				doodle::draw_image(Ruby_CHEW_image, (p.Position.x + camera.Get_position().x) * Block_size, (p.Position.y + camera.Get_position().y) * Block_size, Block_size + 10.0, Block_size + 10.0);
			}
		}

	}
}

void Guard::Draw_sight(Camera& camera, Map MAP)
{

	for (auto& guard : Guards)
	{
		for (int i = 0; i < Sight_size; i++)
		{
			if(guard.Is_okay == true)
			{
				for (auto& m : MAP.Map)
				{
					if (static_cast<int>(guard.Sight_position[i].Position.x) == m.Position.x && static_cast<int>(guard.Sight_position[i].Position.y) == m.Position.y && guard.Sight_position[i].Is_valid == true)
					{
						if (m.Type != Type::WALL)
						{
							switch (guard.Direction)
							{
							case Direction::UP:
							{
								switch (i)
								{
								case 0:
									doodle::draw_image(Sight1_up_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								case 1:
									doodle::draw_image(Sight2_up_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								case 2:
									doodle::draw_image(Sight3_up_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								}
							}
							break;
							case Direction::DOWN:
							{
								switch (i)
								{
								case 0:
									doodle::draw_image(Sight1_down_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								case 1:
									doodle::draw_image(Sight2_down_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								case 2:
									doodle::draw_image(Sight3_down_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								}
							}
							break;

							case Direction::RIGHT:
							{
								switch (i)
								{
								case 0:
									doodle::draw_image(Sight1_right_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								case 1:
									doodle::draw_image(Sight2_right_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								case 2:
									doodle::draw_image(Sight3_right_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								}
							}
							break;

							case Direction::LEFT:
							{
								switch (i)
								{
								case 0:
									doodle::draw_image(Sight1_left_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								case 1:
									doodle::draw_image(Sight2_left_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								case 2:
									doodle::draw_image(Sight3_left_image, (guard.Sight_position[i].Position.x + camera.Get_position().x) * Block_size, (guard.Sight_position[i].Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
									break;
								}
							}
							break;
							}
						}

						if (m.Type == Type::WALL)
						{
							while (i < Sight_size)
							{
								guard.Sight_position[i++].Is_valid = false;
							}
						}
					}
				}
			}
		}
	}
}


void Guard::Set_position(int index)
{
	switch (Guards[index].Direction)
	{
	case Direction::UP:
		//move up
		if (Guards[index].Is_okay == true)
		{
			Guards[index].Target_pos = Guards[index].Position;
			Guards[index].Target_pos.y--;
		}
		break;

	case Direction::DOWN:   //move down
		if (Guards[index].Is_okay == true)
		{
			Guards[index].Target_pos = Guards[index].Position;
			Guards[index].Target_pos.y++;
		}
		break;

	case Direction::RIGHT:  //move right
		if (Guards[index].Is_okay == true)
		{
			Guards[index].Target_pos = Guards[index].Position;
			Guards[index].Target_pos.x++;
		}
		break;

	case Direction::LEFT:   //move left
		if (Guards[index].Is_okay == true)
		{
			Guards[index].Target_pos = Guards[index].Position;
			Guards[index].Target_pos.x--;
		}
		break;
	}
}

void Guard::Change_sight(Map m, int index)
{
	Direction dir;
	bool is_change = false;
	if (Guards[index].Is_okay == true)
	{
		while (is_change == false)
		{
			dir = static_cast<Direction>(doodle::random(0, 4));
			while (dir == Guards[index].Direction)
			{
				dir = static_cast<Direction>(doodle::random(0, 4));
			}
			switch (dir)
			{
			case Direction::UP:
			{
				for (auto& j : m.Map)
				{
					if (Guards[index].Position.x == j.Position.x && Guards[index].Position.y - 1 == j.Position.y && (j.Type != Type::WALL))
					{
						Guards[index].Direction = Direction::UP;
						is_change = true;
					}
				}
			}
			break;
			case Direction::DOWN:
			{
				for (auto& j : m.Map)
				{
					if (Guards[index].Position.x == j.Position.x && Guards[index].Position.y + 1 == j.Position.y && (j.Type != Type::WALL))
					{
						Guards[index].Direction = Direction::DOWN;
						is_change = true;
					}
				}
			}
			break;
			case Direction::RIGHT:
			{
				for (auto& j : m.Map)
				{
					if (Guards[index].Position.x + 1 == j.Position.x && Guards[index].Position.y == j.Position.y && (j.Type != Type::WALL))
					{
						Guards[index].Direction = Direction::RIGHT;
						is_change = true;
					}
				}
			}
			break;
			case Direction::LEFT:
			{
				for (auto& j : m.Map)
				{
					if (Guards[index].Position.x - 1 == j.Position.x && Guards[index].Position.y == j.Position.y && (j.Type != Type::WALL))
					{
						Guards[index].Direction = Direction::LEFT;
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
	for (auto& i : Guards)
	{
		for (auto& j : m.Map)
		{
			if (i.Position == j.Position && j.Type == Type::DOG_CHEW)
			{
				i.Is_okay = false;
				i.Movement = movement;
				if (i.Position == exit_pos)
				{
					j.Type = Type::EXIT;
				}
				else
				{
					j.Type = Type::ROAD;
				}
			}
		}
	}

	for (auto& i : Guards)
	{

		if (i.Is_okay == false)
		{
			if (movement - i.Movement == How_many_craze)
			{
				i.Is_okay = true;
			}
		}
		if (i.Trace_movement == How_many_trace)
		{
			i.Is_trace = false;
		}

	}

}

void Guard::Set_sight()
{
	for (auto& guard : Guards)
	{
		for (int i = 0; i < Sight_size; i++)
		{
			guard.Sight_position[i].Is_valid = true;
		}
		switch (guard.Direction)
		{
		case Direction::UP:
		{
			for (int i = 0; i < Sight_size; i++)
			{
				guard.Sight_position[i].Position = math::vec2{ guard.Position.x,guard.Position.y - (i + 1.0) };
			}
		}
		break;
		case Direction::DOWN:
		{
			for (int i = 0; i < Sight_size; i++)
			{
				guard.Sight_position[i].Position = math::vec2{ guard.Position.x,guard.Position.y + (i + 1.0) };
			}
		}
		break;
		case Direction::RIGHT:
		{
			for (int i = 0; i < Sight_size; i++)
			{
				guard.Sight_position[i].Position = math::vec2{ guard.Position.x + (i + 1.0),guard.Position.y };
			}
		}
		break;
		case Direction::LEFT:
		{
			for (int i = 0; i < Sight_size; i++)
			{
				guard.Sight_position[i].Position = math::vec2{ guard.Position.x - (i + 1.0),guard.Position.y };
			}
		}
		break;
		}
	}
}

void Guard::Tracing_check(Minsoo minsoo)
{
	for (int i = 0; i < static_cast<int>(Guards.size()); i++)
	{
		for (int j = 0; j < Sight_size; j++)
		{
			if (minsoo.Get_position() == Guards[i].Sight_position[j].Position && Guards[i].Sight_position[j].Is_valid == true && Guards[i].Is_okay == true)
			{
				Guards[i].Is_trace = true;
			}
		}
	}
}

bool Guard::Is_trace_sommeone() 
{
	How_many_guards_tracing = 0;
	for (auto& i : Guards)
	{
		if (i.Is_trace == true && i.Is_okay == false) //
		{
			i.Is_trace = false;
		}
	}
	for (auto& i : Guards)
	{
		if (i.Is_trace == true)
		{
			How_many_guards_tracing++;
		}
	}

	if (How_many_guards_tracing > 0)
	{
		return true;
	}

	return false;
}

void Guard::Update_position()
{
		for (auto& guard : Guards)
		{
			if (guard.Position.x > guard.Target_pos.x)
			{
				guard.Position.x -= doodle::DeltaTime * 2;
				if (guard.Position.x <= guard.Target_pos.x)
				{
					guard.Position.x = guard.Target_pos.x;
				}
			}
			else if (guard.Position.x < guard.Target_pos.x)
			{
				guard.Position.x += doodle::DeltaTime * 2;
				if (guard.Position.x >= guard.Target_pos.x)
				{
					guard.Position.x = guard.Target_pos.x;
				}
			}

			else if (guard.Position.y > guard.Target_pos.y)
			{
				guard.Position.y -= doodle::DeltaTime * 2;
				if (guard.Position.y <= guard.Target_pos.y)
				{
					guard.Position.y = guard.Target_pos.y;
				}
			}
			else if (guard.Position.y < guard.Target_pos.y)
			{
				guard.Position.y += doodle::DeltaTime * 2;
				if (guard.Position.y >= guard.Target_pos.y)
				{
					guard.Position.y = guard.Target_pos.y;
				}
			}
		}
}



void Guard::Check_watching_wall(Map m)
{
	for (int index = 0; index < Guards.size(); index++)
	{
		switch (Guards[index].Direction)
		{
		case Direction::UP:   //move up
		{
			for (auto& i : m.Map)
			{
				if (i.Position.x == Guards[index].Position.x && i.Position.y == Guards[index].Position.y - 1 && i.Type == Type::WALL)
				{
					Change_sight(m, index);

				}
			}
		}
		break;
		case Direction::DOWN:   //move down
			for (auto& i : m.Map)
			{
				if (i.Position.x == Guards[index].Position.x && i.Position.y == Guards[index].Position.y + 1 && i.Type == Type::WALL)
				{
					Change_sight(m, index);

				}
			}
			break;
		case Direction::RIGHT:   //move right
			for (auto& i : m.Map)
			{
				if (i.Position.x == Guards[index].Position.x + 1 && i.Position.y == Guards[index].Position.y && i.Type == Type::WALL)
				{
					Change_sight(m, index);;

				}
			}
			break;
		case Direction::LEFT:   //move left
			for (auto& i : m.Map)
			{
				if (i.Position.x == Guards[index].Position.x - 1 && i.Position.y == Guards[index].Position.y && i.Type == Type::WALL)
				{
					Change_sight(m, index);

				}
			}
			break;
		}
	}

}