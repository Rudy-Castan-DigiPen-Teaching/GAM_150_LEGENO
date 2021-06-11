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
	TUTORIAL,
	FLOOR_1,
	FLOOR_2,
	FLOOR_3,
	PAUSE,
	CLEAR,
	ENDING,
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
	TREASURE_CROWN,
	TREASURE_KEY,
	TREASURE_COIN,
	TREASURE_DIA,
	EXIT,
	CAN_ESCAPE,
	DOG_CHEW,
	BOMB,
	BOMB_TO_ROAD,
	LADDER,
	NEXT
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
	BITE,
	BOMB_FUSE,
	CHEWING_GUM,
	CRASH_WALL,
	EXPLOSION,
	FOOT_STEP,
	GET_TREASURE,
	MEOW,
	PUT_ITEM,
	RADAR,
	SELECT_EFFECT,
	SELECT_LIMIT_EFFECT,
	TIMER_TIC,
	TIMES_UP,
	WIN,
	LADDER,
	PASS,
	COUNT
};

/* BGM
* BasicBGM
* Siren
* MainMenuBGM
* LevelSelectMenuBGM
* EndingBGM
*/