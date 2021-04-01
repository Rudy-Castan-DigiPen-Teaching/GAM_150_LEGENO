#include"Minsoo.h"

void Minsoo::Draw_minsu()
{
	doodle::set_fill_color(255, 255, 0);
	doodle::draw_ellipse(position.x* block_size, position.y* block_size, 20);	//block_size=30;

	/*doodle::push_settings();
	for (int i{ 0 }; i < 200; i++)
	{
		doodle::no_fill();
		doodle::set_outline_width(100);
		doodle::set_outline_color(0);
		doodle::draw_ellipse(position.x* block_size, position.y* block_size, 160+i*10);
	}
	doodle::pop_settings();*/

	doodle::draw_text(to_string(movement),0,75);
}
void Minsoo::setup()
{
	position = math::vec2{ 2.5,2.5 };
	movement = 0;
}
void Minsoo::set_position(doodle::KeyboardButtons button)
{
	switch (button)
	{
	case doodle::KeyboardButtons::S:
		//if (check_collision(math::vec2{ position.x,position.y + 1 }) == false)
		{
			position.y += 1;
			movement++;
		}
		break;
	case doodle::KeyboardButtons::A:
		//if (check_collision(math::vec2{ position.x - 1,position.y }) == false)
		{
			position.x -= 1;
			movement++;
		}
		break;
	case doodle::KeyboardButtons::D:
		//if (check_collision(math::vec2{ position.x + 1,position.y }) == false)
		{
			position.x += 1;
			movement++;
		}
		break;
	case doodle::KeyboardButtons::W:
		//if (check_collision(math::vec2{ position.x,position.y - 1 }) == false)
		{
			position.y -= 1;
			movement++;
		}
		break;
	}
}

math::vec2 Minsoo::GetPosition()
{
	return position;
}

bool Minsoo::check_collision(math::vec2 Position)
{
	Map MAP;
	MAP.setup();
	Position -= 0.5;  // starting position is {2.5, 2.5}

	for (auto& i : MAP.map)
	{
		if (i.position == Position && i.type == Type::wall)
		{
			return false;
		}
	}
	return true;
}
