/*--------------------------------------------------------------
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
File Name: Pathfinding.h
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include"Map.h"	// Map class
#include"vec2.h"	// vec2 struct
#include<vector>	// std::vector


struct Node
{
	math::ivec2 pos{0,0};
	std::vector<Node> prev;
	bool is_end = false;
	Node() {};
	Node(math::ivec2 p, bool end) {
		pos.x = p.x;
		pos.y = p.y;
		is_end = end;
	}
	Node(math::ivec2 p, Node previous)
	{
		pos.x = p.x;
		pos.y = p.y;
		prev.push_back(previous);
	}

};

std::vector<Node> path_finding(Map map, math::vec2 minsoo_pos, math::ivec2 guard_pos);


