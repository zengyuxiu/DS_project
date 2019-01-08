/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-03 20:16
#
# Filename: test.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include"SimpleSort.cpp"
#include "HeapSort.cpp"
int main(void){
    SqList L;
    L.r[1] = 1;
    L.r[2] = 6;
    L.r[3] = 8;
    L.r[4] = 4;
    L.r[5] = 5;
    L.r[6] = 2;
    L.length = 6;
    MergeSort(L);
    //HeapSort(L);
    return 1;
}
