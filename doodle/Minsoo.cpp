#include"Minsoo.h"

void Minsoo::Draw_minsu([[maybe_unused]]Camera camera)
{
	doodle::set_fill_color(255, 255, 0);
	switch(direction)
	{
	case Direction::DOWN:
		doodle::draw_image(Minsoo_Down, 2.0 * block_size, 2.0 * block_size, block_size, block_size);
		break;
	case Direction::UP:
		doodle::draw_image(Minsoo_Up, 2.0 * block_size, 2.0 * block_size, block_size, block_size);
		break;
	case Direction::RIGHT:
		doodle::draw_image(Minsoo_right, 2.0 * block_size, 2.0 * block_size, block_size, block_size);
		break;
	case Direction::LEFT:
		doodle::draw_image(Minsoo_left, 2.0 * block_size, 2.0 * block_size, block_size, block_size);
		break;
	}

#ifdef _DEBUG

#else
	doodle::push_settings();
	for (int i{ 0 }; i < 200; i++)
	{
		doodle::no_fill();
		doodle::set_outline_width(100);
		doodle::set_outline_color(0);
		doodle::draw_ellipse((position.x+0.5 + camera.GetPosition().x)* block_size, (position.y+0.5 + camera.GetPosition().y)* block_size, 350+i*10.0);
	}
	doodle::pop_settings();
#endif
	doodle::draw_text(to_string(movement),0,80);
}
void Minsoo::setup()
{
	position = math::ivec2{ 2,2 };
	movement = 0;
	chew_item = 3;
	bomb_item = 1;
	explode_count = -1;
}

void Minsoo::set_position(doodle::KeyboardButtons button)
{
	switch (button)
	{
	case doodle::KeyboardButtons::S:
	{
		position.y += 1;
		movement++;
		direction = Direction::DOWN;
		if(explode_count>0)
		{
			explode_count--;
		}
	}
		break;
	case doodle::KeyboardButtons::A:
		{
			position.x -= 1;
			movement++;
			direction = Direction::LEFT;
			if(explode_count>0)
			{
				explode_count--;
			}
		}
		break;
	case doodle::KeyboardButtons::D:
		{
			position.x += 1;
			movement++;
			direction = Direction::RIGHT;
			if(explode_count>0)
			{
				explode_count--;
			}
		}
		break;
	case doodle::KeyboardButtons::W:
		{
			position.y -= 1;
			movement++;
			direction = Direction::UP;
			if(explode_count>0)
			{
				explode_count--;
			}
		}
		break;
	}
}

math::ivec2 Minsoo::GetPosition()
{
	return position;
}

