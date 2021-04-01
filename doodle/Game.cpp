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
	}
}
void Game::Update()
{
	timer = 5 - static_cast<int>(doodle::ElapsedTime);
	if (timer <= 0)
	{
		Reset();
	}
}
void Game::Reset()
{
	timer = 5;
	doodle::ElapsedTime = 0;
	minsu.setup();
}

bool Game::check(doodle::KeyboardButtons doodleButton)
{
	math::vec2 position = minsu.GetPosition() -0.5;
	switch (doodleButton)
	{
	case doodle::KeyboardButtons::S:
		
			position.y += 1;
		
		break;
	case doodle::KeyboardButtons::A:
		
			position.x -= 1;
			
		break;
	case doodle::KeyboardButtons::D:
		
			position.x += 1;
			
		break;
	case doodle::KeyboardButtons::W:
		
			position.y -= 1;
		break;
	}

	for (auto& i : map.map)
	{
		if (i.position == position && i.type == Type::wall)
		{
			return false;
		}
	}
	return true;
}