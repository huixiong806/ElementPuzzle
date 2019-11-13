#include "player.h"
#include "edge.h"
#include "node.h"
NS_EM_BEGIN
Player::Player(Vec2i position_)
{
	position = position_;
	for (int i = 0; i < 3; ++i)
		tool[i] = 0;
	for (int i = 0; i < 26; ++i)
		passPermit[i] = 0;
	passPermit[(size_t)'N' - 'A'] = -1;
	airUnit = 0;
}
Player::Player(Vec2i position_, std::vector<int32_t>tool_, std::vector<int32_t>passPermit_, int32_t airUnit_)
{
	position = position_;
	for (int i = 0; i < 3; ++i)
		tool[i] = tool_[i];
	for (int i = 0; i < 26; ++i)
		passPermit[i] = passPermit_[i];
	airUnit = airUnit_;
}
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
	if (this->tool[tool]<=0)
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
	//没有N卡，并且对N有需求，则无法满足 (不能用A代替) 
	if (passPermit[(int32_t)('N'-'A')]==0&&index==(int32_t)('N'-'A'))return false;
	//A卡无限或需求卡无限， 则满足。 
	if (passPermit[index] == -1 || passPermit[0] == -1)return true;
	if (passPermit[index] == 0 && passPermit[0] == 0)return false;
	else
	{
		if (passPermit[index]>0)
			passPermit[index]--;
		else passPermit[0]--;
		if (passPermit[0] == 0)//A通行证用完，则自动持有N通行证 
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
const Vec2i Player::getPosition()const
{
	return position;
}
NS_EM_END
