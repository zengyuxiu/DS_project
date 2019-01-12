/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-07 17:53
#
# Filename: test.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<iostream>
#include"huffman_tree.h"
#include"char_map.h"
#include "tool.cpp"
int main(){
    Char_Map CM;
    HuffmanTree HT;
    HuffmanCode HC;
    Get_Weight(CM,"in");
    HuffmanCoding(HT,HC,CM.weight,128);
    Map(HC,CM);
    Transform(HC);
    std::cout << Decode("10",HC);
    return OK;
}
