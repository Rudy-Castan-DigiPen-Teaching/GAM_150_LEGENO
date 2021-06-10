/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include "Map.h"
#include <fstream> // to load file

using namespace doodle;

void Map::Set_up(int level)
{
    Map.clear();
    std::ifstream readFile;

    readFile.open("assets/Map" + to_string(level - (static_cast<int>(State::FLOOR_1) - 1)) + ".txt");
    int width = 0;
    int height = 0;
    Treasure_num = 4;
    if (readFile.is_open())
    {
        while (!readFile.eof())
        {
            char a;
            readFile >> a;
 /*           if (readFile.eof())
            {
                break;
            }*/
            switch (a)
            {
            case '0': 
            {
            		Map.push_back(info{ math::ivec2{width,height},Type::ROAD });
					 break;
            }
            case '1':
            {
            		Map.push_back(info{ math::ivec2{width,height},Type::WALL });
					 break;
            }
            case '2': 
            {
            	Map.push_back(info{ math::ivec2{width,height},Type::RADAR });
                break;
            }
            case '3':
            {
                switch (level)
                {
                    case  static_cast<int>(State::TUTORIAL) :
                    {
                        
                        switch (Treasure_num)
                        {
                            case 1:
                            {
                                Map.push_back(info{ math::ivec2{width,height},Type::TREASURE_CROWN });
                                Treasure_num = 2;
                                break;
                            }
                            case 2:
                            {
                                Map.push_back(info{ math::ivec2{width,height},Type::TREASURE_KEY });
                                Treasure_num = 1;
                                break;
                            }

                            case 3:
                            {
                                Map.push_back(info{ math::ivec2{width,height},Type::TREASURE_COIN });
                                Treasure_num = 2;
                                break;
                            }
                            case 4:
                            {
                                Map.push_back(info{ math::ivec2{width,height},Type::TREASURE_DIA });
                                Treasure_num = 3;
                                break;
                            }                       	
                        }
                        break;
                    }
                    case static_cast<int>(State::FLOOR_1) :
                    {
                        switch (Treasure_num)
                        {
                        case 3:
                        {
                            Map.push_back(info{ math::ivec2{width,height},Type::TREASURE_CROWN });
                            Treasure_num = 2;
                            break;
                        }
                        case 4:
                        {
                            Map.push_back(info{ math::ivec2{width,height},Type::TREASURE_KEY });
                            Treasure_num = 3;
                            break;
                        }
                        }
                        break;
                    }

                    case static_cast<int>(State::FLOOR_2) :
                    {
                        switch (Treasure_num)
                        {
                        case 3:
                        {
                            Map.push_back(info{ math::ivec2{width,height},Type::TREASURE_COIN });
                            Treasure_num = 2;
                            break;
                        }
                        case 4:
                        {
                            Map.push_back(info{ math::ivec2{width,height},Type::TREASURE_DIA });
                            Treasure_num = 3;
                            break;
                        }
                        }
                        break;
                    }

                }
                break;
            }
            }

            if (width < Map_width - 1)
            {
                width++;
            }
            else if (width == (Map_width - 1))
            {
                width = 0;
                height++;
            }

        }
    }
    readFile.close();

    for (auto& i : Map)
    {
        int rand = doodle::random(0, 15);
        i.Random_num = rand;
    }
    Bomb_target_time = 2;
}

doodle::Image& Map::Set_wall(info& value)
{
    int wall_count = 0;
    int index = 0;
    for (int i = 0; i < Map.size(); i++)
    {
        if (Map[i].Position == value.Position)
        {
            index = i;
            break;
        }
    }

    if (index < Map_width)
    {
        return WallWall;
    }
    else if (index + 1 % (Map_width) == 0)
    {
        return WallWall;
    }
    else if (index % (Map_width) == 0)
    {
        return WallWall;
    }
    else if (index > Map.size() - (Map_width + 1))                       
    {
        return WallWall;
    }
    else
    {
        if (Map[index - Map_width - 1].Type == Type::WALL)
        {
            wall_count++;
        }
        if (Map[index - Map_width].Type == Type::WALL)
        {
            wall_count++;
        }
        if (Map[index - Map_width + 1].Type == Type::WALL)
        {
            wall_count++;
        }
        if (Map[index - 1].Type == Type::WALL)
        {
            wall_count++;
        }
        
        if (Map[index + 1].Type == Type::WALL)
        {
            wall_count++;
        }
        if (Map[index + Map_width - 1].Type == Type::WALL)
        {
            wall_count++;
        }
        if (Map[index + Map_width].Type == Type::WALL)
        {
            wall_count++;
        }
        if (Map[index + Map_width + 1].Type == Type::WALL)
        {
            wall_count++;
        }
    }
    switch (wall_count) {
    case 1:
        break;
    case 2:
    case 3:
        if (Map[index - Map_width - 1].Type == Type::WALL)
        {
            return Wall_Edge_2;
        }
        else if (Map[index - Map_width + 1].Type == Type::WALL)
        {
            return Wall_Edge_3;
        }
        else if (Map[index + Map_width - 1].Type == Type::WALL)
        {
            return Wall_Edge_1;
        }
        else if ( Map[index + Map_width + 1].Type == Type::WALL)
        {
            return Wall_Edge_4;
        }
        else
            break;
    case 4:
    case 5:
    case 6:
        if (Map[index - Map_width].Type != Type::WALL)
        {
            return Wall_Side_Up;
        }
        else if ( Map[index - 1].Type != Type::WALL)
        {
            return Wall_Side_Left;
        }
        else if ( Map[index + 1].Type != Type::WALL)
        {
            return Wall_Side_Right;
        }
        else if ( Map[index + Map_width].Type != Type::WALL)
        {
            return Wall_Side_Down;
        }
        else
            break;
    case 7:
        if (Map[index - Map_width - 1].Type != Type::WALL)
        {
            return Wall_Corner_4;
        }
        else if ( Map[index - Map_width + 1].Type != Type::WALL)
        {
            return Wall_Corner_1;
        }
        else if ( Map[index + Map_width - 1].Type != Type::WALL)
        {
            return Wall_Corner_3;
        }
        else if ( Map[index + Map_width + 1].Type != Type::WALL)
        {
            return Wall_Corner_2;
        }
        else
            break;
    case 8:
        break;
    }
    
    return WallWall;
}



