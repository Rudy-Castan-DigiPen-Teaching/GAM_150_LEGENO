/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#pragma once
enum class State
{
	SPLASH,
	START,
	CREDIT,
	OPTION,
	LEVEL_SELECT,
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
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
	Bite,
	BombFuse,
	ChewingGum,
	CrashWall,
	ETC,
	Explosion,
	FootStep,
	GetTreasure,
	Meow,
	PutItem,
	Radar,
	RubyAppear,
	SelectEffect,
	SelectLimitEffect,
	TimerTic,
	TimesUp,
	Win,
};

/* BGM
* BasicBGM
* Siren
* MainMenuBGM
* LevelSelectMenuBGM
*/