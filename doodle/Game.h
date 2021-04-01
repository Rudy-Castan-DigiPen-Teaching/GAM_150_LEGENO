#include"Map.h"
#include"Minsoo.h"
#include "Guard.h"
#include"doodle/doodle.hpp"
class Game
{
	Map map;
	Minsoo minsu;
	Guard guard;
public:
	void setup();
	void Draw();
	void set_position(doodle::KeyboardButtons doodleButton);
};