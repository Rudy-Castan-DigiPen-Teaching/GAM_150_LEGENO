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
	
}

void Game::set_position(doodle::KeyboardButtons doodleButton)
{
	minsu.set_position(doodleButton);
}