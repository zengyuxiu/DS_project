/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-24 16:13
#
# Filename: Main.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<algorithm>
#include<queue>
#include "keybox.h"
int main (){
    std::vector <Event> Events;
    //KeyBox key_box = CreateStructure(Events);
    int N , K ,w ,s ,c;
    std::cin >> N >> K;
    KeyBox key_box(N);
    for(int i = 1;i<=K;i++){
        std::cin >> w >> s >> c;
        Event one_event(w,s,c);
        Events.push_back(one_event);
    }
    std::sort(Events.begin(),Events.end(),Earier_Begin);
    std::vector<Event> Begin_Time_List(Events);
    std::sort(Events.begin(),Events.end(),Earier_End);
    std::vector<Event> End_Time_List(Events);
    std::queue<Event> Time_Seq;
    std::size_t rent_key = 1;
    std::size_t return_key = 1;
    //按时间顺序安排事件
    do{
        if(Begin_Time_List[rent_key-1].Key_number != End_Time_List[return_key-1].Key_number){
            if(Begin_Time_List[rent_key-1].Begin_Time < End_Time_List[return_key-1].End_Time){
                Time_Seq.push(Begin_Time_List[rent_key-1]);
                Time_Seq.back().Type = RENT;
                rent_key++;
            }
            else{
                Time_Seq.push(End_Time_List[return_key-1]);
                Time_Seq.back().Type =RETURN;
                return_key++;
            }
        }
        else{
            Time_Seq.push(Begin_Time_List[rent_key-1]);
            Time_Seq.back().Type = RENT;
            rent_key++;
            Time_Seq.push(End_Time_List[return_key-1]);
            Time_Seq.back().Type =RETURN;
            return_key++;
        }
    }while(rent_key<=Begin_Time_List.size()&&return_key<=End_Time_List.size());
    while(rent_key<=Begin_Time_List.size()){
        Time_Seq.push(Begin_Time_List[rent_key-1]);
        Time_Seq.back().Type = RENT;
        rent_key++;
    }
    while(return_key<=End_Time_List.size()){
        Time_Seq.push(End_Time_List[return_key-1]);
        Time_Seq.back().Type = RETURN;
        return_key++;
    }
    while(!Time_Seq.empty()){
        auto event= Time_Seq.front();
        if(event.Type == RETURN)
            key_box.Return(event);
        else
            key_box.Rent(event);
        Time_Seq.pop();
    }
    return OK;
}
