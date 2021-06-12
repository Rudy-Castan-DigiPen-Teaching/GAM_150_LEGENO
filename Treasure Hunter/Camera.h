/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Camera.h
Project: GAM150
Author: Hyosang Jung
-----------------------------------------------------------------*/
#pragma once

#include "vec2.h" // vec2 struct

class Camera
{
public:
	const math::vec2& Get_position() const;	 
	void Update(const math::vec2& followObjPos);
private:
	math::vec2 position { 0, 0 };
};


