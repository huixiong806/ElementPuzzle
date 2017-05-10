#include <iostream>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <graphics.h>
#include <sstream>
#include "game.h"
USING_NS_EM;
std::shared_ptr<Game> game;
const Vec2d screenSize=Vec2d(1024,768);
void readLevel()
{
	int32_t w, h,x,y;
	std::ifstream inputStream;
	inputStream.open("level.txt",std::ios::in);
	inputStream >> h >> w;
	game = std::make_shared<Game>(w, h);
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			int32_t type, teleportid, x, y, prop;
			inputStream >> type >> teleportid >> x >> y >> prop;
			game->getMap()->setNode(i, j, Node((NodeType)type, teleportid,Vec2i(x,y),(Prop)prop));
			//std::cout << (int)(NodeType)type << std::endl;
		}
	}
	for (int i = 0; i <= h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			int32_t type;
			int32_t passPermit0, passPermit1, passTimesLimit;
			bool allowPass0, allowPass1;
			int32_t pressureNeed;
			uint32_t allowBreak;
			inputStream >> type >> passPermit0 >> passPermit1 >> passTimesLimit >> allowPass0>> allowPass1>> pressureNeed>> allowBreak;
			game->getMap()->setEdgeR(i, j, Edge((EdgeType)type, passPermit0, passPermit1, passTimesLimit, allowPass0, allowPass1, pressureNeed, allowBreak));
		}
	}
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j <= w; ++j)
		{
			int32_t type;
			int32_t passPermit0, passPermit1, passTimesLimit;
			bool allowPass0, allowPass1;
			int32_t pressureNeed;
			uint32_t allowBreak;
			inputStream >> type >> passPermit0 >> passPermit1 >> passTimesLimit >> allowPass0 >> allowPass1 >> pressureNeed >> allowBreak;
			game->getMap()->setEdgeC(i, j, Edge((EdgeType)type, passPermit0, passPermit1, passTimesLimit, allowPass0, allowPass1, pressureNeed, allowBreak));
		}
	}
	inputStream >> x >> y;
	game->setPlayer(Vec2i(x,y));
}
void outputImage(std::string filename,const Vec2d startPoint,const Vec2d picLen)
{
	PIMAGE imgA = newimage();
	PIMAGE imgB = newimage(picLen.x,picLen.y);
	getimage(imgA,filename.c_str());
	putimage(imgB,0,0,picLen.x,picLen.y,imgA,0,0, getwidth(imgA),getheight(imgA));
	putimage_withalpha(NULL,imgB,startPoint.x,startPoint.y,0,0,picLen.x,picLen.y);
	delimage(imgA);
	delimage(imgB);
}
void printmap()
{
	Vec2d mapSize=Vec2d(game->getMap()->getWidth(),game->getMap()->getHeight());
	Vec2d picLen=Vec2d((screenSize.x*2.0/3.0)/(double)std::max(mapSize.x,mapSize.y),(screenSize.x*2.0/3.0)/(double)std::max(mapSize.x,mapSize.y));
	Vec2d rectangleSize=Vec2d(picLen.x*mapSize.x,picLen.y*mapSize.y);
	Vec2d delta=(screenSize-rectangleSize)/2.0;
	outputImage("image\\other\\background.png",Vec2d(0,0),screenSize);
	for(int i=0;i<mapSize.y;++i)
	{
		for(int j=0;j<mapSize.x;++j)
		{
			Vec2d picturePosition=Vec2d(j*picLen.x+delta.x,i*picLen.y+delta.y);
			int32_t type=game->getMap()->getNode(i,j).typeToInt();
			std::stringstream ss;
			ss<<"image\\node\\main_back\\"<<type<<".png";
			outputImage(ss.str(),picturePosition,picLen);
			ss.str("");
			if(type==3)type=type*10+game->getMap()->getNode(i,j).getTeleportIndex();
			ss<<"image\\node\\main_front\\"<<type<<".png";
			outputImage(ss.str(),picturePosition,picLen);
			ss.str("");
			type=game->getMap()->getNode(i,j).propToInt();
			if(type>=1&&type<=26)type=1;
			if(type>=27&&type<=52)type=2;
			ss<<"image\\node\\prop_back\\"<<type<<".png";
			outputImage(ss.str(),picturePosition,picLen);
			ss.str("");
			type=game->getMap()->getNode(i,j).propToInt();
			if(type>=27&&type<=52)type-=26;
			ss<<"image\\node\\prop_front\\"<<type<<".png";
			outputImage(ss.str(),picturePosition,picLen);
		}
	}
}
int main()
{
	//初始化为640*480大小
    initgraph(screenSize.x, screenSize.y);
 	readLevel();
 	printmap();
    //等待用户按键
    getch();
    //关闭图形界面
    closegraph();
	return 0;
} 
