#include"game.h"
NS_EM_BEGIN
Game::Game(int32_t width, int32_t height)
{ 
	map = (std::make_shared<Map>(width, height));
};
std::shared_ptr<Map> Game::getMap()
{
	return map;
}
void Game::setPlayer(Vec2i position)
{
	player = std::make_shared<Player>(position);
}
std::vector<Event> Game::move(int32_t direction)
{
	std::vector<Event>events;
	Vec2i position = player->getPosition();
	Vec2i nextPosition = position+moveDelta[direction];
	if (nextPosition.x < 0 || nextPosition.x >= map->getHeight() || nextPosition.y < 0 || nextPosition.y >= map->getWidth())
	{
		events.push_back(Event(EventType::playerMoveFailed));
		return events;
	}
	int32_t way = (direction == 0 || direction == 2) ? 1 : 0;
	Edge* edge;
	if (direction <= 1)//up,down
	{
		if (way == 1)edge = &map->getEdgeR(position.x,position.y);
		else edge = &map->getEdgeR(position.x+1, position.y);
	}
	else//left,right
	{
		if (way == 1)edge = &map->getEdgeC(position.x, position.y);
		else edge = &map->getEdgeC(position.x, position.y+1);
	}
	events=player->move(*edge,map->getNode(nextPosition.x, nextPosition.y),way, nextPosition);
	return events;
}
std::vector<Event> Game::interactive(int32_t direction,uint32_t tool)
{
	std::vector<Event>events;
	Vec2i position = player->getPosition();
	Vec2i nextPosition = position+moveDelta[direction];
	int32_t way = (direction == 0 || direction == 2) ? 1 : 0;
	Edge* edge;
	if (direction <= 1)//up,down
	{
		if (way == 1)edge = &map->getEdgeR(position.x,position.y);
		else edge = &map->getEdgeR(position.x+1, position.y);
	}
	else//left,right
	{
		if (way == 1)edge = &map->getEdgeC(position.x, position.y);
		else edge = &map->getEdgeC(position.x, position.y+1);
	}
	if(tool<=2)events=player->break_wall(*edge,tool);
	else events=player->pressurize(*edge);
	return events;
}
std::shared_ptr<Player> Game::getPlayer()
{
	return player;
}
NS_EM_END
