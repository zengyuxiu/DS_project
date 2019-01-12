/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2019-01-12 18:08
#
# Filename:		MutiFind.cpp
#
# Description: -mf
#
=============================================================================*/
#include"../Tree/SpeciesTree.h"
#include"Find.h"
int main()
{
	Tree t1;
	t1.Grow();
	Find f1;
	f1.MutiFind();
	std::cout << f1;
}


