/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-03 22:17
#
# Filename: QSort.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include"SqList.h"
int Partition(SqList &L,int low,int high){
    L.r[0] = L.r[low];
    auto pivo = L.r[low];
    while(low < high){
        while(low<high&&L.r[high]>=pivo)
            --high;
        L.r[low] = L.r[high];
        while(low<high&&L.r[low]<=pivo)
            ++low;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}
void QSort(SqList &L,int low,int high){
    if(low < high){
        auto pivo = Partition(L,low,high);
        QSort(L,low,pivo);
        QSort(L,pivo+1,high);
    }
}
void QSort(SqList &L){
    QSort(L,1,L.length);
}
