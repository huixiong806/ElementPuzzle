#include "edge.h"
#include "player.h"
NS_EM_BEGIN
bool Edge::pressurize()
{
	if (type != EdgeType::pressureDoor)
		return false;
	pressureNeed--;
	if (pressureNeed <= 0)
		type = EdgeType::empty;
	return true;
}
bool Edge::break_wall(uint32_t tool)
{
	if (type != EdgeType::ironWall && type != EdgeType::dirtWall && type != EdgeType::woodenWall)
		return false;
	if (((1 << tool)&allowBreak) == false)
		return false;
	type = EdgeType::empty;
	allowPass[0] = allowPass[1] = true;
	passPermit[0] = passPermit[1] = -1;
	passTimesLimit = -1;
	return true;
}
std::pair<bool, std::vector<Event>> Edge::tryToPass(Player& player, int32_t way)
{
	std::vector<Event>events;
	bool success = false;
	do
	{
		if (allowPass[way] == false)
		{
			success = false;
			break;
		}
		if (passTimesLimit == 0)
		{
			success = false;
			break;
		}
		if (passPermit[way] == -1)
		{
			success = true;
			break;
		}
		if (player.usePermition(passPermit[way]))
		{
			success = true;
		}else {
			events.push_back(EventType::playerHaveNoPermition);
			success = false;
		}
	}while (0);
	if (success)events.push_back(Event(EventType::playerMoveSuccessfully));
	else events.push_back(Event(EventType::playerMoveFailed));
	return make_pair(success, events);
}
const int32_t Edge::typeToInt()const
{
	return (int32_t)type;
}
const int32_t Edge::getPassPermit(int index)const
{
	return passPermit[index];
}
NS_EM_END
