#include "node.h"
#include "player.h"
NS_EM_BEGIN
std::vector<Event> Node::arrive(Player& player)
{
	std::vector<Event> events;
	if (type == NodeType::endPoint)
		events.push_back(Event(EventType::playerWin));
	else if (type == NodeType::lava)
		events.push_back(Event(EventType::playerLose));
	else if (type == NodeType::teleportPoint)
	{
		events.push_back(Event(EventType::playerTeleported));
		player.setPosition(teleportTarget);
	}
	if (prop != Prop::empty)
	{
		if ((int32_t)prop >= (int32_t)Prop::A && (int32_t)prop <= (int32_t)Prop::Z)
			player.addForeverPermition((int32_t)prop - 1);
		else if ((int32_t)prop >= (int32_t)Prop::a && (int32_t)prop <= (int32_t)Prop::z)
			player.addOneTimePermition((int32_t)prop - 27);  
		else if ((int32_t)prop >= (int32_t)Prop::shovel && (int32_t)prop <= (int32_t)Prop::pickaxe)
			player.addTool((int32_t)prop - 53);
		else if (prop == Prop::airUnit)
			player.addAirUnit();
		events.push_back(Event(EventType::playerPickUpProp, prop));
		prop = Prop::empty;
	}
	return events;
}
const int32_t Node::typeToInt()const
{
	return (int32_t)type;
}
const int32_t Node::propToInt()const
{
	return (int32_t)prop;
}
const int32_t Node::getTeleportIndex()const
{
	return teleportIndex;
}
NS_EM_END
