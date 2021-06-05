/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author: 
-----------------------------------------------------------------*/
#pragma once

#include "vec2.h" // vec2 struct

class Camera
{
public:
	//Camera(math::vec2 movableRange);
	//void SetPosition(math::vec2 newPosition);
	const math::vec2& Get_position() const;	 
	//void SetExtent(math::irect2 newExtent);
	void Update(const math::vec2& followObjPos);
private:
	//math::irect2 extent;
	math::vec2 position { 0, 0 };
	//math::rect2 movableRange;
};


