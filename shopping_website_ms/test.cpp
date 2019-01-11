/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-11 13:35
#
# Filename: test.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include "good_store.hpp"
#include "StoreIndex.h"
#include "index.h"
#include "sales_hash_tables.cpp"
#include "store.h"
int main(){
    StoreIndex store_index;
    store_index.bulid("store");
    Index   index;
    index.CreateIndex("g1",store_index);
    index.CreateRecycleList();
    Sales_hash_index    hash_table;
    hash_table._mkhash(store_index);
}
