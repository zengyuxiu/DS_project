/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified: 2019-01-10 10:12
#
# Filename: shell_sort.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<iostream>
#include"SqList.h"
void shell_sort(RcdType array[], int length) {
    std::cout<< "Running in "<<__PRETTY_FUNCTION__<<":";
    //array[0] is empty;
    array++;
    int h = 1;
    while (h < length / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < length; i++) {
            for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
                std::swap(array[j], array[j - h]);
            }
        }
        h = h / 3;
    }
}

