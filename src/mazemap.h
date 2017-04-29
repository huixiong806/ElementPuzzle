#ifndef MAZE_H
#define MAZE_H
#include <cstddef>
#include <vector> 
#include "definitions.h"
NS_MS_BEGIN
using BitType = uint8_t;
template<class NodeType,class EdgeType,class PostType>
class Map
{
private:
	std::vector<std::vector<NodeType>> node;
	std::vector<std::vector<EdgeType>> edgeRow;
	std::vector<std::vector<EdgeType>> edgeCol;
	std::vector<std::vector<PostType>> post;
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
		post.resize(height+1);
		for(auto&& item:post)
			item.resize(width+1);
	}
	const NodeType& getNode(size_t r,size_t c)
	{
		return node[r][c];
	}
	void setNode(size_t r,size_t c,const NodeType& value)
	{
		node[r][c]=value;
	}
	const EdgeType& getEdgeR(size_t r,size_t c)
	{
		return edgeRow[r][c];
	}
	void setEdgeR(size_t r,size_t c,const EdgeType& value)
	{
		edgeRow[r][c]=value;
	}
	const EdgeType& getEdgeC(size_t r,size_t c)
	{
		return edgeCol[r][c];
	}
	void setEdgeC(size_t r,size_t c,const EdgeType& value)
	{
		edgeCol[r][c]=value;
	}
};
NS_MS_END
#endif 
