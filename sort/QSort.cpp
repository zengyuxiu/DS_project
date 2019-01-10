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
#include<iostream>
#include"SqList.h"
int Partition(RcdType r[],int low,int high){
    r[0] = r[low];
    auto pivo = r[low];
    while(low < high){
        while(low<high&&r[high]>=pivo)
            --high;
        r[low] = r[high];
        while(low<high&&r[low]<=pivo)
            ++low;
        r[high] = r[low];
    }
    r[low] = r[0];
    return low;
}
void QSort(RcdType r[],int low,int high){
    if(low < high){
        auto pivo = Partition(r,low,high);
        QSort(r,low,pivo);
        QSort(r,pivo+1,high);
    }
}
void QSort(RcdType r[],int length){
    std::cout<< "Running in "<<__PRETTY_FUNCTION__<<":\t";
    QSort(r,1,length);
}
