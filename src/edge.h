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
	Edge(EdgeType type_, int32_t passPermit0_, int32_t passPermit1_, int32_t passTimesLimit_, bool allowPass0_, bool allowPass1_, int32_t pressureNeed_, uint32_t allowBreak_) :
		type(type_), passTimesLimit(passTimesLimit_), pressureNeed(pressureNeed_), allowBreak(allowBreak_)
	{
		passPermit[0] = passPermit0_;
		passPermit[1] = passPermit1_;
		allowPass[0] = allowPass0_;
		allowPass[1] = allowPass1_;
	}
	Edge(){}
	const int32_t typeToInt()const;
	const int32_t getPassPermit(int index)const;
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
