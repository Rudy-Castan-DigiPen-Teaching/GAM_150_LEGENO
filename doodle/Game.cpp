#include"Game.h"

void Game::setup()
{
	map.setup();
}

void Game::Draw()
{
	map.draw();
	minsu.Draw_minsu();
	guard.Draw_guard();
}

void Game::set_position(doodle::KeyboardButtons doodleButton)
{
	minsu.set_position(doodleButton);
}