#include "Map.h"
#include <fstream>
#include "doodle/doodle.hpp"
#include "Minsoo.h"

void Map::setup()
{
	std::ifstream readFile;             

	readFile.open("assets/Maze1.txt");    
	double width = 0;
	double height = 0;
	if (readFile.is_open())   
	{
		while (!readFile.eof())    
		{
			char a;
			readFile >> a;
			switch (a)
			{
			case '0': map.push_back(info{ math::vec2{width,height},Type::wall });
				break;
			case '1': map.push_back(info{ math::vec2{width,height},Type::road });
				break;	
			}
			if (width < map_width-1)
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
			set_fill_color(0, 0, 255);
			set_outline_width(1);
			set_outline_color(255);
			draw_rectangle(i.position.x * block_size , i.position.y * block_size, block_size);
			pop_settings();
			break;
		case Type::road:
			push_settings();
			set_fill_color(0, 0, 0);
			set_outline_width(1);
			set_outline_color(255);
			draw_rectangle(i.position.x * block_size, i.position.y * block_size, block_size);
			pop_settings();
			break;
		}
	}
}