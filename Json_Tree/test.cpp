/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-02 17:46
#
# Filename: test.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<vector>
#include<string>
#include<fstream>
#include "GetInfo.cpp"
int main(){
    std::vector<std::string> Info;
    std::ifstream file("inin");
    GetInfo(file,Info);
    return OK;
}
