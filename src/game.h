#ifndef GAME_H
#define GAME_H
#include "mazemap.hpp"
#include "edge.h"
#include "player.h"
#include "vector2d.hpp"
#include "event.h"
#include <memory>
NS_EM_BEGIN
class Game
{
public:
	Game(int32_t width, int32_t height);
	//void move(int32_t direction);
	std::shared_ptr<Map> getMap();
	void setPlayer(Vec2i position);
	std::shared_ptr<Player> getPlayer();
	std::vector<Event> move(int32_t direction);
	std::vector<Event> interactive(int32_t direction,uint32_t tool);
private:
	std::shared_ptr<Map> map;
	std::shared_ptr<Player> player;
};
NS_EM_END
#endif
