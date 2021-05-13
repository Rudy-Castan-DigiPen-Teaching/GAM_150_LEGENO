#include"Map.h"
#include"vec2.h"
#include<vector>


struct Node
{
	math::ivec2 pos;
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
vector<Node> path_finding(Map map,math::vec2 minsoo_pos, math::ivec2 guard_pos)
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

		for (auto& i : map.map)
		{
			if (i.position.x == node.pos.x+1 && i.position.y == node.pos.y && i.type != Type::wall && is_visited[node.pos.y][node.pos.x + 1]==false)   //right
			{
				is_visited[i.position.y][i.position.x] = true;
				que.push_back(Node{ math::ivec2{ i.position.x , i.position.y}, node });
			}
			if (i.position.x == node.pos.x-1 && i.position.y == node.pos.y && i.type != Type::wall && is_visited[node.pos.y][node.pos.x - 1] == false)   //left
			{
				is_visited[i.position.y][i.position.x] = true;
				que.push_back(Node{ math::ivec2{ i.position.x , i.position.y }, node });
			}
			if (i.position.x  == node.pos.x && i.position.y == node.pos.y - 1 && i.type != Type::wall && is_visited[node.pos.y-1][node.pos.x ] == false)   //Up
			{
				is_visited[i.position.y][i.position.x] = true;
				que.push_back(Node{ math::ivec2{ i.position.x, i.position.y  }, node });
			}
			if (i.position.x  == node.pos.x && i.position.y== node.pos.y+1 && i.type != Type::wall && is_visited[node.pos.y+1][node.pos.x ] == false)   //Down
			{
				is_visited[i.position.y][i.position.x] = true;
				que.push_back(Node{ math::ivec2{ i.position.x, i.position.y }, node });
			}
		}
	}
	return path;
}






