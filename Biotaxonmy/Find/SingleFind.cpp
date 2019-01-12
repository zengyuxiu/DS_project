/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2019-01-12 18:08
#
# Filename:		SingleFind.cpp
#
# Description: 
#
=============================================================================*/
#include"../Tree/SpeciesTree.h"
#include"Find.h"
int main (int arg,char ** argv)
{
	Tree t1;
	t1.Grow();
	Find f1;
	if (arg != 1)
	{
		std::string AimName(argv[1]);
		f1.SingleFind(AimName);
	}
	std::cout << f1;
}

