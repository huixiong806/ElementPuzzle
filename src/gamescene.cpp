#include <iostream>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <graphics.h>
#include <sstream>
#include <time.h>
#include "image.hpp"
#include "game.h"
USING_NS_EM;
using namespace std;
shared_ptr<Game> game;
const Vec2d screenSize=Vec2d(1024,768);
const char interactive[3][4]=
{
	{'Y','H','G','J'},
	{'F','V','C','B'},
	{'W','S','A','D'}
};
void readLevel(int levelID)
{
	int32_t w, h,x,y;
	stringstream levelName;
	levelName<<"level\\1-"<<levelID<<".epl";
	ifstream inputStream;
	inputStream.open(levelName.str(),ios::in);
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
void printPoint()
{
	Vec2d mapSize = Vec2d(game->getMap()->getWidth(), game->getMap()->getHeight());
	Vec2d picLen = Vec2d((screenSize.x*4.0 / 7.0) / (double)max(mapSize.x, mapSize.y), (screenSize.x*4.0 / 7.0) / (double)max(mapSize.x, mapSize.y));
	Vec2d rectangleSize = Vec2d(picLen.x*mapSize.x, picLen.y*mapSize.y);
	Vec2d delta = (screenSize - rectangleSize) / 2.0;
	for (int i = 0; i<=mapSize.y; ++i)
	{
		for (int j = 0; j<=mapSize.x; ++j)
		{
			Vec2d picturePosition = Vec2d(j*picLen.x + delta.x - picLen.x / 2.0, i*picLen.y + delta.y - picLen.y / 2.0);
			image::printPoint(picturePosition, picLen);
		}
	}
}
void printNode()
{
	Vec2d mapSize=Vec2d(game->getMap()->getWidth(),game->getMap()->getHeight());
	Vec2d picLen=Vec2d((screenSize.x*4.0/7.0)/(double)max(mapSize.x,mapSize.y),(screenSize.x*4.0/7.0)/(double)max(mapSize.x,mapSize.y));
	Vec2d rectangleSize=Vec2d(picLen.x*mapSize.x,picLen.y*mapSize.y);
	Vec2d delta=(screenSize-rectangleSize)/2.0;
	for(int i=0;i<mapSize.y;++i)
	{
		for(int j=0;j<mapSize.x;++j)
		{
			Vec2d picturePosition=Vec2d(j*picLen.x+delta.x,i*picLen.y+delta.y);
			const Node& node=game->getMap()->getNode(i,j);
			image::printNode_maintype(node.getType(),node.getTeleportIndex(),picturePosition,picLen);
			image::printNode_prop(node.getProp(),picturePosition,picLen);
			if (game->getPlayer()->getPosition() == Vec2i(i, j))image::printPlayer(picturePosition,picLen);
		}
	}
}
//待重构
void printEdge()
{
	Vec2d mapSize=Vec2d(game->getMap()->getWidth(),game->getMap()->getHeight());
	Vec2d picLen=Vec2d((screenSize.x*4.0/7.0)/(double)max(mapSize.x,mapSize.y),(screenSize.x*4.0/7.0)/(double)max(mapSize.x,mapSize.y));
	Vec2d rectangleSize=Vec2d(picLen.x*mapSize.x,picLen.y*mapSize.y);
	Vec2d delta=(screenSize-rectangleSize)/2.0;
	for(int i=0;i<=mapSize.y;++i)
	{
		for(int j=0;j<mapSize.x;++j)
		{
			Vec2d picturePosition=Vec2d(j*picLen.x+delta.x,i*picLen.y+delta.y-picLen.y/2.0);
			int32_t type=game->getMap()->getEdgeR(i,j).typeToInt();
			bool condition=0;
			std::stringstream ss;
			ss<<"image\\edgeR\\back\\"<<type<<".png";
			outputImage(ss.str(),picturePosition,picLen);
			ss.str("");
			if(type==9)condition=true;
			if(type>=6&&type<=9)
				type=game->getMap()->getEdgeR(i,j).getPassPermit(0)+50;
			ss<<"image\\edgeR\\front\\"<<type<<".png";
			if(!condition)	
				outputImage(ss.str(),picturePosition,picLen);
			else
			{
				
				outputImage(ss.str(),Vec2d(j*picLen.x+delta.x+picLen.x/10.4,i*picLen.y+delta.y-picLen.y/2.0+picLen.y/6.3),picLen*3.0/5.0);
				type=game->getMap()->getEdgeR(i,j).getPassPermit(1)+50;
				ss.str("");
				ss<<"image\\edgeR\\front\\"<<type<<".png";
				outputImage(ss.str(),Vec2d(j*picLen.x+delta.x+picLen.x/3.8,i*picLen.y+delta.y-picLen.y/2.0+picLen.y/6.3),picLen*3.0/5.0);
			}
			
		}
	}
	for(int i=0;i<mapSize.y;++i)
	{
		for(int j=0;j<=mapSize.x;++j)
		{
			Vec2d picturePosition=Vec2d(j*picLen.x+delta.x-picLen.x/2.0,i*picLen.y+delta.y);
			int32_t type=game->getMap()->getEdgeC(i,j).typeToInt();
			std::stringstream ss;
			bool condition=0;
			ss<<"image\\edgeC\\back\\"<<type<<".png";
			outputImage(ss.str(),picturePosition,picLen);
			ss.str("");
			if(type==9)condition=true;
			if(type>=6&&type<=9)
				type=game->getMap()->getEdgeC(i,j).getPassPermit(0)+50;
			ss<<"image\\edgeC\\front\\"<<type<<".png";
			if(!condition)	
				outputImage(ss.str(),picturePosition,picLen);
			else
			{
				
				outputImage(ss.str(),Vec2d(j*picLen.x+delta.x+picLen.x/3.8-picLen.x/2.0,i*picLen.y+delta.y+picLen.y/5.1),picLen*4.0/9.0);
				type=game->getMap()->getEdgeC(i,j).getPassPermit(1)+50;
				ss.str("");
				ss<<"image\\edgeC\\front\\"<<type<<".png";
				outputImage(ss.str(),Vec2d(j*picLen.x+delta.x+picLen.x/3.8-picLen.x/2.0,i*picLen.y+delta.y+picLen.y/2.9),picLen*4.0/9.0);
			}
		}
	}
}
void printmap(int level)
{
	setbkcolor(EGERGB(0xff, 0xff, 0xff));
	setcolor(EGERGB(0x0, 0x0, 0x0));
	setfont(40, 0, "consolas");
	std::stringstream title;
	title<<"Level "<<level;
	outtextxy(420,0,title.str().c_str());
	//outputImage("image\\other\\background.png",Vec2d(0,0),screenSize);
	printNode();
	printEdge();
	printPoint();
}
void printEventInformations(std::vector<Event>& events)
{
	stringstream information;
	setcolor(EGERGB(0x0, 0x3f, 0x0));
	setfont(12, 0, "宋体"); 
	for (auto&& item : events)
		information<<eventInformationText[(int)item.type]<<"   ";
	outtextxy(0,0,information.str().c_str());
}
void printOtherInformations()
{
	outputImage("image\\info\\scene.png", Vec2d(820,350),Vec2d(199,311));
	outputImage("image\\info\\operation.png", Vec2d(0, 350), Vec2d(145, 300));
	stringstream information;
	setcolor(EGERGB(0x0, 0x3f, 0x0));
	setfont(22, 0, "宋体");
	//输出道具信息
	const string propName[3] = { "铲","锤","镐" };
	for (int i = 0; i < 3; ++i)
	{
		information = stringstream();
		information << propName[i] << ": " << game->getPlayer()->getToolCount(i);
		outtextxy(22, i * 22 + 20, information.str().c_str());
	}
	//输出通行证信息
	for (int i = 0,j=0; i < 26; ++i)
	{
		information = stringstream();
		j++;
		if (game->getPlayer()->getPermition(i) == -1)
			information << (char)(i + 'A') << ": 永久";
		else if (game->getPlayer()->getPermition(i) > 0)
			information << (char)(i + 'A') << ": "<< game->getPlayer()->getPermition(i);
		else j--;
		outtextxy(22, j * 22 + 70, information.str().c_str());
	}
}
int keyLock;//按键锁，3帧才能使用一次键盘 
void lockTheKey()
{
	keyLock=3;
}
//win? lose?
std::pair<bool,bool> update(int level)
{
	bool win = false, lose = false;
	std::vector<Event>events;
	if(keyLock>0)keyLock--;
	if(keyLock==0)
	{ 
		int dir=-1;int type=1,tool=-1;
		if (keystate(key_up))dir = 0,lockTheKey();
		else if (keystate(key_down))dir = 1,lockTheKey();
		else if (keystate(key_left))dir = 2,lockTheKey();
		else if (keystate(key_right))dir = 3,lockTheKey();
		if(keystate('R'))lose=true;
		for(int i=0;i<3;++i)
		{
			for(int j=0;j<4;++j)
			{
					if(keystate(interactive[i][j]))
					{
						dir=j;
						tool=i;
						type=2;
						lockTheKey();
						break;
					}
			}
			if(type==2)break;
		}
		if (dir == -1)return std::make_pair(win,lose);
		if(type==1)
		{
			events=game->move(dir);
		}else if(type==2)
		{
			events=game->interactive(dir,tool);
		}
		for (auto&& item : events)
		{
			if (item.type == EventType::playerLose)lose = true;
			if (item.type == EventType::playerWin)win = true;
		}
		//if(win||lose)return;
		cleardevice();
		printmap(level);
		printEventInformations(events);
		printOtherInformations();
	}
	return std::make_pair(win,lose);
}
int main()
{
	int level=7;
	setinitmode(0);
    initgraph(screenSize.x, screenSize.y);
	setcaption("元素迷宫");
    image::init();
	//level<=total levels
    while(level<=7)
    {
 		readLevel(level);
 		cleardevice();
 		printmap(level);
		printOtherInformations();
		while(true)
		{
			clock_t timeStart=clock();
			std::pair<bool,bool>result=update(level);
			if(result.first||result.second)
			{
				if(result.first)level++;//won the game
				break;//won/lost the game
			}
			Sleep(60-(clock()-timeStart));
		}
	}
	setcolor(EGERGB(0xff, 0x0, 0x0));
	setfont(60, 0, "宋体");
	outtextxy(250,300,"YOU WON THE GAME!");
	while(getch()!='q');
    closegraph();
	return 0;
} 
