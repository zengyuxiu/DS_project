/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified:	2019-01-11 09:36
#
# Filename:		sales_hash_tables.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<functional>
#include "good_store.hpp"

void    Sales_hash_index::_mkhash(StoreIndex &store_index){
    std::hash<std::string>          hash;
    for(std::size_t i = 0;i<name_index.size();++i){
        Good            good = name_index[i];
        Index           index;
        index.CreateIndex(good.Name,store_index);
        long        sales_sum = 0;
        for(auto index_good:index.goods)
            for(auto good:index_good)
                sales_sum += good->Object->sales;
        good.sales = sales_sum;
        good.hash= (unsigned short int)hash(good.Name);
        this->HashTable[good.hash] = i;
    }
}
