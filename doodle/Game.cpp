#include"Game.h"

void Game::setup()
{
	map.setup();
	guard.setup();
}

void Game::Draw()
{
	map.draw();
	guard.Draw_guard();
	minsu.Draw_minsu();
	doodle::draw_text(std::to_string(timer),80,80);
}

void Game::set_position(doodle::KeyboardButtons doodleButton)
{
	if (check(doodleButton) == false)
	{
		minsu.set_position(doodleButton);
		for (int i=0; i<static_cast<int>(guard.guards.size()); i++)
		{
			if (minsu.GetPosition() == guard.guards[i])
			{
				Reset();
			}
			int direction = doodle::random(1, 5);
			while (1)
			{
				if (check_guard(i, direction) == false)
				{
					guard.move(i, direction);
					break;
				}
				direction = doodle::random(1, 5);
			}
		}
	}
}
void Game::Update()
{
	timer = 20 - static_cast<int>(doodle::ElapsedTime);
	if (timer <= 0)
	{
		Reset();
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
	caught_by_guard();

}

void Game::Reset()
{
	timer = 20;
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
	}
	//for (auto& i : map.map)
	//{
	//	if (i.position == position && i.type == Type::wall)
	//	{
	//		return true;
	//	}
	//}
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
		else if (map.map[i].position == position && map.map[i].type == Type::exit)
		{
			Reset();
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
		if (position.x == i.x  && position.y == i.y )
		{
			Reset();
		}
	}
}

bool Game::check_guard(int index, int direction)
{
	switch (direction)
	{
	case 1:   //move up
	{
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].x  && i.position.y == guard.guards[index].y -1  && i.type == Type::wall)
			{
				return true;
			}
		}
	}
		break;
	case 2:   //move down
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].x && i.position.y == guard.guards[index].y + 1 && i.type == Type::wall)
			{
				return true;
			}
		}
		break;
	case 3:   //move right
		for (auto& i : map.map)
		{
			if (i.position.x == guard.guards[index].x+1 && i.position.y == guard.guards[index].y  && i.type == Type::wall)
			{														 
				return true;										 
			}														 
		}															 
		break;														 
	case 4:   //move left											 
		for (auto& i : map.map)										 
		{															 
			if (i.position.x == guard.guards[index].x-1 && i.position.y == guard.guards[index].y && i.type == Type::wall)
			{
				return true;
			}
		}
		break;
	}
	return false;
}