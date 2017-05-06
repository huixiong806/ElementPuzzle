#ifndef EVENT_HPP
#define EVENT_HPP
#include "vector2d.hpp"
#include "definitions.h"
#include "enumtype.h"
#include <cstdint>
NS_EM_BEGIN
class Event
{
public:
	Event(){}
	~Event(){}
	Event(EventType type_,Prop prop_)
	{
		type=type_;
		prop=prop_;
	}
	Event(EventType type_, Vec2i position_)
	{
		type=type_;
		position=position_;
	}
	Event(EventType type_)
	{
		type=type_;
	}
	EventType type;
	Prop prop;
	Vec2i position;
private:
};
NS_EM_END
#endif