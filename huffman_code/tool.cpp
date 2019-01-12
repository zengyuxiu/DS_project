/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified:	2019-01-08 15:28
#
# Filename:		tool.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<bitset>
#include<fstream>
#include"char_map.h"
#include"huffman_tree.h"
#define SIZE    8*sizeof(int)
using namespace std;
string essay;
Status Get_Weight(Char_Map &CM,string filename){
    ifstream file(filename);
    while(file.good())  {
        string  line;
        std::getline(file,line);
        for(auto ch:line){
            CM.weight[(int)ch]++;
        }
        essay+=line;
    }
    return OK;
}
Status Transform(HuffmanCode HC){
    unsigned long   SHIFT = 0;
    unsigned int num = 0;
    ofstream out_file("out",ios::binary);
    if(!out_file.is_open())
        return ERROR;
    string code_essay;
    for(auto ch : essay){
        code_essay += HC[(int)ch+1];
    }
    //位运算转化string
    for(auto ch:code_essay){
        unsigned int mask = 1;
        if(SHIFT < SIZE){
            //在string中有一处置一
            if(ch == '1'){
                mask <<= SHIFT;    
                num ^= mask;
                SHIFT++;
            }
        }
        else{
            out_file.write(reinterpret_cast<char *>(&num),SIZE);
            SHIFT = 0;
            mask = 1;
            num = 0;
            if(ch == '1')
                num ^= mask;
        }
    }
    if(num != 0)
        out_file.write(reinterpret_cast<char *>(&num),SIZE);
    out_file.close();
    return OK;
}
//一一对应HC和CM
Status Map(HuffmanCode HC,Char_Map &CM){
    for(int i = 1; i<=128;i++){
        string code_string= HC[i];
        Code_BitSet cdbtst;
        for(auto ch:code_string)
            if(ch == '1')
                cdbtst.push_back(TURE);
            else
                cdbtst.push_back(FALSE);
        CM.HuffmanCode.push_back(cdbtst);
    }
    return OK;
}
//解码
char Decode(string code,HuffmanCode &HC){
    for(int i  = 0;i<128;++i){
        string  hfcs= HC[i] ;
        if(hfcs== code)
            return (char)(i-1);
    }
    exit(OVERFLOW);
}
