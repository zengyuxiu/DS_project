/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-22 14:23
#
# Filename: StoreIndex.h
#
# Description: 
#
=============================================================================*/
#include<stdio.h>

#include <dirent.h>

#include <string>

#include "good_store.hpp"
#include  "store.h"
#include <fstream>
#ifndef STOREINDEX
#define STOREINDEX
StoreIndex::StoreIndex(std::string DirName){
    DIR *dp;
    struct dirent *dirp;
    auto * pre_newbase = new Store;
    this->Head = pre_newbase;
    if((dp = opendir(DirName.c_str())))
        while((dirp = readdir(dp)))
            if(dirp->d_type == 8){
                this->length ++;
                std::string filename(dirp->d_name);
                ifstream File(filename);
                auto * newbase = new Store(File);
                newbase->filename = filename;
                newbase ->number = length;
                pre_newbase->next = newbase;
                pre_newbase = newbase;
                newbase = NULL;
                File.close();
            }
    this->Tail = pre_newbase;
    pre_newbase->next = NULL;
    closedir(dp);
};
Status StoreIndex::Add(Store * new_store){
    if(!new_store)
        return ERROR;
    this->Tail-> next = new_store;
    this->Tail = new_store;
    this->length++;
    new_store->number = this->length;
    return OK;
}
Status StoreIndex::Add(std::string filename){
    ifstream File(filename);
    if(File.good()){
        auto * new_store = new Store(File);
        StoreIndex::Add(new_store);
        return OK;
    }
    else return ERROR;
}
Status StoreIndex::Del(int del_number){
    if(del_number > this->length)
        return ERROR;
    auto front_p = this->Head;
    auto current_p = this->Head;
    auto latter_p = this->Head;
    for(;front_p->next != NULL;front_p = front_p ->next)
        if(front_p->next->number == del_number)
            break;
    this->length --;
    current_p = front_p -> next;
    latter_p = current_p -> next;
    for(;latter_p!=NULL;latter_p = latter_p->next)
        latter_p->number -- ;
    front_p -> next = current_p ->next; 
    free(current_p);
    return OK;
}
Status StoreIndex::Output(){
    string OutFile("Info.txt");
    ofstream  Out(OutFile);
    if(!Out.good())
        return ERROR;
    for(auto store = this->Head;store;store = store->next)
        Out<< store->number << '\t' << store->Name << std::endl;
    return OK;
}
#endif
