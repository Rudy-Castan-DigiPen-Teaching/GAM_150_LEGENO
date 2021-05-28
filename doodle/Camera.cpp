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
	math::vec2 hotspot = {doodle::Width/250.0,doodle::Height/250.0};
	position = -(followObjPos-hotspot);
}
