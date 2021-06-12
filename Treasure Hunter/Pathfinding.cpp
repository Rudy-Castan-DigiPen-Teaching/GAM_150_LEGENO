/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Pathfinding.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#include"Pathfinding.h"


std::vector<Node> path_finding(Map map, math::vec2 minsoo_pos, math::ivec2 guard_pos) //find path between positions
{
	std::vector<Node> path;
	std::vector<Node> que;

	bool is_visited[MAP_HEIGHT][MAP_WIDTH] = { false, };

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

		for (auto& i : map.map)
		{
			if (i.position.x == node.pos.x + 1 && i.position.y == node.pos.y && i.type != Type::WALL && is_visited[node.pos.y][node.pos.x + 1] == false)   //right
			{
				is_visited[i.position.y][i.position.x] = true;
				que.push_back(Node{ math::ivec2{ i.position.x , i.position.y}, node });
			}
			if (i.position.x == node.pos.x - 1 && i.position.y == node.pos.y && i.type != Type::WALL && is_visited[node.pos.y][node.pos.x - 1] == false)   //left
			{
				is_visited[i.position.y][i.position.x] = true;
				que.push_back(Node{ math::ivec2{ i.position.x , i.position.y }, node });
			}
			if (i.position.x == node.pos.x && i.position.y == node.pos.y - 1 && i.type != Type::WALL && is_visited[node.pos.y - 1][node.pos.x] == false)   //Up
			{
				is_visited[i.position.y][i.position.x] = true;
				que.push_back(Node{ math::ivec2{ i.position.x, i.position.y  }, node });
			}
			if (i.position.x == node.pos.x && i.position.y == node.pos.y + 1 && i.type != Type::WALL && is_visited[node.pos.y + 1][node.pos.x] == false)   //Down
			{
				is_visited[i.position.y][i.position.x] = true;
				que.push_back(Node{ math::ivec2{ i.position.x, i.position.y }, node });
			}
		}
	}
	return path;
}