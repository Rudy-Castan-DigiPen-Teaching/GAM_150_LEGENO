/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Camera.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include"Camera.h"
#include"doodle/doodle.hpp"

const math::vec2& Camera::Get_position() const
{
	return position;
}

void Camera::Update(const math::vec2& followObjPos)
{
	math::vec2 hotspot;
	hotspot = { doodle::Width / 220.0,doodle::Height / 270.0 };
	position = -(followObjPos-hotspot);
}
