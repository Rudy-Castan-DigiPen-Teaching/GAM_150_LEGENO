#include "Map.h"
#include <fstream>
#include "doodle/doodle.hpp"
#include "Guard.h"


void Guard::setup()
{
	guards.clear();
	guards.push_back(guard_info{ math::ivec2(4, 3) , Direction::UP });
	guards.push_back(guard_info{ math::ivec2(9, 4), Direction::UP });
	guards.push_back(guard_info{ math::ivec2(15, 4), Direction::UP });
	guards.push_back(guard_info{ math::ivec2(6, 8), Direction::DOWN });
	guards.push_back(guard_info{ math::ivec2(11,8), Direction::UP });
	guards.push_back(guard_info{ math::ivec2(14, 8), Direction::RIGHT });
	guards.push_back(guard_info{ math::ivec2(4, 15), Direction::DOWN });
	guards.push_back(guard_info{ math::ivec2(7, 16), Direction::UP });
	guards.push_back(guard_info{ math::ivec2(15, 17), Direction::UP });
	guards.push_back(guard_info{ math::ivec2(21, 9), Direction::DOWN });
	guards.push_back(guard_info{ math::ivec2(25, 9), Direction::UP });
	guards.push_back(guard_info{ math::ivec2(27, 11), Direction::UP });
}

void Guard::Draw_guard()
{
	doodle::set_fill_color(255, 0, 0);
	for (auto p : guards)
	{
		doodle::draw_ellipse((p.position.x + 0.5) * 30  , (p.position.y + 0.5 ) * 30 , 20);
	}
}

void Guard::Draw_Sight()
{

	for (auto g : guards)
	{
		switch (g.direction)
		{
		case Direction::UP:   //move up
		{
		doodle::push_settings();
		doodle::set_fill_color(255, 255, 0);
		doodle::draw_triangle(g.position.x *30, (g.position.y )*30, (g.position.x + 1)*30, (g.position.y )*30, (g.position.x +0.5)*30, (g.position.y - 1)*30);
		doodle::pop_settings();
		}
		break;

		case Direction::DOWN:   //move down
		{
			doodle::push_settings();
			doodle::set_fill_color(255, 255, 0);
			doodle::draw_triangle(g.position.x *30, (g.position.y +1)*30, (g.position.x + 1)*30, (g.position.y +1)*30, (g.position.x +0.5)*30, (g.position.y + 2)*30);
			doodle::pop_settings();
		}
		break;

		case Direction::RIGHT:  //move right
		{
			doodle::push_settings();
			doodle::set_fill_color(255, 255, 0);
			doodle::draw_triangle((g.position.x+1) * 30, (g.position.y) * 30, (g.position.x+1 ) * 30, (g.position.y+1) * 30, (g.position.x +2) * 30, (g.position.y + 0.5) * 30);
			doodle::pop_settings();
		}
		break;

		case Direction::LEFT:   //move left
		{
			doodle::push_settings();
			doodle::set_fill_color(255, 255, 0);
			doodle::draw_triangle(g.position.x * 30, (g.position.y) * 30, (g.position.x ) * 30, (g.position.y+1) * 30, (g.position.x -1) * 30, (g.position.y + 0.5) * 30);
			doodle::pop_settings();
		}
		break;
		}
	}
}
	

void Guard::move(int index)
{
	switch (guards[index].direction)
	{
	case Direction::UP:   //move up
		guards[index].position.y--;
		break;

	case Direction::DOWN:   //move down
		guards[index].position.y++;
		break;

	case Direction::RIGHT:  //move right
		guards[index].position.x++;
		break;

	case Direction::LEFT:   //move left
		guards[index].position.x--;
		break;
	}

}

void Guard::change_sight(Map m, int index)
{
	Direction dir;
	bool is_change = false;
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
					if (guards[index].position.x == j.position.x && guards[index].position.y - 1 == j.position.y && j.type == Type::road)
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
					if (guards[index].position.x == j.position.x && guards[index].position.y + 1 == j.position.y && j.type == Type::road)
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
					if (guards[index].position.x + 1 == j.position.x && guards[index].position.y == j.position.y && j.type == Type::road)
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
					if (guards[index].position.x - 1 == j.position.x && guards[index].position.y == j.position.y && j.type == Type::road)
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