#include "Map.h"
#include <fstream>
#include "doodle/doodle.hpp"

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
			case '0': map.push_back(info{ math::vec2{width,height},wall });
				break;
			case '1': map.push_back(info{ math::vec2{width,height},road });
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
		case wall: 
			set_fill_color(0, 0, 255);
			draw_rectangle(i.position.x * block_size , i.position.y * block_size, block_size);
			break;
		case road: 
			set_fill_color(0, 0, 0);
			draw_rectangle(i.position.x * block_size, i.position.y * block_size, block_size);
			break;
		}
	}
}