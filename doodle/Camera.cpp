#include"Camera.h"

const math::vec2& Camera::GetPosition() const
{
	return position;
}

void Camera::Update(const math::vec2& followObjPos)
{
	math::vec2 hotspot = { 2,2 };
	position = -(followObjPos-hotspot);
}
