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
const char interactive[3][4]=
{
	{'y','h','g','j'},
	{'f','v','c','b'},
	{'w','s','a','d'}
};
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
void printNode()
{
	Vec2d mapSize=Vec2d(game->getMap()->getWidth(),game->getMap()->getHeight());
	Vec2d picLen=Vec2d((screenSize.x*2.0/3.0)/(double)std::max(mapSize.x,mapSize.y),(screenSize.x*2.0/3.0)/(double)std::max(mapSize.x,mapSize.y));
	Vec2d rectangleSize=Vec2d(picLen.x*mapSize.x,picLen.y*mapSize.y);
	Vec2d delta=(screenSize-rectangleSize)/2.0;
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
			if(game->getPlayer()->getPosition()==Vec2i(i,j))
				type=233;
			ss<<"image\\node\\prop_front\\"<<type<<".png";
			outputImage(ss.str(),picturePosition,picLen);
		}
	}
}
void printEdge()
{
	Vec2d mapSize=Vec2d(game->getMap()->getWidth(),game->getMap()->getHeight());
	Vec2d picLen=Vec2d((screenSize.x*2.0/3.0)/(double)std::max(mapSize.x,mapSize.y),(screenSize.x*2.0/3.0)/(double)std::max(mapSize.x,mapSize.y));
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
void printmap()
{
	outputImage("image\\other\\background.png",Vec2d(0,0),screenSize);
	printNode();
	printEdge();
}
int main()
{
	//初始化为640*480大小
    initgraph(screenSize.x, screenSize.y);
 	readLevel();
 	printmap();
    char key; 
	bool win = false, lose = false;
	while (key = getch())
	{
		if (key == -32)continue;
		int dir=-1;int type=1,tool=-1;
		if (key == 38)dir = 0;
		if (key == 40)dir = 1;
		if (key == 37)dir = 2;
		if (key == 39)dir = 3;
		for(int i=0;i<3;++i)
		{
			for(int j=0;j<4;++j)
			{
				if(key==interactive[i][j])
				{
					dir=j;
					tool=i;
					type=2;
					break;
				}
			}
			if(type==2)break;
		}
		//std::stringstream ss;
		//ss<<type<<" "<<dir<<" "<<(int)key;
		//outtextxy(0,0,ss.str().c_str());
		//std::cout<<type<<" "<<dir<<" "<<tool<<std::endl;
		if (dir == -1)continue;
		std::vector<Event>events;
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
		cleardevice(); 
		printmap();
		if(win)
		{
			outtextxy(0,0,"You win!");
			break;
		}
		if (lose)
		{
			outtextxy(0,0,"You lose!");
			break;
		}
	}
	getch();
    closegraph();
	return 0;
} 
