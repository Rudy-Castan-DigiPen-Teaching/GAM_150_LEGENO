#include"Sprite.h"

Sprite::Sprite(const std::filesystem::path& spriteInfoFile, int howmanyimage,double target_time):image(spriteInfoFile),target_time(target_time)
{
	frameSize = { image.GetWidth() / howmanyimage,image.GetHeight() };
	pixcel_num = howmanyimage;
}

void Sprite::Update()
{
	static double timer = 0;
	timer += doodle::DeltaTime;
	if (timer > target_time)
	{
		currAnim++;
		if (currAnim == pixcel_num)
		{
			currAnim = 0;
		}
		timer = 0;
	}
}

math::ivec2 Sprite::GetDrawPos()
{
	math::ivec2 pos;
	pos.x = currAnim * frameSize.x;

	return pos;
}
