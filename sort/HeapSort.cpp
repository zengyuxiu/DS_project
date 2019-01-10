/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-03 22:39
#
# Filename: HeapSort.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include"SqList.h"
#include <iostream>
typedef SqList HeapType;
void HeapAdjust(RcdType r[],int s,int m){
    auto rc = r[s];
    for(int j =2;j<=m;j*=2){
        if(j<m&&r[j] < r[j+1])
            ++j;
        if(rc >= r[j])
            break;
        r[s] = r[j];
        s = j;
    }
    r[s] = rc;
}
void HeapSort(RcdType r[],int length){
    std::cout<< "Running in "<<__PRETTY_FUNCTION__<<":";
    for(int i = length/2;i>0;--i)
        HeapAdjust(r,i,length);
    for(int i = length;i>1;--i){
        auto tmp = r[1];
        r[1] = r[i];
        r[i] = tmp;
        HeapAdjust(r,1,i-1);
    }
}
