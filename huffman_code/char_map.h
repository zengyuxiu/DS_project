/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-06 21:22
#
# Filename: char_map.h
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<array>
#include<vector>
#include<string>
#include<bitset>
#include<fstream>
#include<map>
#ifndef CHARMAP
using namespace std;
#define CHARMAP
#define INFINITY    1024
#define MAX_VERTEX_NUM 20
#define TURE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2
typedef int Status;
typedef std::vector<bool> Code_BitSet;
typedef struct Char_Map{
    unsigned int                                weight[128] ={0};
    std::vector<Code_BitSet>                    HuffmanCode;
}Char_Map;
#endif
