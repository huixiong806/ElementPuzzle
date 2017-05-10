#include <iostream>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "game.h"
USING_NS_EM;
const char interactive[3][4]=
{
	{'y','h','g','j'},
	{'f','v','c','b'},
	{'w','s','a','d'}
};
std::shared_ptr<Game> game;
void printmap(std::shared_ptr<Map> map)
{
	int w = map->getWidth();
	int h = map->getHeight();
	Vec2i playerpos = game->getPlayer()->getPosition();
	for (int i = 0; i < 2*h+1;++i)
	{
		for (int j = 0; j < 2 * w + 1; ++j)
		{
			if (!(i & 1) && !(j & 1))
				std::cout << "#";
			else if (!(i & 1))
			{
				int type= map->getEdgeR(i>> 1, j - 1 >> 1).typeToInt();
				std::string out = "";
				if (type == 0)out = "  ";
				else if (type == 1)out = "##";
				else if (type == 2)out = "--";
				else if (type == 3)out = "~~";
				else if (type == 4)out = "==";
				else if (type == 5)out = "PR";
				else if (type == 6)out += "-",out+=(char)(map->getEdgeR(i>> 1, j - 1 >> 1).getPassPermit(1)+'a');
				else if (type == 7)out += "v",out+=(char)(map->getEdgeR(i>> 1, j - 1 >> 1).getPassPermit(0)+'a');
				else if (type == 8)out += "^",out+=(char)(map->getEdgeR(i>> 1, j - 1 >> 1).getPassPermit(1)+'a');
				else if (type == 9)out+=(char)(map->getEdgeR(i >> 1, j - 1 >> 1).getPassPermit(0)+'a'),out+=(char)(map->getEdgeR(i>> 1, j - 1 >> 1).getPassPermit(1)+'a');
				else if (type == 10)out = "v-";
				else if (type == 11)out = "^-";
				else if (type == 12)out = "xx";
				else if (type == 13)out = "vx";
				else if (type == 14)out = "^x";
				std::cout << out;
			}
			else if (!(j & 1))
			{
				int type = map->getEdgeC(i-1>> 1, j >> 1).typeToInt();
				std::string out = "";
				if (type == 0)out = " ";
				else if (type == 1)out = "#";
				else if (type == 2)out = "-";
				else if (type == 3)out = "~";
				else if (type == 4)out = "=";
				else if (type == 5)out = "P";
				else if (type == 6)out = (char)(map->getEdgeC(i-1 >> 1, j >> 1).getPassPermit(1) + 'a');
				else if (type == 7)out = (char)(map->getEdgeC(i-1 >> 1, j >> 1).getPassPermit(0) + 'a');
				else if (type == 8)out = (char)(map->getEdgeC(i-1 >> 1, j >> 1).getPassPermit(1) + 'a');
				else if (type == 9)out = "?";
				else if (type == 10)out = ">";
				else if (type == 11)out = "<";
				else if (type == 12)out = "x";
				else if (type == 13)out = "x";
				else if (type == 14)out = "x";
				std::cout << out;
			}
			else
			{
				if (playerpos == Vec2i(i - 1 >> 1, j - 1 >> 1))
				{
					std::cout << "ME";
					continue;
				}
				int o = map->getNode(i - 1 >> 1, j - 1 >> 1).typeToInt();
				if (o == 0)
				{
					int prop = map->getNode(i - 1 >> 1, j - 1 >> 1).propToInt();
					if (prop == 0)
						std::cout << "  ";
					else if (prop >= 1 && prop <= 26)
						std::cout << " " << (char)(prop - 1 + 'A');
					else if (prop >= 27 && prop <= 52)
						std::cout << " " << (char)(prop - 27 + 'a');
					else if (prop == 53)std::cout << "->";
					else if (prop == 54)std::cout << "-]";
					else if (prop == 55)std::cout << "-}";
					else if (prop == 56)std::cout << ";[";
				}
				else if (o == 4)
					std::cout << "~~";
				else if (o == 1)
					std::cout << "ST";
				else if (o == 2)
					std::cout << "ED";
				else
				{
					o = map->getNode(i - 1 >> 1, j - 1 >> 1).getTeleportIndex();
					std::cout << (o > 9 ? "" : "0") << o;
				}
			}
		}
		std::cout << std::endl;
	}
}
void readLevel()
{
	int32_t w, h,x,y;
	std::ifstream fs;
	fs.open("level.txt",std::ios::in);
	fs >> h >> w;
	game = std::make_shared<Game>(w, h);
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			int32_t type, teleportid, x, y, prop;
			fs >> type >> teleportid >> x >> y >> prop;
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
			fs >> type >> passPermit0 >> passPermit1 >> passTimesLimit >> allowPass0>> allowPass1>> pressureNeed>> allowBreak;
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
			fs >> type >> passPermit0 >> passPermit1 >> passTimesLimit >> allowPass0 >> allowPass1 >> pressureNeed >> allowBreak;
			game->getMap()->setEdgeC(i, j, Edge((EdgeType)type, passPermit0, passPermit1, passTimesLimit, allowPass0, allowPass1, pressureNeed, allowBreak));
		}
	}
	fs >> x >> y;
	game->setPlayer(Vec2i(x,y));
}
int main()
{
	std::cout << "ElementPuzzle_CMD" << std::endl;
	std::cout << "copyright 2017 orangebird,all rights reserved." << std::endl;
	readLevel();
	char key;
	printmap(game->getMap());
	bool win = false, lose = false;
	while (key = getch())
	{
		if (key == -32)continue;
		int dir=-1;int type=1,tool=-1;
		if (key == 72)dir = 0;
		if (key == 80)dir = 1;
		if (key == 75)dir = 2;
		if (key == 77)dir = 3;
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
		std::cout<<type<<" "<<dir<<" "<<tool<<std::endl;
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
		
		system("cls");
		printmap(game->getMap());
		if(win)
		{
			std::cout << "You win!" << std::endl;
			break;
		}
		if (lose)
		{
			std::cout << "You lose!" << std::endl;
			break;
		}
	}
	std::cout << "press any key to exit..." << std::endl;
	_getch();
	return 0;
}