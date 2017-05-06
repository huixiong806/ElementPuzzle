#include "player.h"
#include "edge.h"
#include "node.h"
NS_EM_BEGIN
std::vector<Event> Player::pressurize(Edge& target)
{
	std::vector<Event>events;
	if (airUnit<1)
	{
		events.push_back(Event(EventType::playerHaveNoProp));
		return events;
	}
	if (target.pressurize())
	{
		airUnit--;
		events.push_back(Event(EventType::playerUseProp));
		return events;
	}
	else
	{
		events.push_back(Event(EventType::cannotInteractive));
		return events;
	}
}
std::vector<Event> Player::break_wall(Edge& target, uint32_t tool)
{
	std::vector<Event>events;
	if (this->tool[tool]<1)
	{
		events.push_back(Event(EventType::playerHaveNoProp));
		return events;
	}
	if (target.break_wall(tool))
	{
		this->tool[tool]--;
		events.push_back(Event(EventType::playerUseProp));
		return events;
	}
	else
	{
		events.push_back(Event(EventType::cannotInteractive));
		return events;
	}
}
std::vector<Event> Player::move(Edge& edge, Node& target, int32_t way, Vec2i targetPos)
{
	std::pair<bool, std::vector<Event>> PassEvents = edge.tryToPass(*this, way);
	if (PassEvents.first == false)
		return PassEvents.second;
	position = targetPos;
	std::vector<Event> arriveEvents = target.arrive(*this);
	PassEvents.second.insert(PassEvents.second.end(), arriveEvents.begin(), arriveEvents.end());
	return PassEvents.second;
}
bool Player::usePermition(int32_t index)
{
	if (passPermit[index] == -1 || passPermit[0] == -1)return true;
	if (passPermit[index] == 0 && passPermit[0] == 0)return false;
	else
	{
		if (passPermit[index]>0)
			passPermit[index]--;
		else passPermit[0]--;
		if (passPermit[0] == 0)//Aͨ��֤���꣬���Զ�����Nͨ��֤ 
			passPermit[(int32_t)('N' - 'A')] = -1;
		return true;
	}
}
void Player::addTool(int index)
{
	tool[index]++;
}
void Player::addAirUnit()
{
	airUnit++;
}
void Player::addForeverPermition(int32_t index)
{
	passPermit[index] = -1;
	if (index == 'A' - 'A')passPermit[(int32_t)('N' - 'A')] = 0;
}
void Player::addOneTimePermition(int32_t index)
{
	if (passPermit[index] != -1)
		passPermit[index]++;
	if (passPermit[0]>0 || passPermit[0] == -1)
		passPermit[(int32_t)('N' - 'A')] = 0;
}
void Player::setPosition(Vec2i position_)
{
	position = position_;
}
NS_EM_END