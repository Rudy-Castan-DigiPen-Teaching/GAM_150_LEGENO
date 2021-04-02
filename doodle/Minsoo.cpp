#include"Minsoo.h"

void Minsoo::Draw_minsu()
{
	doodle::set_fill_color(255, 255, 0);
	doodle::draw_ellipse((position.x + 0.5)* block_size, (position.y+0.5)* block_size, 20);	//block_size=30;

	/*doodle::push_settings();
	for (int i{ 0 }; i < 200; i++)
	{
		doodle::no_fill();
		doodle::set_outline_width(100);
		doodle::set_outline_color(0);
		doodle::draw_ellipse(position.x* block_size, position.y* block_size, 160+i*10);
	}
	doodle::pop_settings();*/

	doodle::draw_text(to_string(movement),0,80);
}
void Minsoo::setup()
{
	position = math::ivec2{ 2,2 };
	movement = 0;
}
void Minsoo::set_position(doodle::KeyboardButtons button)
{
	switch (button)
	{
	case doodle::KeyboardButtons::S:
	{
		position.y += 1;
		movement++;
	}
		break;
	case doodle::KeyboardButtons::A:
		{
			position.x -= 1;
			movement++;
		}
		break;
	case doodle::KeyboardButtons::D:
		{
			position.x += 1;
			movement++;
		}
		break;
	case doodle::KeyboardButtons::W:
		{
			position.y -= 1;
			movement++;
		}
		break;
	}
}

math::ivec2 Minsoo::GetPosition()
{
	return position;
}