void Map::Draw(Camera& camera)
{

    for (auto& i : Map)
    {
        switch (i.Type)
        {
        case Type::WALL: 
        {
            push_settings();
            draw_image(Set_wall(i), (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            pop_settings();
            break;
        }
        case Type::ROAD:
        {
            push_settings();
            switch (i.Random_num)
            {
            case 0: {draw_image(Road1, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
                break; }
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            {
                draw_image(Road2, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
                break;
            }
            case 13:
            case 14:
            {
                draw_image(Road3, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
                break;
            }
            }
            pop_settings();
            break;
        }
        case Type::RADAR:
        {
            push_settings();
            draw_image(Road1, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            draw_image(Radar, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
            pop_settings();
            break;
        }
        case Type::NEXT:
        {
            push_settings();
            draw_image(Road1, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            draw_image(Next, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            pop_settings();
            break;
        }
        case Type::TREASURE_CROWN:
        {
            push_settings();
            draw_image(Road2, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            draw_image(Treasure_1, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
            pop_settings();
            break;
        }
        case Type::TREASURE_KEY:
        {
            push_settings();
            draw_image(Road2, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            draw_image(Treasure_2, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
            pop_settings();
            break;
        }
        case Type::TREASURE_COIN:
        {
            push_settings();
            draw_image(Road2, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            draw_image(Treasure_3, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
            pop_settings();
            break;
        }
        case Type::TREASURE_DIA:
        {
            push_settings();
            draw_image(Road2, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            draw_image(Treasure_4, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
            pop_settings();
            break;
        }
        case Type::EXIT:
        {
            push_settings();
            draw_image(Breakable_wall, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            pop_settings();
            break;
        }
        case Type::DOG_CHEW:
        {
            push_settings();
            draw_image(Road2, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            draw_image(Dog_chew, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
            pop_settings();
            break;
        }
        case Type::BOMB:
        {
            push_settings();
            draw_image(Road2, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            draw_image(Bomb, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);
            pop_settings();
            break;
        }
        case Type::CAN_ESCAPE:
        {
            push_settings();
            Bomb_target_time -= doodle::DeltaTime;
            draw_image(Explode.image, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size, Explode.GetDrawPos().x, 0);
            Explode.Update();
            if (Bomb_target_time < 0)
            {
                Explode.currAnim = 0;
                draw_image(Escape, (i.Position.x + camera.Get_position().x) * Block_size - 25, (i.Position.y + camera.Get_position().y) * Block_size - 25, Block_size * 2.5, Block_size * 2.5);
            }
            pop_settings();
            break;
        }

        case Type::LADDER:
        {
            Bomb_target_time -= doodle::DeltaTime;
            draw_image(Explode.image, (i.Position.x + camera.Get_position().x)* Block_size, (i.Position.y + camera.Get_position().y)* Block_size, Block_size, Block_size, Explode.GetDrawPos().x, 0);
            Explode.Update();
            if (Bomb_target_time < 0)
            {
                Explode.currAnim = 0;
                draw_image(Road2, (i.Position.x + camera.Get_position().x)* Block_size - 25, (i.Position.y + camera.Get_position().y)* Block_size - 25, Block_size * 2.5, Block_size * 2.5);              
                draw_image(Ladder, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size);              
             }
        		
            break;
        }
        	
        case Type::BOMB_TO_ROAD:
        {
            push_settings();
            Bomb_target_time -= doodle::DeltaTime;
            draw_image(Explode.image, (i.Position.x + camera.Get_position().x) * Block_size, (i.Position.y + camera.Get_position().y) * Block_size, Block_size, Block_size, Explode.GetDrawPos().x, 0);
            Explode.Update();
            if (Bomb_target_time < 0)
            {
                Explode.currAnim = 0;
                i.Type = Type::ROAD;
                Bomb_target_time = 2;
            }
            pop_settings();
            break;
        }
        }

    }

}