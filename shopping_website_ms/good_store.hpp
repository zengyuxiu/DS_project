/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2018-12-22 11:37
#
# Filename:		good_store.hpp
#
# Description: 
#
=============================================================================*/
#ifndef GOOD_STORE
#define GOOD_STORE
#define TURE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define CREDIBILITYLEVEL 6
typedef int Status;
#include <dirent.h>
#include <array>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class Good;
typedef class Store{
    public:
        Store();
        Store(ifstream &filename);
        Status AddGoods (string Info);
        Status AddGoods ();
        Status DelGoods (string good_name);
        std::string             filename;
        friend class            Good;
        string                  Name;
        int                     number = 0;
        int                     credibility = 0;
        vector<Good*>           goods;
        Store *                 next = NULL;
}Store;
typedef class StoreIndex{
    public:
    Store*                      Head = NULL; 
    Store*                      Tail = NULL; 
    long                        length = 0;
    StoreIndex(std::string DirName);
    Status Output();
    Status Add(Store * new_store);
    Status Add(string filename);
    Status Del(int number);
}StoreIndex;
typedef class Good{
    public:
        string                  Name;
        Good(std::vector<std::string> Info){
            if(Info.size() == 3) {
                Name = Info[0];
                this->price = stol(Info[1]);
                this->sales = stol(Info[2]);
            }
        };
        Good(string name,long price,long sales){
            this->Name = name;
            this->price = price;
            this->sales = sales;
        }
        Good (Good * ObjectGood){
            this->Name = ObjectGood->Name;
            this->price = ObjectGood -> price;
            this->sales = ObjectGood -> sales;
        }
        long                    sales = 0;
    private:
        long                    price = 0;
        Store*                  store = NULL;
}Good;
typedef class index_good{
    public:
        index_good(Good * ObjectGood){
            this->Object = ObjectGood;
        }
        Good *                  Object = NULL;
        Store *                 Belong = NULL;
        index_good *            front = NULL;
        index_good *            next = NULL;
        int                     Length = 0;
}index_good;
typedef struct Index{
    string                      Name;
    std::array<std::vector<index_good*>,CREDIBILITYLEVEL> goods;
    index_good*                 Head = NULL;
    index_good*                 Tail = NULL;           
    Status CreateRecycleList();
    Status CreateIndex(string Name,StoreIndex &I);
    bool   Compare(const index_good *g1,const index_good * g2);
}Index;
typedef struct Good_Hash_Table{
    std::vector<string>         NameList;
    int                         HashTable[unsigned(-1)];
}Good_Hash_Table;
#endif
