/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2018-04-24 18:24
#
# Filename:		GetList.cpp
#
# Description: 
#
=============================================================================*/
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
/*=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# name: 数据处理模块
#
# 接口：文件流 字符串向量
# 	
# 功能：将线性的分类信息拆分成各个节点的名字
=============================================================================*/


std::vector<std::string> &  GetList (std::ifstream & File,std::vector<std::string> &list)
{
		std::string Line;
		std::getline(File,Line);
		std::string node;
		for (const auto c:Line)
		{
			if (c=='\t'||c=='\n')
			{
				list.push_back(node);
				node.erase();
			}
			else
				node+=c;
		}
	return list;
}
