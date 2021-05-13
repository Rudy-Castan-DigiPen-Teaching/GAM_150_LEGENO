#pragma once
enum class State
{
	START,
	CREDIT,
	IN_GAME,
	CLEAR,
	GAME_OVER
};

enum class MenuOption
{
	start,
	quit,
	credit
};

enum class Type
{
	wall,
	road,
	radar,
	treasure,
	exit,
	can_escape,
	dog_chew,
	bomb
};

enum class Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

enum class SoundType
{
	Siren,
};

