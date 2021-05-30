/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include"Camera.h"
#include"doodle/doodle.hpp"

//Camera::Camera(math::rect2 movableRange)
//{
//	
//}



//void Camera::SetPosition(math::vec2 newPosition)
//{
//	
//}



const math::vec2& Camera::Get_position() const
{
	return position;
}


//void Camera::SetExtent(math::irect2 newExtent)
//{
//	
//}

void Camera::Update(const math::vec2& followObjPos)
{
	//math::vec2 hotspot = { doodle::Width/250.0,doodle::Height/250.0 };
	math::vec2 hotspot = {doodle::Width/220.0,doodle::Height/270.0};
	position = -(followObjPos-hotspot);
}
