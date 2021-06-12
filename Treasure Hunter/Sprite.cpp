/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Sprite.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include"Sprite.h"

Sprite::Sprite(const std::filesystem::path& spriteInfoFile, int howmanyimage,double target_time):image(spriteInfoFile),target_time(target_time)
{
	frameSize = { image.GetWidth() / howmanyimage,image.GetHeight() };
	pixcel_num = howmanyimage;
}

void Sprite::Update() // update texel position using target time, delta time
{
	animtimer += doodle::DeltaTime;
	if (animtimer > target_time)
	{
		currAnim++;
		if (currAnim == pixcel_num)
		{
			currAnim = 0;
		}
		animtimer = 0;
	}
}

math::ivec2 Sprite::GetFrameSize() const // size of one image
{
	return frameSize;
}

math::ivec2 Sprite::GetDrawPos()// get texel position
{
	math::ivec2 pos;
	pos.x = currAnim * frameSize.x;

	return pos;
}
