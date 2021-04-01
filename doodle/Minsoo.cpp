#include"Minsoo.h"

void Minsoo::Draw_minsu()
{
	doodle::set_fill_color(255, 255, 0);
	doodle::draw_ellipse(position.x, position.y, 20);
}
void Guard::Draw_guard()
{
	doodle::set_fill_color(255, 0, 0);

	doodle::draw_ellipse(130,100, 20);
	doodle::draw_ellipse(230, 150, 20);
	doodle::draw_ellipse(280, 140, 20);
	doodle::draw_ellipse(340, 200, 20);
	doodle::draw_ellipse(530, 100, 20);
	doodle::draw_ellipse(700, 100, 20);

	doodle::draw_ellipse(130, 400, 20);
	doodle::draw_ellipse(230, 370, 20);
	doodle::draw_ellipse(280, 370, 20);
	doodle::draw_ellipse(340, 400, 20);
	doodle::draw_ellipse(530, 400, 20);
	doodle::draw_ellipse(700, 370, 20);
}

void Minsoo::set_position(doodle::KeyboardButtons button)
{
	switch (button)
	{
	case doodle::KeyboardButtons::S:
		position.y += 30;
		break;
	case doodle::KeyboardButtons::A:
		position.x -= 30;
		break;
	case doodle::KeyboardButtons::D:
		position.x += 30;
		break;
	case doodle::KeyboardButtons::W:
		position.y -= 30;
		break;
	}

}
