#pragma once

#include "vec2.h"

class Camera
{
public:
	//Camera(math::vec2 movableRange);
	//void SetPosition(math::vec2 newPosition);
	const math::vec2& GetPosition() const;
	//void SetExtent(math::irect2 newExtent);
	void Update(const math::vec2& followObjPos);
private:
	//math::irect2 extent;
	math::vec2 position;
	//math::rect2 movableRange;
};


