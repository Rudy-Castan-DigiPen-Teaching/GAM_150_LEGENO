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
	PAUSE,
	CLEAR,
	GAME_OVER
};

enum class MenuOption
{
	START,
	CREDIT,
	QUIT,
	OPTION,
};

enum class PauseOption
{
	SOUND,
	RESTART,
	MAIN_MENU,
};

enum class Type
{
	WALL,
	ROAD,
	RADAR,
	TREASURE_crown,
	TREASURE_key,
	TREASURE_coin,
	TREASURE_dia,
	EXIT,
	CAN_ESCAPE,
	DOG_CHEW,
	BOMB,
	BOMB_TO_ROAD
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
	Explosion,
	FootStep,
	GetTreasure,
	Meow,
	PutItem,
	Radar,
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