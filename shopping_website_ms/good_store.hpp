/*=============================================================================
 *
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
    std::vector<Good>       name_index;
typedef class Store{
    public:
        Store(){
        };
        Store(ifstream &filename);
        //增加商品
        Status AddGoods (string Info);
        Status AddGoods ();
        //删去商品
        Status DelGoods (string good_name);
        //向文件输出信息
        Status Output();
        vector<Good*>           goods;
        std::string             filename;
        friend class            Good;
        string                  Name;
        int                     number = 0;
        int                     credibility = 0;
        Store *                 next = NULL;
}Store;
typedef class StoreIndex{
    public:
    Store*                      Head = NULL; 
    Store*                      Tail = NULL; 
    long                        length = 0;
    void    bulid(std::string DirName);
    Status Output();
    Status Add(Store * new_store);
    Status Add(string filename);
    Status Buy(string store_name,string good_name,int number);
    Status Del(int number);
}StoreIndex;
StoreIndex I;
typedef class Good{
    public:
        string                  Name;
        std::size_t             hash = 0;
        void _mkindex(std::string good_name){
            for(auto good:name_index)
                if(good.Name == good_name)
                    return ;
            Good    good(good_name);
            name_index.push_back(good);
        }        
        Good(std::vector<std::string> Info){
            if(Info.size() == 3) {
                Name = Info[0];
                _mkindex(Name);
                this->price = stol(Info[1]);
                this->sales = stol(Info[2]);
            }
        };
        Good(string name,long price,long sales){
            this->Name = name;
            _mkindex(name);
            this->price = price;
            this->sales = sales;
        }
        Good (Good * ObjectGood){
            this->Name = ObjectGood->Name;
            this->price = ObjectGood -> price;
            this->sales = ObjectGood -> sales;
        }
        Good (std::string good_name){
            this->Name = good_name;
        };
        long                    sales = 0;
        Store*                  store = NULL;
        long                    price = 0;
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
typedef struct Sales_hash_index{
        int                         HashTable[(unsigned short int)(-1)];
        void    _mkhash(StoreIndex &store_index);
}Sales_hash_index;
#endif
