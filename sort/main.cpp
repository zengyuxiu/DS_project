/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified:	2019-01-09 16:49
#
# Filename:		test.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<iostream>
#include<chrono>
#include<vector>
#include<string>
#include<fstream>
#include<dirent.h>
#include<sstream>
#include "SimpleSort.cpp"
#include "HeapSort.cpp"
#include "merge_sort.cpp"
#include "shell_sort.cpp"
#include "QSort.cpp"
#include "radix_sort.cpp"
using namespace std;
typedef struct instance{
    string          source_file_name;
    SqList          L;
}instance;
int sort_clock(SqList &L);
typedef     void (*SortFunc)(RcdType *,int);
std::vector<SortFunc> SortFuncs{
    QSort,bubble_sort,InsertSort,shell_sort,merge_sort,radixsort,SelectSort,HeapSort
};
int main(void){
    vector<instance> instances;
	string dirname("instances");
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(dirname.c_str())) == NULL)
		cout << "Can't open " << dirname << endl;

	while((dirp = readdir(dp)) != NULL){
        string filename = dirp->d_name;
        string path = dirname + '/' + filename;
        if(filename == "." ||filename == "..")
            continue;
        ifstream    in (path);
        instance    instnc;
        instnc.source_file_name = filename;
        instnc.L.length = 20000;
        string      info;
        getline(in,info);
        istringstream stringin(info) ;
        for(int i = 1;i<=20000;i++){
            int key = 0 ;
            stringin >> key;
            instnc.L.r[i] = key;
        }
        instances.push_back(instnc);
    }

	closedir(dp);

    for(auto instnc:instances){
        std::cout << "INSTANCE : " << instnc.source_file_name << endl;
        sort_clock(instnc.L);
    }
    return 1;
}
int sort_clock(SqList &L){
    for(auto Sort:SortFuncs){
        auto start = std::chrono::system_clock::now();
        (*Sort)(L.r,L.length);
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout <<"\t"<< (double)duration.count()* std::chrono::microseconds::period::num /std::chrono::microseconds::period::den<<"\tseconds";
        std::cout << std::endl;
    }
    return 1;
}
