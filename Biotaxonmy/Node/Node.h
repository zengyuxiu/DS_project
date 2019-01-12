/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2019-01-12 18:08
#
# Filename:		Node.h
#
# Description: 
#
=============================================================================*/
#ifndef NODE_H
#define NODE_H
#include<memory>
#include<vector>
#include<string>
#include<map>
#include"../DataBase/Static_Node.h"
class Node
{
	friend class Call;
	friend class Static_Node;
	friend class Tree;
	friend class Find;
	protected:
		Node * Up_Node;
		std::vector<Node *> Down_Node; //子节点向量
		std::string _Name; //学名
		std::string _OtherName; //别名
		long long _id; //id
		void OtherName(std::string other_name)
		{
			_OtherName = other_name;
		}
	public:
		Node(std::vector<std::string>::const_iterator name)
		:_Name(*name)
		{
		};
		void Recall(Node  &	Father_Node)  //回溯
		{
			Up_Node = &Father_Node;
		}
		void Inherit(Node & Son_Node)  //继承
		{
			Down_Node.push_back(&Son_Node);
			Son_Node._id = Down_Node.size();
		}
		static void Init(std::vector<Static_Node *> &Node_Ptr_Vector); //初始化
};
class Species: public Node
{
	public:
	static std::vector<Species*> SpeciesAutoNode;
	static std::map<std::string,Species *> SpeciesMap;
	Species() = default;
	Species(std::vector<std::string>::const_iterator name)
	:Node(name)
	{
	};
	static void Static_Destruction()  //析构动态节点
	{
		for(auto AutoNode:SpeciesAutoNode)
			delete AutoNode;
	}
};
class Genus: public Node
{
	public:
	static std::vector<Genus*> GenusAutoNode;
	static std::map<std::string,Genus *> GenusMap;
	Genus() = default;
	static void Static_Destruction()
	{
		for(auto AutoNode:GenusAutoNode)
			delete AutoNode;
	}
	Genus(std::vector<std::string>::const_iterator name)
	:Node(name)
	{
	};
	void Bulid(std::vector<std::string>::const_iterator name);
};
class Family: public Node
{
	public:
	static std::vector<Family*> FamilyAutoNode;
	static std::map<std::string,Family *> FamilyMap;
	Family() = default;
	static void Static_Destruction()
	{
		for(auto AutoNode:FamilyAutoNode)
			delete AutoNode;
	}
	Family(std::vector<std::string>::const_iterator name)
	:Node(name)
	{
	};
	void Bulid(std::vector<std::string>::const_iterator name);
};
class Order: public Node
{
	public:
	static std::vector<Order*> OrderAutoNode;
	static std::map<std::string,Order *> OrderMap;
	Order() = default;
	static void Static_Destruction()
	{
		for(auto AutoNode:OrderAutoNode)
			delete AutoNode;
	}
	Order(std::vector<std::string>::const_iterator name)
	:Node(name)
	{
	};
	void Bulid(std::vector<std::string>::const_iterator name);
};
class Class: public Node
{
	public:
	static std::vector<Class*> ClassAutoNode;
	static std::map<std::string,Class *> ClassMap;
	Class() = default;
	static void Static_Destruction()
	{
		for(auto AutoNode:ClassAutoNode)
			delete AutoNode;
	}
	Class(std::vector<std::string>::const_iterator name)
	:Node(name)
	{
	};
	void Bulid(std::vector<std::string>::const_iterator name);
};
class Phylum : public Node
{
	public:
	static std::vector<Phylum*> PhylumAutoNode;
	static std::map<std::string,Phylum *> PhylumMap;
	Phylum() = default;
	static void Static_Destruction()
	{
		for(auto AutoNode:PhylumAutoNode)
			delete AutoNode;
	}
	Phylum(std::vector<std::string>::const_iterator name)
	:Node(name)
	{
	};
	void Bulid(std::vector<std::string>::const_iterator name);
};
class Kingdom : public Node
{
	public:
	static std::vector<Kingdom*> KingdomAutoNode;
	static std::map<std::string,Kingdom *> KingdomMap;
	Kingdom() = default;
	static void Static_Destruction()
	{
		for(auto AutoNode:KingdomAutoNode)
			delete AutoNode;
	}
	Kingdom(std::vector<std::string>::const_iterator name)
	:Node(name)
	{
	};
	void Bulid(std::vector<std::string>::const_iterator name);
};
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 定义动态节点目录
#
# 接口：
# 	
# 功能：
=============================================================================*/


std::vector<Kingdom*>Kingdom::KingdomAutoNode;
std::vector<Phylum*>Phylum::PhylumAutoNode;
std::vector<Class*>Class::ClassAutoNode;
std::vector<Order*>Order::OrderAutoNode;
std::vector<Family*>Family::FamilyAutoNode;
std::vector<Genus*>Genus::GenusAutoNode;
std::vector<Species*>Species::SpeciesAutoNode;
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 定义动态节点关联容器
#
# 接口：
# 	
# 功能：
=============================================================================*/


