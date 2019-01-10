/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified:	2019-01-10 11:57
#
# Filename:		Random.cpp
#
# Description: 
#
=============================================================================*/
#include<functional>
#include<stdio.h>
#include<fstream>
#include<array>
#include<random>
#include<string>
#include<algorithm>
#include<iostream>
#include<dirent.h>
#include<time.h>
#include<sstream>
using namespace std;
struct{
    bool operator()(int a,int b){
        return a >= b;
    }
}anti_less;
int main(){
	string dirname("instances");
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(dirname.c_str())) == NULL)
		cout << "Can't open " << dirname << endl;

    time_t nowtime;
    std::default_random_engine engine(nowtime);
	while((dirp = readdir(dp)) != NULL){
        string path = dirname + '/' + dirp->d_name;
        std::ofstream instance (path);
        for(int i = 1;i<=20000;i++){
            instance << engine() << '\t';
        }
        instance.close();
    }
	closedir(dp);

    ifstream r1("./instances/r1",ios::out);
    string      info;
    getline(r1,info);
    array<int,20000> array1;
    istringstream stringin(info) ;
    for(int i = 0;i<20000;i++){
        int key = 0 ;
        stringin >> key;
        array1[i] = key;
    }
    r1.close();
    ofstream r1_sort("./instances/r1");
    sort(array1.begin(),array1.end());
    for(auto key:array1){
        r1_sort << key << '\t';
    }

    ifstream r2("./instances/r2",ios::out);
    info.clear();
    getline(r2,info);
    array<int,20000> array2;
    stringin.str("");
    stringin.str(info) ;
    for(int i = 0;i<20000;i++){
        int key = 0 ;
        stringin >> key;
        array2[i] = key;
    }
    r2.close();
    ofstream r2_sort("./instances/r2");
    sort(array2.begin(),array2.end(),greater<int>());
    for(auto key:array2){
        r2_sort << key << '\t';
    }

	return 0;
}
