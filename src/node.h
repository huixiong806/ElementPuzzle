#ifndef NODE_H
#define NODE_H
#include "vector2d.hpp"
#include "event.h"
#include "definitions.h"
#include "enumtype.h"
#include <vector>
#include <cstdint>
NS_EM_BEGIN
class Event;
class Player;
class Node
{
public:
	Node(){}
	~Node(){}
	Node(NodeType type_,int32_t teleportIndex_,Vec2i teleportTarget_,Prop prop_):
			type(type_),teleportIndex(teleportIndex_),teleportTarget(teleportTarget_),prop(prop_)
	{}
	std::vector<Event> arrive(Player& player);
	const int32_t typeToInt()const;
	const int32_t propToInt()const;
	const int32_t getTeleportIndex()const;
private:
	NodeType type;
	int32_t teleportIndex;
	Vec2i teleportTarget;
	Prop prop;
};
NS_EM_END
#endif