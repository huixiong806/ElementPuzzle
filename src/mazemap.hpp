#ifndef MAZE_HPP
#define MAZE_HPP
#include <cstddef>
#include <vector> 
#include "definitions.h"
#include "edge.h"
#include "node.h"
#include"vector2d.hpp"
NS_EM_BEGIN
using BitType = uint8_t;
class Map
{
private:
	std::vector<std::vector<Node>> node;
	std::vector<std::vector<Edge>> edgeRow;
	std::vector<std::vector<Edge>> edgeCol;
	size_t width,height;
protected:
public:
	Map(size_t width_,size_t height_):
		width(width_),height(height_)
	{
		node.resize(height);
		for(auto&& item:node)
			item.resize(width);
		edgeRow.resize(height+1);
		for(auto&& item:edgeRow)
			item.resize(width);
		edgeCol.resize(height);
		for(auto&& item:edgeCol)
			item.resize(width+1);
	}
	const Node& getNode(size_t r,size_t c)
	{
		return node[r][c];
	}
	void setNode(size_t r,size_t c,const Node& value)
	{
		node[r][c]=value;
	}
	const Edge& getEdgeR(size_t r,size_t c)
	{
		return edgeRow[r][c];
	}
	void setEdgeR(size_t r,size_t c,const Edge& value)
	{
		edgeRow[r][c]=value;
	}
	const Edge& getEdgeC(size_t r,size_t c)
	{
		return edgeCol[r][c];
	}
	void setEdgeC(size_t r,size_t c,const Edge& value)
	{
		edgeCol[r][c]=value;
	}
};
NS_EM_END
#endif 
