/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include"Minsoo.h"

void Minsoo::Draw_minsu(Camera camera,[[maybe_unused]]bool camera_move)
{
	doodle::set_fill_color(255, 255, 0);
	switch (direction)
	{
	case Direction::DOWN:
		doodle::draw_image(Minsoo_Down.image, (position.x + camera.Get_position().x) * Block_size, (position.y + camera.Get_position().y) * Block_size, Block_size, Block_size, Minsoo_Down.GetDrawPos().x, 0);
		break; 
	case Direction::UP:
		doodle::draw_image(Minsoo_Up.image, (position.x + camera.Get_position().x) * Block_size, (position.y + camera.Get_position().y) * Block_size, Block_size, Block_size, Minsoo_Up.GetDrawPos().x, 0);
		break;
	case Direction::RIGHT:
		doodle::draw_image(Minsoo_right.image, (position.x + camera.Get_position().x) * Block_size, (position.y + camera.Get_position().y) * Block_size, Block_size, Block_size, Minsoo_right.GetDrawPos().x, 0);
		break; 
	case Direction::LEFT:
		doodle::draw_image(Minsoo_left.image, (position.x + camera.Get_position().x) * Block_size, (position.y + camera.Get_position().y) * Block_size, Block_size, Block_size, Minsoo_left.GetDrawPos().x,0);
		break;
	}
}
void Minsoo::Set_up()
{
	is_dead = false;
	position = math::ivec2{ 2,2 };
	movement = 0;
	chew_item = 3;
	bomb_item = 1;
	explode_count = -1;
	target_pos = position;
}

void Minsoo::Set_position(doodle::KeyboardButtons button)
{
	target_pos = Get_position();  //fist set curr pos

	switch (button)
	{
	case doodle::KeyboardButtons::S:
	case doodle::KeyboardButtons::Down:
	{
		target_pos.y += 1;
		direction = Direction::DOWN;
	}
		break;
	case doodle::KeyboardButtons::A:
	case doodle::KeyboardButtons::Left:
		{
		target_pos.x -= 1;
		direction = Direction::LEFT;

		}
		break;
	case doodle::KeyboardButtons::D:
	case doodle::KeyboardButtons::Right:
		{
		target_pos.x += 1;			
		direction = Direction::RIGHT;
		}
		break;
	case doodle::KeyboardButtons::W:
	case doodle::KeyboardButtons::Up:
		{
		target_pos.y -= 1;
		direction = Direction::UP;
		}
		break;
	}


}

void Minsoo::Update_position(bool& is_move)
{
	if (is_move == true)
	{
		if (position.x > target_pos.x)
		{
			position.x -= doodle::DeltaTime * 2;
			Minsoo_left.Update();
			if (position.x <= target_pos.x)
			{
				position.x = target_pos.x;
				is_move = false;
				movement++;
				Minsoo_left.currAnim = 0;
				if (explode_count != 0)
				{	
					explode_count--;
				}
			}

		}
		else if (position.x < target_pos.x)
		{
			position.x += doodle::DeltaTime * 2;
			Minsoo_right.Update();
			if (position.x >= target_pos.x)
			{
				position.x = target_pos.x;
				is_move = false;
				movement++;
				Minsoo_right.currAnim = 0;
				if (explode_count != 0)
				{
					explode_count--;
				}
			}
		}

		else if (position.y > target_pos.y)
		{
			position.y -= doodle::DeltaTime * 2;
			Minsoo_Up.Update();
			if (position.y <= target_pos.y)
			{
				position.y = target_pos.y;
				is_move = false;
				movement++;
				Minsoo_Up.currAnim = 0;
				if (explode_count != 0)
				{
					explode_count--;
				}
			}
		}
		else if (position.y < target_pos.y)
		{
			position.y += doodle::DeltaTime * 2;
			Minsoo_Down.Update();
			if (position.y >= target_pos.y)
			{
				position.y = target_pos.y;
				is_move = false;
				movement++;
				Minsoo_Down.currAnim = 0;
				if (explode_count != 0)
				{
					explode_count--;
				}
			}
		}
	}
}

math::vec2 Minsoo::Get_position()
{
	return position;
}

