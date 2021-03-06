/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-23 10:23
#
# Filename: index.h
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<array>
#include "StoreIndex.h"
#include <algorithm>
#ifndef INDEX
#define  INDEX
//销量比较函数
struct {
    bool operator()(index_good *g1,index_good * g2) const{
        return (g1->Object->sales < g2->Object->sales);
    }
}SalesLess;
//按信誉度创建商店目录
Status Index::CreateIndex(string Name,StoreIndex &I){
    this->Name = Name;
    for(auto store = I.Head->next;store;store=store->next){
        for(auto good:store->goods)
            if(good->Name == this->Name ){
                auto new_index_good = new index_good(good);
                new_index_good ->Belong = store;
                this->goods[store->credibility].push_back(new_index_good);
            }
    }
    for(auto & good_list:goods){
        std::sort(good_list.begin(),good_list.end(),SalesLess);
    }
    return OK;
}
//构建循环
Status Index::CreateRecycleList(){
    this->Head = this->goods[5].front();
    for(int i = 0 ;i<CREDIBILITYLEVEL;i++){
        if(i){
            this->goods[((i-1)%CREDIBILITYLEVEL)].front()->front= this->goods[i].back();
            this->goods[i].back()->next= this->goods[((i-1)%CREDIBILITYLEVEL)].front();
        }
        //头尾相接 
        else{
            this->goods[5].front()->front= this->goods[0].back();
            this->goods[0].back()->next= this->goods[5].front();
        }
        //向后指针
        for(std::size_t j = 0 ; (j+1) < this->goods[i].size();j++)
            this->goods[i][j]->next = this->goods[i][j+1];
        //向前指针
        for(std::size_t j = this->goods[i].size() -1; j > 0;j++)
            this->goods[i][j]->front = this->goods[i][j-1];
    }
    return OK;
}
#endif

