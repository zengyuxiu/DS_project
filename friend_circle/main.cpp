/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-10 15:23
#
# Filename: main.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<iostream>
#include"person_club.hpp"
#include<vector>
#include<array>
void make_friends(std::vector<person> &persons,std::vector<club> &clubs);
int main(){
    int     person_number = 0,club_number = 0;
    std::cin >> person_number >> club_number;
    std::vector<person>         persons;
    std::vector<club>           clubs;
    int   club_mem_sum[M+1]={0};
    for(int i = 1;i<=person_number;++i){
        person p(i);
        persons.push_back(p);
    }
    //建立基础关系
    for(int i = 1;i<=club_number;++i){
        int     member_number;
        std::cin >> member_number;
        club    c(i,member_number);
        for(int r = 1;r<=member_number;++r){
            int person_id = 0;
            std::cin >> person_id;
            c.member_ids.push_back(person_id);
            persons[person_id-1].tag_numbers++;
            persons[person_id-1].tag[i] = 1;
        }
        clubs.push_back(c);
    }
    //圈子之间取并集
    make_friends(persons,clubs);
    //统计圈子的大小
    for(auto person:persons){
        int i = 0;
        for(int r = 0;;r++){
            if(person.tag[r]){
                club_mem_sum[r]++;
                i++;
                if(i == person.tag_numbers)
                    break;
            }
        }
    }
    int max_mem_num = club_mem_sum[1];
    for(int i = 2;i<=club_number;i++){
        if(club_mem_sum[i]>max_mem_num)
            max_mem_num = club_mem_sum[i];
    }
    std::cout << max_mem_num;
}
void make_friends(std::vector<person> &persons,std::vector<club> &clubs){
    for(auto club:clubs){
        //用common_tag确定所有可能的域
        std::array<bool,M+1>    common_tag;
        int                     tag_numbers = 0;
        common_tag.fill(0);
        for(auto id:club.member_ids){
            int i = 0,r = 1;
            for(;i<=persons[id-1].tag_numbers;r++)
                if(persons[id-1].tag[r]) {
                    if(!common_tag[r]){
                        common_tag[r] = 1;
                        tag_numbers++;
                    }
                    i++;
                }
        }
        int i = 0;
        for(int r = 1;;r++){
            if(common_tag[r]){
                for(auto id:club.member_ids)
                    persons[id-1].tag[r] = 1;
                i++;
                if(i == tag_numbers)
                    break;
            }
        } 
    }
}
