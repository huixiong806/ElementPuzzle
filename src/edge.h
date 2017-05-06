#ifndef EDGE_H
#define EDGE_H
#include "vector2d.hpp"
#include "event.h"
#include "definitions.h"
#include "enumtype.h"
#include <vector>
#include <cstdint>
NS_EM_BEGIN
class Player;
class Event;
class Edge
{
public:
	bool pressurize();
	bool break_wall(uint32_t tool);
	//玩家尝试通过 
	std::pair<bool, std::vector<Event>> tryToPass(Player& player, int32_t way);
private:
	EdgeType type;//类型 
	int32_t passPermit[2];//表示两个方向通过需要的通行证 
	int32_t passTimesLimit;//通过次数限制 
	bool allowPass[2];//两个方向是否可以通过 
	int32_t pressureNeed;//开门需要的气压 
	uint32_t allowBreak;//三位二进制数，表示是否允许用工具破坏 ，从低到高为铲，锤，镐 
};
NS_EM_END
#endif
