#include "Map.h"
#include <fstream>
#include "doodle/doodle.hpp"
#include "Minsoo.h"

using namespace doodle;

void Map::setup()
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
            case '0': map.push_back(info{ math::ivec2{width,height},Type::road });
                break;
            case '1': map.push_back(info{ math::ivec2{width,height},Type::wall });
                break;
            case '2':map.push_back(info{ math::ivec2{width,height},Type::radar });
                break;
            case '3':map.push_back(info{ math::ivec2{width,height},Type::treasure });
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


void Map::draw(Camera& camera)
{
	for (auto& i : map)
	{
        switch (i.type)
        {
        case Type::wall:
            push_settings();
            set_fill_color(0, 0, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle((i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size);
            pop_settings();
            break;
        case Type::road:
            push_settings();
            set_fill_color(0, 0, 255);
            set_outline_width(1);
            set_outline_color(255);
            draw_image(Road, (i.position.x + camera.GetPosition().x) * block_size - 30.0, (i.position.y + camera.GetPosition().y) * block_size - 30.0, block_size + 200.0, block_size + 200.0);
            pop_settings();
            break;
        case Type::radar:
            push_settings();
            set_fill_color(0, 255, 0);
            set_outline_width(1);
            set_outline_color(255);
            //draw_rectangle((i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size);
            draw_image(Radar, (i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size, block_size);            
            pop_settings();
            break;
        case Type::treasure:
            push_settings();
            set_fill_color(255, 255, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle((i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size);
            pop_settings();
            break;
        case Type::exit:
            push_settings();
            set_fill_color(255, 40, 0);
            set_outline_width(1);
            set_outline_color(255);
            //draw_rectangle((i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size);
            draw_image(Breakable_wall, (i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size, block_size);            pop_settings();
            break;
        case Type::dog_chew:
            push_settings();
            set_fill_color(0, 0, 255);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle((i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size);
            draw_image(Dog_chew, (i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size, block_size);
            pop_settings();
            break;
        case Type::bomb:
            push_settings();
            set_fill_color(200, 200, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_image(Road, (i.position.x + camera.GetPosition().x) * block_size - 30.0, (i.position.y + camera.GetPosition().y) * block_size - 30.0, block_size + 200.0, block_size + 200.0);
            draw_image(Bomb,(i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size,block_size,block_size);
            pop_settings();
            break;
        case Type::can_escape:
            push_settings();
            set_fill_color(200, 40, 200);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle((i.position.x + camera.GetPosition().x) * block_size, (i.position.y + camera.GetPosition().y) * block_size, block_size);
            pop_settings();
            break;
        }
        
	}
}