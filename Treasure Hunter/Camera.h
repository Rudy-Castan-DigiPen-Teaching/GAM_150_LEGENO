/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Project: GAM150
Author: 
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


