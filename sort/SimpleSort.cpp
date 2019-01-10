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
#include<iostream>
#include"SqList.h"
void InsertSort(RcdType r[],int length){
    std::cout<< "Running in "<<__PRETTY_FUNCTION__<<":";
    for(int i = 2;i<=length;++i){
        if(r[i]<r[i-1]){
            r[0] = r[i];
            r[i] = r[i-1];
            int j=i-2;
            for(;r[0]<r[j];--j)
                r[j+1] = r[j];
            r[j+1] = r[0];
        }
    }
}
int SelectMin(RcdType r[],int i,int length){
    auto min = r[i];
    int pos = i;
    for(int j = i+1;j<=length;++j)
        if(r[j] < min){
            pos = j;
            min = r[j];
        }
    return pos;
}
void SelectSort(RcdType r[],int length){
    std::cout<< "Running in "<<__PRETTY_FUNCTION__<<":";
    for(int i = 1;i<=length;++i){
        int j = SelectMin(r,i,length);
        if(i != j){
            auto tmp = r[i];
            r[i] = r[j];
            r[j] = tmp;
        }
    }
}
void bubble_sort(RcdType arr[], int len) {
    std::cout<< "Running in "<<__PRETTY_FUNCTION__<<":";
	int i, j;
	for (i = 1; i <= len ; i++)
		for (j = 1; j <= len - i; j++)
			if (arr[j] > arr[j + 1]){
                auto tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}
