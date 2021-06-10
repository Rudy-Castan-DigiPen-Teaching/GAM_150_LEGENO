/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include"Map.h"	// Map class
#include"vec2.h"	// vec2 struct
#include<vector>	// std::vector


struct Node
{
	math::ivec2 pos{0,0};
	vector<Node> prev;
	bool is_end = false;
	Node() {};
	Node(math::ivec2 p, bool end) {
		pos.x = p.x;
		pos.y = p.y;
		is_end = end;
	}
	Node(math::ivec2 p, Node previous) {
		pos.x = p.x;
		pos.y = p.y;
		prev.push_back(previous);
	}
};

template<int height, int width>
vector<Node> path_finding(Map map,math::vec2 minsoo_pos, math::ivec2 guard_pos) //find path between positions
{
	vector<Node> path;
	vector<Node> que;

	bool is_visited[height][width] = { false, };

	is_visited[guard_pos.y][guard_pos.x] = true;

	que.push_back(Node(math::ivec2{ guard_pos.x, guard_pos.y }, true));

	while (!que.empty() == true)
	{
		Node node = que.front();
		que.erase(que.begin());

		if (node.pos.x == minsoo_pos.x && node.pos.y == minsoo_pos.y)
		{
			Node path_node = node;
			while (path_node.is_end != true)
			{
				path.push_back(path_node);
				path_node = node.prev.front();
				node = path_node;
			}
			break;
		}

		for (auto& i : map.Map)
		{
			if (i.Position.x == node.pos.x+1 && i.Position.y == node.pos.y && i.Type != Type::WALL && is_visited[node.pos.y][node.pos.x + 1]==false)   //right
			{
				is_visited[i.Position.y][i.Position.x] = true;
				que.push_back(Node{ math::ivec2{ i.Position.x , i.Position.y}, node });
			}
			if (i.Position.x == node.pos.x-1 && i.Position.y == node.pos.y && i.Type != Type::WALL && is_visited[node.pos.y][node.pos.x - 1] == false)   //left
			{
				is_visited[i.Position.y][i.Position.x] = true;
				que.push_back(Node{ math::ivec2{ i.Position.x , i.Position.y }, node });
			}
			if (i.Position.x  == node.pos.x && i.Position.y == node.pos.y - 1 && i.Type != Type::WALL && is_visited[node.pos.y-1][node.pos.x ] == false)   //Up
			{
				is_visited[i.Position.y][i.Position.x] = true;
				que.push_back(Node{ math::ivec2{ i.Position.x, i.Position.y  }, node });
			}
			if (i.Position.x  == node.pos.x && i.Position.y== node.pos.y+1 && i.Type != Type::WALL && is_visited[node.pos.y+1][node.pos.x ] == false)   //Down
			{
				is_visited[i.Position.y][i.Position.x] = true;
				que.push_back(Node{ math::ivec2{ i.Position.x, i.Position.y }, node });
			}
		}
	}
	return path;
}