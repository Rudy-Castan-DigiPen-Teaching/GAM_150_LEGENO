#include "Map.h"
#include <fstream>
#include "doodle/doodle.hpp"
#include "Minsoo.h"

void Map::setup()
{
    map.clear();
    std::ifstream readFile;

    readFile.open("assets/Maze1.txt");
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


void Map::draw()
{
	using namespace doodle;
	for (auto& i : map)
	{
        switch (i.type)
        {
        case Type::wall:
            push_settings();
            set_fill_color(0, 0, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle(i.position.x * block_size, i.position.y * block_size, block_size);
            pop_settings();
            break;
        case Type::road:
            push_settings();
            set_fill_color(0, 0, 255);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle(i.position.x * block_size, i.position.y * block_size, block_size);
            pop_settings();
            break;
        case Type::radar:
            push_settings();
            set_fill_color(0, 255, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle(i.position.x * block_size, i.position.y * block_size, block_size);
            pop_settings();
            break;
        case Type::treasure:
            push_settings();
            set_fill_color(255, 255, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle(i.position.x * block_size, i.position.y * block_size, block_size);
            pop_settings();
            break;
        case Type::exit:
            push_settings();
            set_fill_color(255, 255, 0);
            set_outline_width(1);
            set_outline_color(255);
            draw_rectangle(i.position.x * block_size, i.position.y * block_size, block_size);
            pop_settings();
            break;
        }
	}
}