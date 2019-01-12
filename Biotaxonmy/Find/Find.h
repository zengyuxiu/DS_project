/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2019-01-12 18:08
#
# Filename:		Find.h
#
# Description: 
#
=============================================================================*/
#ifndef FIND_H
#define FIND_H
#include"../Call/Call.h"
#include"../Tree/SpeciesTree.h"
class Find:public Call
{
	friend std::ostream & operator<< (std::ostream & out, Find & f1);
	private:
		std::vector<std::string> Name_Vector;
		Node * FatherNode;
		int DEPTH;
	public:
		std::string TabofEndNode(Node * Node_Ptr,int depth) override;  //对查找功能特化的格式化输出
		std::string TabofMiddleNode(Node * Node_Ptr,int depth) override;  //对查找功能特化的格式化输出
		void MutiFind();  //多相查找模块
		void SingleFind(std::string Name);  //单一查找模块
		void Print(Node * Node_Ptr) override; //对查找功能特化的打印模块
		inline bool Check(Node * Node_Ptr)  //目标检索模块
		{
			for (auto name:Name_Vector)
				if (name == Node_Ptr->_Name)
					return true;
			return false;
		}
		Node * Analyze( std::vector<Node *> & Node_Ptr_Vector); //同级节点的分析溯源模块
};
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 打印模块
#
# 接口：Node * depth
# 	
# 功能：为打印功能特化
=============================================================================*/

void Find::Print(Node * Node_Ptr)
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
# name:格式化输出
#
# 接口：Node * depth
# 	
# 功能：为查找功能特化
=============================================================================*/

std::string Find::TabofEndNode(Node * Node_Ptr,int depth)
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
	if (Check(Node_Ptr))  //特化
		Line+='*';
	return Line;
}
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name:格式化输出 
#
# 接口：Node * depth
# 	
# 功能：为查找功能特化
=============================================================================*/

std::string Find::TabofMiddleNode(Node * Node_Ptr,int depth)
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
	if (Check(Node_Ptr))  //特化
		Line+='*';
	return Line;
}
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 解析模块
#
# 接口：节点向量
# 	
# 功能：返回节点向量组共同的祖先节点
=============================================================================*/

Node * Find::Analyze( std::vector<Node *> & Node_Ptr_Vector) //同级节点的分析溯源
{
	DEPTH= 1;
	std::vector<std::string> Name;
	do
	{
		Name.clear();
		for (auto ptr : Node_Ptr_Vector)
		{
			FatherNode = Call::Recall(ptr,DEPTH);
			Name.push_back(FatherNode ->_Name);
			Name_Vector.push_back(FatherNode->_Name);
		}	
		std::sort(Name.begin(),Name.end());
		DEPTH++;	
	}
	while (!(*Name.begin() == Name.back()));
	return FatherNode;
}
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 单个查找
#
# 接口：节点名字
# 	
# 功能：调用查找模块
=============================================================================*/

void Find::SingleFind(std::string Name = "脊索动物门")
{
	auto Node_Ptr = Tree::Secrch(Name);
	if(Node_Ptr != NULL)
		Print(Node_Ptr);
	else
		std::cerr<<"There are no node named that!";
}
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 多相查找模块
#
# 接口：
# 	
# 功能：创建目标节点，调用同级节点解析模块
=============================================================================*/

void Find::MutiFind()  //多相查找模块
{
	std::string Name;
	std::cout<<"Please input the Node Name Enter by Enter" << std::endl;
	while(std::getline(std::cin,Name))
	{
		if(Name != "")
		{
			Name_Vector.push_back(Name);
		}		
		else
			break;
	}
	std::vector<Node *> Node_Ptr_Vector;
	for(auto name:Name_Vector)
	{
		Node_Ptr_Vector.push_back(Tree::Secrch(name));
	}
	FatherNode =Analyze(Node_Ptr_Vector);
	Call::Print(FatherNode);
}

std::ostream & operator<< (std::ostream & out , Find & f1) // 重载 <<
{
	out << f1.osstream.str() << std::endl;
	return out;
}


#endif
