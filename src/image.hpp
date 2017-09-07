#ifndef IMAGE_H
#define IMAGE_H
#include "vector2d.hpp"
#include "enumtype.h"
#include <vector>
#include <sstream>
#include <cstdint>
#include <graphics.h>
NS_EM_BEGIN
namespace image
{
	PIMAGE letter[26];
	PIMAGE number[16];
	PIMAGE hexagon,lava,player,circle,triangle,point;
	PIMAGE shovel,hammer,pickaxe,airUnit;
	void readImage(const std::string& filename,PIMAGE& target)
	{
		target=newimage();
		getimage(target,filename.c_str());
	}
	void init()
	{
		std::stringstream filename;
		//letters 
		for(int i=0;i<26;++i)
		{
			filename.str("");
			filename<<"image\\letter\\"<<i<<".png";
			readImage(filename.str(),letter[i]);		
		}
		//numbers
		for(int i=0;i<16;++i)
		{
			filename.str("");
			filename<<"image\\number\\"<<i<<".png";
			readImage(filename.str(),number[i]);
		}
		//items
		readImage("image\\item\\hexagon.png",hexagon);
		readImage("image\\item\\circle.png",circle);
		readImage("image\\item\\triangle.png",triangle);
		readImage("image\\item\\player.png",player);
		readImage("image\\item\\lava.png",lava);
		readImage("image\\item\\point.png", point);
		//props
		readImage("image\\prop\\shovel.png",shovel);
		readImage("image\\prop\\hammer.png",hammer);
		readImage("image\\prop\\pickaxe.png",pickaxe);
		readImage("image\\prop\\airUnit.png",airUnit);
	}
	void printImage(PIMAGE& image,const Vec2d startPoint,const Vec2d picLen)
	{
		PIMAGE temp = newimage(picLen.x,picLen.y);
		putimage(temp,0,0,picLen.x,picLen.y,image,0,0, getwidth(image),getheight(image));
		putimage_withalpha(NULL,temp,startPoint.x,startPoint.y,0,0,picLen.x,picLen.y);
		delimage(temp);
	}
	void printPoint(const Vec2d startPoint, const Vec2d pictureLength)
	{
		printImage(point, startPoint, pictureLength);
	}
	//打印node的主要部分到屏幕 
	void printNode_maintype(NodeType nodeType,int tag,const Vec2d startPoint,const Vec2d pictureLength)
	{
		switch (nodeType)
		{
		case NodeType::empty:
			break;
		case NodeType::startPoint:
			printImage(hexagon,startPoint,pictureLength);
			printImage(letter[int('s'-'a')],startPoint,pictureLength);
			break;
		case NodeType::endPoint:
			printImage(hexagon,startPoint,pictureLength);
			printImage(letter[int('e'-'a')],startPoint,pictureLength);
			break;
		case NodeType::teleportPoint:
			printImage(hexagon,startPoint,pictureLength);
			printImage(number[tag],startPoint,pictureLength);
			break;
		case NodeType::lava:
			printImage(lava,startPoint,pictureLength);
		}
	}
	void printPlayer(const Vec2d startPoint, const Vec2d pictureLength)
	{
		printImage(player, startPoint, pictureLength);
	}
	//打印node上的道具到屏幕 
	void printNode_prop(Prop propType,const Vec2d startPoint,const Vec2d pictureLength)
	{
		if(propType==Prop::empty)return;
		//A~Z
		if(int(propType)>0&&int(propType)<=26)
		{
			printImage(circle,startPoint,pictureLength);
			printImage(letter[int(propType)-1],startPoint,pictureLength);
		}
		//a~z 
		else if(int(propType)>26&&int(propType)<=52)
		{
			printImage(triangle,startPoint,pictureLength);
			printImage(letter[int(propType)-27],startPoint,pictureLength);
		}else
		{
			switch (propType)
			{
			case Prop::shovel:
				printImage(shovel,startPoint,pictureLength);
				break;
			case Prop::hammer:
				printImage(hammer,startPoint,pictureLength);
				break;
			case Prop::pickaxe:
				printImage(pickaxe,startPoint,pictureLength);
				break;
			case Prop::airUnit:
				printImage(airUnit,startPoint,pictureLength);
				break;
			}
		}
	}
}
NS_EM_END
#endif
