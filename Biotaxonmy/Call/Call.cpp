/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-05-14 02:28
#
# Filename: Call.cpp
#
# Description: -a && -p
#
=============================================================================*/
#include"cstring"
#include"Call.h"
#include"../Tree/SpeciesTree.h"
int main(int arg,char ** argv)
{
	Tree t1;
	t1.Grow();
	Call c1;
	if (arg == 1)
		c1.Print();	
	else
	{
		std::string Mode(argv[1]);
		if (Mode == "Phylum")  //列出所有Phylum
		{
			for (auto  Node_Ptr:Phylum::PhylumAutoNode)
				c1.Print(Node_Ptr);						
		}
		else if (Mode == "Class") //同理
		{
			for (auto  Node_Ptr:Class::ClassAutoNode)
				c1.Print(Node_Ptr);						
		}
		else if (Mode == "Order")
		{
			for (auto  Node_Ptr:Order::OrderAutoNode)
				c1.Print(Node_Ptr);						
		}
		else if (Mode == "Family")
		{
			for (auto  Node_Ptr:Family::FamilyAutoNode)
				c1.Print(Node_Ptr);						
		}
		else if (Mode == "Species")
		{
			for (auto  Node_Ptr:Species::SpeciesAutoNode)
				c1.Print(Node_Ptr);						
		}
	}
	std::cout <<c1;
}
