/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2019-01-12 18:07
#
# Filename:		Call.h
#
# Description: 
#
=============================================================================*/
#ifndef CALL_H
#define CALL_H
#include<string>
#include"../Node/Node.h"
#include<algorithm>
#include<sstream>
class Call
{
	friend std::ostream & operator<< (std::ostream & out, Call & c1);
	public:
	Call();
	~Call();
	std::ostringstream osstream;  //输出
	virtual void Print(Node * Node_Ptr);  //打印模块
	virtual bool Scan(int depth,Node * Node_Ptr);  //遍历访问模块
	Node * Recall(Node * Node_Ptr,int depth);  //按深度回溯
	virtual std::string TabofEndNode(Node * Node_Ptr,int depth);  //格式化输出模块
	virtual std::string TabofMiddleNode(Node * Node_Ptr,int depth);  //格式化输出模块
};

Call::Call()
{}
Call::~Call()
{}
std::ostream & operator<< (std::ostream & out , Call & c1) // 重载 <<
{
	out << c1.osstream.str() << std::endl;
	return out;
}










/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 回溯模块
#
# 接口：Node * depth
# 	
# 功能：回溯depth层
=============================================================================*/

Node * Call::Recall(Node * Node_Ptr,int depth)
{
	Node * FatherNode = Node_Ptr;
	for(;depth>0;depth--)
		FatherNode = FatherNode->Up_Node;
	return FatherNode;
}








/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name:	打印模块
#
# 接口：Node * 
# 	
# 功能：调用访问模块，输出到流osstream
=============================================================================*/
void Call::Print(Node* Node_Ptr = Kingdom::KingdomAutoNode[0])
{
	int depth = 0;
	osstream<< '\n'<< Node_Ptr->_Name;
	Call::Scan(depth,Node_Ptr);
}




/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name:	递归访问模块
#
# 接口：depth , Node * 
# 	
# 功能：按深度进行递归访问
=============================================================================*/


bool Call::Scan(int depth,Node * Node_Ptr)
{
	if(Node_Ptr->Down_Node.empty())
		return true;
	else
	{
		depth++;
		for(auto son_node_ptr:Node_Ptr->Down_Node)
		{
			if (son_node_ptr == Node_Ptr->Down_Node.back())
			{
				//输出 \n+ ∟	+ name >> osstream
				osstream<<TabofEndNode(son_node_ptr,depth);
				Call::Scan(depth,son_node_ptr);
				return true;
			}
			else
			{	
				//输出 \n+三岔+ name >> osstream
				osstream<< TabofMiddleNode(son_node_ptr,depth);
				Call::Scan(depth,son_node_ptr);
			}
		}
	}
	return false;
}

/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name:	格式化输出模块
#
# 接口： Node * , depth
# 	
# 功能：按深度进行中间节点和尾节点的格式化输出
#
# 输出：std::string
=============================================================================*/
std::string Call::TabofEndNode(Node * Node_Ptr,int depth)
{
	std::string Line{"\n"};
	for (;depth>1;depth--)
	{
		if ( Call::Recall(Node_Ptr,depth)->Down_Node.back()->_Name== Call::Recall(Node_Ptr,depth-1)->_Name)
			Line += "    ";
		else
			Line += "│   ";
	}
	Line += "└── ";
	Line += Node_Ptr->_Name;
	return Line;
}
std::string Call::TabofMiddleNode(Node * Node_Ptr,int depth)
{
	std::string Line{"\n"};
	for (;depth>1;depth--)
	{
		if ( Call::Recall(Node_Ptr,depth)->Down_Node.back()->_Name== Call::Recall(Node_Ptr,depth-1)->_Name)
			Line += "    ";
		else
			Line += "│   ";
	}
	Line += "├── ";
	Line += Node_Ptr->_Name;
	return Line;
}
#endif
