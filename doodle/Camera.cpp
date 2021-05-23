#include"Camera.h"

//Camera::Camera(math::rect2 movableRange)
//{
//	
//}
//
//void Camera::SetPosition(math::vec2 newPosition)
//{
//	
//}
//
const math::vec2& Camera::Get_position() const
{
	return position;
}


////void Camera::SetExtent(math::irect2 newExtent)
////{
////	
////}
//
void Camera::Update(const math::vec2& followObjPos)
{
	math::vec2 hotspot = { 2,2 };
	position = -(followObjPos-hotspot);
}