std::map<std::string,Kingdom *> Kingdom::KingdomMap;
std::map<std::string,Phylum *> Phylum:: PhylumMap;
std::map<std::string,Class *> Class::ClassMap;
std::map<std::string,Order *> Order::OrderMap;
std::map<std::string,Family *> Family::FamilyMap;
std::map<std::string,Genus *> Genus::GenusMap;
std::map<std::string,Species *> Species::SpeciesMap;
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name:动态节点的建立
#
# 接口：来自静态类的名字域的迭代器
# 	
# 功能：建立新节点
=============================================================================*/


void Kingdom::Bulid(std::vector<std::string>::const_iterator name) 
{
	//申请空间
	Phylum * p1 = (Phylum *)new Phylum(name);
	//加入目录
	Phylum::PhylumAutoNode.push_back(p1);
	//加入关联容器
	Phylum::PhylumMap.insert(std::pair<std::string,Phylum *>(*name,p1));
	//继承
	Inherit (*p1);
	//回溯
	(*p1).Recall(*this);
}
void Phylum::Bulid(std::vector<std::string>::const_iterator name) 
{
	//申请空间
	Class * p1 = (Class *)new Class (name);
	//加入目录
	Class::ClassAutoNode.push_back(p1);
	//加入关联容器
	Class::ClassMap.insert(std::pair<std::string,Class *>(*name,p1));
	//继承
	Inherit (*p1);
	//回溯
	(*p1).Recall(*this);
}
void Class::Bulid(std::vector<std::string>::const_iterator name) 
{
	Order* p1 = ( Order*)new Order(name);
	Order::OrderAutoNode.push_back(p1);
	Order::OrderMap.insert(std::pair<std::string,Order *>(*name,p1));
	Inherit (*p1);
	(*p1).Recall(*this);
}
void Order::Bulid(std::vector<std::string>::const_iterator name) 
{
	Family * p1 = (Family*)new Family(name);
	Family::FamilyAutoNode.push_back(p1);
	Family::FamilyMap.insert(std::pair<std::string,Family *>(*name,p1));
	Inherit (*p1);
	(*p1).Recall(*this);
}
void Family::Bulid(std::vector<std::string>::const_iterator name) 
{
	Genus * p1 = (Genus *)new Genus (name);
	Genus::GenusAutoNode.push_back(p1);
	Genus::GenusMap.insert(std::pair<std::string,Genus *>(*name,p1));
	Inherit (*p1);
	(*p1).Recall(*this);
}
void Genus::Bulid(std::vector<std::string>::const_iterator name) 
{
	Species * p1 = (Species*)new Species(name);
	Species::SpeciesAutoNode.push_back(p1);
	Species::SpeciesMap.insert(std::pair<std::string,Species *>(*name,p1));
	Inherit (*p1);
	(*p1).Recall(*this);
}
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 动态节点的初始化
#
# 接口：静态节点向量
# 	
# 功能：建立初始树状结构
=============================================================================*/


void Node::Init(std::vector<Static_Node *> &Node_Ptr_Vector)
{
	Kingdom * k1 = (Kingdom *)new Kingdom(Node_Ptr_Vector[0]->_iter);
	Kingdom::KingdomAutoNode.push_back(k1);
	Kingdom::KingdomMap.insert(std::pair<std::string,Kingdom *>(*(Node_Ptr_Vector[0]->_iter),k1));

	Phylum * p1 = (Phylum *)new Phylum(Node_Ptr_Vector[1]->_iter);
	Phylum::PhylumAutoNode.push_back(p1);
	Phylum::PhylumMap.insert(std::pair<std::string,Phylum *>(*(Node_Ptr_Vector[1]->_iter),p1));

	Class * c1 = (Class *)new Class (Node_Ptr_Vector[2]->_iter);
	Class::ClassAutoNode.push_back(c1);
	Class::ClassMap.insert(std::pair<std::string,Class *>(*(Node_Ptr_Vector[2]->_iter),c1));

	Order* o1 = ( Order*)new Order(Node_Ptr_Vector[3]->_iter);
	Order::OrderAutoNode.push_back(o1);
	Order::OrderMap.insert(std::pair<std::string,Order *>(*(Node_Ptr_Vector[3]->_iter),o1));

	Family * f1 = (Family*)new Family(Node_Ptr_Vector[4]->_iter);
	Family::FamilyAutoNode.push_back(f1);
	Family::FamilyMap.insert(std::pair<std::string,Family *>(*(Node_Ptr_Vector[4]->_iter),f1));

	Genus* g1 = (Genus*)new Family(Node_Ptr_Vector[5]->_iter);
	Genus::GenusAutoNode.push_back(g1);
	Genus::GenusMap.insert(std::pair<std::string,Genus *>(*(Node_Ptr_Vector[5]->_iter),g1));
	
	Species* s1 = (Species*)new Species(Node_Ptr_Vector[6]->_iter);
	Species::SpeciesAutoNode.push_back(s1);
	Species::SpeciesMap.insert(std::pair<std::string,Species *>(*(Node_Ptr_Vector[6]->_iter),s1));

	k1->Inherit(*p1);
	p1->Inherit(*c1);
	c1->Inherit(*o1);
	o1->Inherit(*f1);
	f1->Inherit(*g1);
	g1->Inherit(*s1);




	p1->Recall(*k1);
	c1->Recall(*p1);
	o1->Recall(*c1);
	f1->Recall(*o1);
	g1->Recall(*f1);
	s1->Recall(*g1);
}
#endif
