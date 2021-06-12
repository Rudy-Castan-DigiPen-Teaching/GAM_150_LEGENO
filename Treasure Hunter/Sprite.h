/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Sprite.h
Project: GAM150
Author:Hyosang Jung
-----------------------------------------------------------------*/
#pragma once
#include"vec2.h"// vec2 struct
#include"doodle/doodle.hpp"	// doodle image & functions 

class Sprite
{
public:
    Sprite(const std::filesystem::path& spriteInfoFile,int howmanyimage, double target_time);
    void Update();
    math::ivec2 GetFrameSize() const;
    math::ivec2 GetDrawPos();

    doodle::Image image;
    bool isAnimationDone = false;
    int currAnim = 0;
    math::ivec2 frameSize;
    int pixcel_num = 0;
    double animtimer = 0;
    double target_time;
private:
    std::vector<math::ivec2> frameTexel;
    std::vector<math::ivec2> hotSpotList;
};
