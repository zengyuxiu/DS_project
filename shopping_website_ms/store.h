/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-22 11:50
#
# Filename: store.h
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<fstream>
#include<iostream>
#include <vector>
#include<string>
#include "good_store.hpp"
#ifndef STORE
#define STORE
Status GetInfo(std::ifstream &File,std::vector<std::string> &Info){
    if(!File.good())
        return ERROR;
    std::string Line;
    std::getline(File,Line);
    std::string word;
    for(const auto C: Line)
        if(C == '\t' || C == '\n'){
            Info.push_back(word) ;
            word.erase();
        }
        else
            word+=C;
    return OK;
}

Store::Store(ifstream &filename){
    std::vector<std::string> Info;
    while(GetInfo(filename,Info)){
        //商铺信息
        if(Info.size() == 2){
            this->Name = Info[0];
            this->credibility = std::stoi(Info[1]);
        }
        //商品信息
        else{
            auto * good = new Good(Info);
            this->goods.push_back(good);
        }
        Info.clear();
    }
}
Status Store::AddGoods(string Line){
    std::vector<std::string> Info;
    std::string word;
    for(const auto C:Line)
        if(C == '\t' || C == '\n'){
            Info.push_back(word) ;
            word.erase();
        }
        else word += C;
    auto * good = new Good(Info);
    this->goods.push_back(good);
    return OK;
}
Status Store::AddGoods(){
    string      name;
    long        price = 0;
    long        sales = 0;
    std::cin >> name >> price >> sales;
    auto * good = new Good(name,price,sales);
    this->goods.push_back(good);
    return OK;
}
Status Store::DelGoods (string good_name){
    for(auto good = this->goods.begin();good != this->goods.end();good++)
        if((*good)->Name == good_name){
            this->goods.erase(good);
            return OK;
        }
    return ERROR;
}
#endif



