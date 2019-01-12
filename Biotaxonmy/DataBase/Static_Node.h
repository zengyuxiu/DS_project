/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2019-01-12 18:07
#
# Filename:		Static_Node.h
#
# Description: 
#
=============================================================================*/
#ifndef STATIC_NODE_H
#define STATIC_NODE_H
#include<vector>
#include<string>
#include<map>
class Static_Node
{
	protected:
	std::vector<std::string> Name_Space; //名字空间
	std::string Name; //名字
	public:
	std::vector<std::string>::iterator _iter; //指向名字的迭代器
	Static_Node() = default;//默认构造
	//初始化
	void init(std::string name);
	//按姓名构造
	Static_Node(std::string name)
	:Name(name)
	{
	}
	//重载 == 
	bool operator== (Static_Node & sta_node);
	//重载 >
	bool operator> (Static_Node & sta_node);
	//重载 <
	bool operator< (Static_Node & sta_node);
	//重载 = 
	bool operator = (std::string name);
	//建立节点
	int build (void);
	//添加名字到名字域中
	void add (std::string name); //override
	//查找和检查
	bool check (void); 
	bool find  (void); //override
};
class Static_Kingdom:public Static_Node
{
	public:
	Static_Kingdom() = default;
	Static_Kingdom(std::string name)
	:Static_Node(name)
	{
		build();
	};
};
class Static_Phylum:public Static_Node
{
	public:
	Static_Phylum() = default;
	Static_Phylum(std::string name)
	:Static_Node(name)
	{
		build();
	};
};
class Static_Class:public Static_Node
{
	public:
	Static_Class() = default;
	Static_Class(std::string name)
	:Static_Node(name)
	{
		build();
	};
};
class Static_Order:public Static_Node
{
	public:
	Static_Order() = default;
	Static_Order(std::string name)
	:Static_Node(name)
	{
		build();
	};
};
class Static_Family:public Static_Node
{
	public:
	Static_Family() = default;
	Static_Family(std::string name)
	:Static_Node(name)
	{
		build();
	};
};
class Static_Genus:public Static_Node
{
	public:
	Static_Genus() = default;
	Static_Genus(std::string name)
	:Static_Node(name)
	{
		build();
	};
};
class Static_Species:public Static_Node
{
	public:
	Static_Species() = default;
	Static_Species(std::string name)
	:Static_Node(name)
	{
		build();
	};
};


void Static_Node::init(std::string name)
{
	Name_Space.clear();
	Name_Space.push_back(name);
	_iter = Name_Space.begin();
}


/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 运算符重载
#
# 接口：
# 	
# 功能：
=============================================================================*/


inline bool Static_Node::operator< (Static_Node & sta_node)
{
	return (*this->_iter)<(*sta_node._iter);
}
inline bool Static_Node::operator> (Static_Node & sta_node)
{
	return (*this->_iter)>(*sta_node._iter);
}
inline bool Static_Node::operator== (Static_Node & sta_node)
{
	return (*this->_iter)==(*sta_node._iter);
}
bool Static_Node::operator = (std::string name)
{
	Name = name;
	int flag = Static_Node::build();
	return flag;
}
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 建立模块
#
# 接口：
# 	
# 功能：判断是否添加新的名字到名字域
=============================================================================*/


int Static_Node::build (void)
{
	if (check())
		//无需建立新的节点
		return false; 
	else if (!find())
	{
		//建立新的节点
		add(Name);
		Name.erase();
		return true; 
	}
	//无需建立新的节点
	else return false;  
}
void Static_Node::add (std::string name) 
{
	Name_Space.push_back(name);
	_iter = --Name_Space.end();
}
//如果输入的分类与当前分类不同需要查找，返回ture
bool Static_Node::check (void)
{
	if (Name != *Name_Space.begin()) 
		return false;
	else
		return true;
}
bool Static_Node::find  (void) 
{
	auto iter = Name_Space.begin();
	for (auto name : Name_Space)
	{
		if (name == Name)
		{	
			_iter = iter;
			return true;
		}
		else 
			iter++;
	}
	return false;
}
#endif
