#pragma once
enum class State
{
	START,
	IN_GAME,
	CLEAR,
	GAME_OVER
};

enum class Type
{
	wall,
	road,
	radar,
	treasure,
	exit
};

enum class Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};