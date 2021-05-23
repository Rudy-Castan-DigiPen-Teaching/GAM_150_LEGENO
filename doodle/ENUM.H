#pragma once
enum class State
{
	SPLASH,
	START,
	CREDIT,
	OPTION,
	LEVEL_SELECT,
	IN_GAME,
	CLEAR,
	GAME_OVER
};

enum class MenuOption
{
	START,
	QUIT,
	CREDIT,
	OPTION,
};

enum class Type
{
	WALL,
	ROAD,
	RADAR,
	TREASURE,
	EXIT,
	CAN_ESCAPE,
	DOG_CHEW,
	BOMB
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

