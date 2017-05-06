#ifndef PLAYER_H
#define PLAYER_H
#include "event.h"
#include "vector2d.hpp"
#include "definitions.h"
#include <vector>
#include <cstdint>
NS_EM_BEGIN
class Edge;
class Node;
class Player
{
public:
	std::vector<Event> pressurize(Edge& target);
	std::vector<Event> break_wall(Edge& target, uint32_t tool);
	std::vector<Event> move(Edge& edge, Node& target, int32_t way, Vec2i targetPos);
	bool usePermition(int32_t index);
	void addTool(int index);
	void addAirUnit();
	void addForeverPermition(int32_t index);
	void addOneTimePermition(int32_t index);
	void setPosition(Vec2i position_);
	Player(Vec2i position_, std::vector<int32_t>tool_, std::vector<int32_t>passPermit_,int32_t airUnit_)
	{
		position = position_;
		for (int i = 0; i < 3; ++i)
			tool[i] = tool_[i];
		for (int i = 0; i < 26; ++i)
			passPermit[i] = passPermit_[i];
		airUnit = airUnit_;
	}
private:
	int32_t passPermit[26];//表示持有的通行证
	int32_t airUnit;//持有的气罐数量
	int32_t tool[3];//持有的工具数量
	Vec2i position;//位置坐标 
};
NS_EM_END
#endif