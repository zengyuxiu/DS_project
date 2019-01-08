/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-03 16:36
#
# Filename: SimpleSort.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<vector>
#include"SqList.h"
void InsertSort(SqList &L){
    for(int i = 2;i<=L.length;++i){
        if(L.r[i]<L.r[i-1]){
            L.r[0] = L.r[i];
            L.r[i] = L.r[i-1];
            int j = 0;
            for(int j=i-2;L.r[0]<L.r[j];--j)
                L.r[j+1] = L.r[j];
            L.r[j+1] = L.r[0];
        }
    }
}
int SelectMin(SqList &L,int i){
    auto min = L.r[i];
    int pos = i;
    for(int j = i+1;j<=L.length;++j)
        if(L.r[j] < min){
            pos = j;
            min = L.r[j];
        }
    return pos;
}
void SelectSort(SqList &L){
    for(int i = 1;i<=L.length;++i){
        int j = SelectMin(L,i);
        if(i != j){
            auto tmp = L.r[i];
            L.r[i] = L.r[j];
            L.r[j] = tmp;
        }
    }
}
void bubble_sort(RcdType arr[], int len) {
	int i, j;
	for (i = 0; i < len - 1; i++)
		for (j = 0; j < len - 1 - i; j++)
			if (arr[j] > arr[j + 1]){
                auto tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}
