/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-29 00:41
#
# Filename: GetInfo.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<iostream>
#include<fstream>
#include <string>
#include<vector>
#define TURE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2
typedef int Status;
Status GetInfo(std::ifstream &File,std::vector<std::string> &Info){
    if(!File.good())
        return ERROR;
    std::string word;
    std::vector<std::string> temp_info;
    while(File.good()){
        std::getline(File, word);
        temp_info.push_back(word);
    }
    word.clear();
    for(auto block:temp_info)
        for(auto ch:block){
            word+=ch; 
            if(ch == '{'){
                Info.push_back(word);
                word.clear();
                continue;
            }
            if( ch == '}'){
                //empty object
                if(word.size()==1){
                    Info.back()+=ch;
                    word.clear();
                }
                else{
                    word.pop_back();
                    Info.push_back(word);
                    word.clear();
                    word+=ch;
                }
                continue;
            }
            if(ch == ','){
                Info.push_back(word);
                word.clear();
                continue;
            }
        }
    if(!word.empty())
        Info.push_back(word);
    return OK;
}
