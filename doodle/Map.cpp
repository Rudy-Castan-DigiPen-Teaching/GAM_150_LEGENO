#include "Map.h"
#include <fstream> // to load file

using namespace doodle;

void Map::Set_up()
{
    map.clear();
    std::ifstream readFile;

    readFile.open("assets/Maze2.txt");
    int width = 0;
    int height = 0;
   

    if (readFile.is_open())
    {
        while (!readFile.eof())
        {
            char a;
            readFile >> a;
            switch (a)
            {
            case '0': map.push_back(info{ math::ivec2{width,height},Type::ROAD });
                break;
            case '1': map.push_back(info{ math::ivec2{width,height},Type::WALL });
                break;
            case '2':map.push_back(info{ math::ivec2{width,height},Type::RADAR });
                break;
            case '3':map.push_back(info{ math::ivec2{width,height},Type::TREASURE});
                break;
            }
            if (width < map_width - 1)
            {
                width++;
            }
            else if (width == (map_width - 1))
            {
                width = 0;
                height++;
            }
        }
    }
    readFile.close();
}


void Map::Draw(Camera& camera)
{
	for (auto& i : map)
	{
        switch (i.type)
        {
        case Type::WALL:
            push_settings();
            set_fill_color(0, 0, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_image(Wall, (i.position.x + camera.Get_position().x) * block_size -25 , (i.position.y + camera.Get_position().y)* block_size - 25, block_size*2.5 , block_size*2.5);
            pop_settings();
            break;
        case Type::ROAD:
            push_settings();
            set_fill_color(0, 0, 255); 
            set_outline_width(1);
            set_outline_color(255);

            draw_image(Road, (i.position.x + camera.Get_position().x) * block_size-25 , (i.position.y + camera.Get_position().y) * block_size -25, block_size*2.5, block_size*2.5);

            pop_settings();
            break;
        case Type::RADAR:
            push_settings();
            set_fill_color(0, 255, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_image(Road, (i.position.x + camera.Get_position().x) * block_size - 25, (i.position.y + camera.Get_position().y) * block_size - 25, block_size * 2.5, block_size * 2.5);
            draw_image(Radar, (i.position.x + camera.Get_position().x) * block_size, (i.position.y + camera.Get_position().y) * block_size, block_size, block_size);            
            pop_settings();
            break;
        case Type::TREASURE:
            push_settings();
            set_fill_color(255, 255, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle((i.position.x + camera.Get_position().x) * block_size, (i.position.y + camera.Get_position().y) * block_size, block_size);
            pop_settings();
            break;
        case Type::EXIT:
            push_settings();
            set_fill_color(255, 40, 0);
            set_outline_width(1);
            set_outline_color(255);
            //draw_rectangle((i.position.x + camera.Get_position().x) * block_size, (i.position.y + camera.Get_position().y) * block_size, block_size);
            draw_image(Breakable_wall, (i.position.x + camera.Get_position().x) * block_size, (i.position.y + camera.Get_position().y) * block_size, block_size, block_size);            pop_settings();
            break;
        case Type::DOG_CHEW:
            push_settings();
            set_fill_color(0, 0, 255);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle((i.position.x + camera.Get_position().x) * block_size, (i.position.y + camera.Get_position().y) * block_size, block_size);
            draw_image(Dog_chew, (i.position.x + camera.Get_position().x) * block_size, (i.position.y + camera.Get_position().y) * block_size, block_size, block_size);
            pop_settings();
            break;
        case Type::BOMB:
            push_settings();
            set_fill_color(200, 200, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_image(Road, (i.position.x + camera.Get_position().x) * block_size - 30.0, (i.position.y + camera.Get_position().y) * block_size - 30.0, block_size + 200.0, block_size + 200.0);
            draw_image(Bomb,(i.position.x + camera.Get_position().x) * block_size, (i.position.y + camera.Get_position().y) * block_size,block_size,block_size);
            pop_settings();
            break;
        case Type::CAN_ESCAPE:
            push_settings();
            set_fill_color(200, 40, 200);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle((i.position.x + camera.Get_position().x) * block_size, (i.position.y + camera.Get_position().y) * block_size, block_size);
            pop_settings();
            break;
        }
        
	}
}