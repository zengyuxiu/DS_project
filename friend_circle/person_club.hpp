/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-10 15:15
#
# Filename: person_club.hpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<vector>
#define M   1000
typedef class person{
    public:
    int         id = 0;
    //指示属于哪个圈子
    bool        tag[M+1] ={0};
    int         tag_numbers = 0;
    person(int i){
        this->id = i; 
    }
}person;
typedef class club {
    public:
    int         id = 0;
    int         member_number = 0;
    //属于该圈子的人的id
    std::vector<int>    member_ids; 
    club(int i,int _member_number){
        this->id = i;
        this->member_number = _member_number;
    }
}club;
