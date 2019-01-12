/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-23 13:14
#
# Filename: keybox.h
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<iostream>
#include <vector>
#include <array>
#define TURE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define RENT        -1
#define RETURN      1
typedef int EVENT_TYPE;
typedef int Status;
typedef  struct Event{
    int                                 Begin_Time;
    int                                 End_Time; 
    int                                 Key_number;
    EVENT_TYPE                          Type = 0;
    Event(int w,int s,int c){
        this->Begin_Time = s;
        this->End_Time = s+c;
        this->Key_number = w;
    };
}Event;
typedef struct KeyBox{
    int                                 *Hook_Status = NULL;
    int                                 Hook_Number = 0;
    KeyBox(int N);
    Status Return(Event &e);
    Status Rent(Event &e);
    Status OUT();
}KeyBox;
KeyBox::KeyBox(int N){
    this->Hook_Number = N;
    int *new_status_list = new int [N];
    if(new_status_list)
        this->Hook_Status= new_status_list;
    else
        exit(ERROR);
    int * the_status = this->Hook_Status;
    for(int i = 1;i<=this->Hook_Number;++i,++the_status)
        *the_status = i; 
}
Status KeyBox::OUT(){
   for(int i = 0;i<this->Hook_Number;++i)
       if(this->Hook_Status[i])
           std::cout << this->Hook_Status[i];
       else
           std::cout << 'X';
    std::cout << std::endl;
    return OK;
}
struct{
    bool operator ()(Event e1,Event e2) const{
        return (e1.Begin_Time < e2.Begin_Time);
    }
}Earier_Begin;
struct{
    bool operator ()(Event e1,Event e2) const{
        return (e1.End_Time< e2.End_Time);
    }
}Earier_End;
//归还钥匙
Status KeyBox::Return (Event &e){
    auto the_hook = this->Hook_Status;
    for(int i = 0;i<this->Hook_Number;i++,the_hook++)
        if(!*the_hook){
            *the_hook = e.Key_number;
            break;
        }
    std::cout << e.End_Time<< std::endl;
    return this->OUT();
}
//借出钥匙
Status KeyBox::Rent(Event &e){
    auto the_hook = this->Hook_Status;
    for(int i = 0;i<this->Hook_Number;i++,the_hook++)
        if(*the_hook == e.Key_number){
            *the_hook = 0;
            break;
        } 
    std::cout << e.Begin_Time<< std::endl;
    return this->OUT();
}
