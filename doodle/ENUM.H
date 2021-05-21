#pragma once
enum class State
{
	Splash,
	START,
	CREDIT,
	Option,
	Level_select,
	IN_GAME,
	CLEAR,
	GAME_OVER
};

enum class MenuOption
{
	start,
	quit,
	credit,
	option,
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
	
};

