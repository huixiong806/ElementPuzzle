#ifndef GAME_H
#define GAME_H
#include "mazemap.hpp"
#include "edge.h"
#include "player.h"
#include "event.h"
#include <memory>
NS_EM_BEGIN
class Game
{
public:
	Game(){}
	void move(int32_t direction);

private:
	std::shared_ptr<Map> map;
	std::shared_ptr<Player> player;
};
NS_EM_END
#endif