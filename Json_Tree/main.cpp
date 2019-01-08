/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-30 11:22
#
# Filename: main.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include "Tree.hpp"
#include "GetInfo.cpp"
Tool tool;
int main(){
    std::string filename = "in" ;
    std::ifstream file(filename);
    TNode Tree;
    Tree.key = filename;
    if(GetInfo(file,tool.Info)){
        //TNode::info_tail = Info.end();
        Tree.data = tool.Info.front();
        Translate(&Tree,tool);
    }
    //Search(&Tree,"address.city");
    std::vector<std::string> info;
    DFS_Out(&Tree,info);
    for(auto line:info){
        std::cout << line <<std::endl;
    }
    return OK;
}
