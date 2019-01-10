/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2018-05-06 17:14
#
# Filename:		SpeciesTree.h
#
# Description: 
#
=============================================================================*/
#ifndef TREE_H
#define TREE_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"GetList.cpp"
#include"../DataBase/Static_Node.h"
#include"../Node/Node.h"
class Tree
{
	friend std::vector<std::string> &  GetList (std::ifstream & File,std::vector<std::string> &list);
	private:
		std::string FileName{"Data/data"};
		std::vector<std::string> list;	
		int flag = 0;
	public:
	static Static_Kingdom sta_knd;
	static Static_Phylum sta_phl;
	static Static_Family sta_fml;
	static Static_Order sta_odr;
	static Static_Genus sta_gns;
	static Static_Class sta_cls;
	static Static_Species sta_spc;
	std::ifstream File;
	Tree();
	~Tree();
	void Open_File()
	{
		File.open(FileName);
	}
	void Grow();
	void init();
	static Node * Secrch(std::string CLASSNAME);
	void AddOtherName(std::string Name,std::string OtherName) //添加别名
	{
		Tree::Secrch(Name)->OtherName(OtherName);
	}	
};
















/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 静态类的定义
#
# 接口：
# 	
# 功能：
=============================================================================*/


Static_Kingdom Tree::sta_knd;
Static_Phylum Tree::sta_phl;
Static_Family Tree::sta_fml;
Static_Order Tree::sta_odr;
Static_Genus Tree::sta_gns;
Static_Class Tree::sta_cls;
Static_Species Tree::sta_spc;

















//构造
Tree::Tree()
{
	Open_File();
	Tree::init();
}


















/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 初始化
#
# 接口：
# 	
# 功能：建立树的主干
=============================================================================*/

void Tree::init()
{
	GetList(File,list);
	std::vector<Static_Node *> Node_Ptr_Vector
	{&sta_knd,&sta_phl,&sta_cls,&sta_odr,&sta_fml,&sta_gns,&sta_spc}; //缺少属种
	auto list_iter = list.begin();
	for (auto node_ptr : Node_Ptr_Vector)
	{
		node_ptr->init(*list_iter++);
	}
	list.clear();
	Node::Init(Node_Ptr_Vector);
}






















/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 生长模块
#
# 接口：
# 	
# 功能：在树结构的主干上添加枝叶
=============================================================================*/


void Tree::Grow()
{
	std::vector<Static_Node *> Node_Ptr_Vector
	{&sta_knd,&sta_phl,&sta_cls,&sta_odr,&sta_fml,&sta_gns,&sta_spc}; //缺少属种
	while (File.good())
	{
		GetList(File,list);
		auto list_iter = list.begin();
		for (auto node_ptr = Node_Ptr_Vector.begin();node_ptr != Node_Ptr_Vector.end();node_ptr++)
		{
			int flag = (**node_ptr = *list_iter++);
			if (flag == true)
			{
			//如果发现新的节点
			//map 查找上一级节点所在位置
				switch (node_ptr - Node_Ptr_Vector.begin())
				{
					case	1:
					{
						auto k1 = Kingdom::KingdomMap.find(*(*(node_ptr-1))->_iter);
						k1->second->Bulid((*node_ptr)->_iter);
					}
						break;
					case	2:
					{
						auto p1 = Phylum::PhylumMap.find(*(*(node_ptr-1))->_iter);
						p1->second->Bulid((*node_ptr)->_iter);
					}
						break;
					case	3:
					{
						auto c1 = Class::ClassMap.find(*(*(node_ptr-1))->_iter);
						c1->second->Bulid((*node_ptr)->_iter);
					}
						break;
					case	4:
					{
						auto o1 = Order::OrderMap.find(*(*(node_ptr-1))->_iter);
						o1->second->Bulid((*node_ptr)->_iter);
					}
						break;
					case	5:
					{
						auto f1 = Family::FamilyMap.find(*(*(node_ptr-1))->_iter);
						f1->second->Bulid((*node_ptr)->_iter);
					}
						break;
					case	6:
					{
						auto g1 = Genus::GenusMap.find(*(*(node_ptr-1))->_iter);
						g1->second->Bulid((*node_ptr)->_iter);
					}
						break;
				}
			}
		}
		list.clear();
	}
}













//析构
Tree::~Tree()
{
	Species::Static_Destruction();
	Kingdom::Static_Destruction();
	Phylum::Static_Destruction();
	Class::Static_Destruction();
	Order::Static_Destruction();
	Family::Static_Destruction();
	Genus::Static_Destruction();
	File.close();
}


















/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 查找模块
#
# 接口：学名
# 	
# 功能：利用Node类的关联容器进行查找
=============================================================================*/


Node * Tree:: Secrch(std::string CLASSNAME)
{
	std::vector<std::string> AimName{CLASSNAME};
	auto s1 = Species::SpeciesMap.find(*AimName.cbegin());
	auto p1 = Phylum::PhylumMap.find(*AimName.cbegin());
	auto c1 = Class::ClassMap.find(*AimName.cbegin());
	auto o1 = Order::OrderMap.find(*AimName.cbegin());
	auto f1 = Family::FamilyMap.find(*AimName.cbegin());
	auto g1 = Genus::GenusMap.find(*AimName.cbegin());
	auto k1 = Kingdom::KingdomMap.find(*AimName.cbegin());
	if (s1 != Species::SpeciesMap.end())
		return s1->second;
	if (p1 != Phylum::PhylumMap.end())
		return p1->second;
	if (c1 != Class::ClassMap.end())
		return c1->second;
	if (o1 != Order::OrderMap.end())
		return o1->second;
	if (f1 != Family::FamilyMap.end())
		return f1->second;
	if (g1 != Genus::GenusMap.end())
		return g1->second;
	if (k1 != Kingdom::KingdomMap.end())
		return k1->second;
	return NULL;
};
#endif
