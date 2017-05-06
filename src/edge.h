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
	//��ҳ���ͨ�� 
	std::pair<bool, std::vector<Event>> tryToPass(Player& player, int32_t way);
private:
	EdgeType type;//���� 
	int32_t passPermit[2];//��ʾ��������ͨ����Ҫ��ͨ��֤ 
	int32_t passTimesLimit;//ͨ���������� 
	bool allowPass[2];//���������Ƿ����ͨ�� 
	int32_t pressureNeed;//������Ҫ����ѹ 
	uint32_t allowBreak;//��λ������������ʾ�Ƿ������ù����ƻ� ���ӵ͵���Ϊ���������� 
};
NS_EM_END
#endif
