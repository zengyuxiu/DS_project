/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2019 All rights reserved.
#
# Last modified:	2019-01-09 14:22
#
# Filename:		main.cpp
#
# Description: 
#
=============================================================================*/
#include<vector>
#include<typeinfo>
#include<strstream>
#include<algorithm>
#include <array>
#include <iostream>
int nan = 25;
using namespace std;
int Cal(int num1,int num2,int operator_n){
    switch(operator_n){
        case 1:
            return (num1+num2);
            break;
        case 2:
            return (num1-num2);
            break;
        case 3:
            return (num1*num2);
            break;
        case 4: 
            if(num1 % num2)
                return nan;
            else
                return (num1/num2);
            break;
        default:
            return 0;
    }
}
string  Int2String(int number){
    strstream   tmp_string;
    string      result;
    tmp_string << number;
    tmp_string >> result;
    return result;
}
char Operatation2Char(int op){
    switch(op) {
        case 1:
            return '+';
            break;
        case 2:
            return '-';
            break;
        case 3:
            return '*';
            break;
        case 4:
            return '/';
            break;
        default:
            return '\000';
            break;
    }
}
//暴力枚举
int main(){
    array<int,4>            number; 
    int                     op1 = 0,op2 =  0,op3 = 0;
    vector<string>          results;
    for(auto &num:number)
        std::cin >> num;
    std::sort(number.begin(),number.end());
    //三重循环操作数
    for(op1 = 1;op1<=4;op1++)
        for(op2 = 1;op2<=4;op2++)
            for(op3 = 1;op3<=4;op3++){
               do{
                   //(((a,b),c),b)
                    auto result1 = Cal(number[0],number[1],op1) ;
                    auto result2 = Cal(result1,number[2],op2) ;
                    auto result3 = Cal(result2,number[3],op3) ;
                    if(result1 == nan || result2 == nan || result3 == nan)
                        continue;
                    if(result3 == 24){
                        string result;
                        result += "((";
                        result += Int2String(number[0]);
                        result += Operatation2Char(op1);
                        result += Int2String(number[1]);
                        result+= ')';
                        result += Operatation2Char(op2);
                        result += Int2String(number[2]);
                        result+= ')';
                        result += Operatation2Char(op3);
                        result += Int2String(number[3]);
                        results.push_back(result);
                    }
                   //((a,b),(c,d))
                    result1 = Cal(number[0],number[1],op1) ;
                    result2 = Cal(number[2],number[3],op3) ;
                    result3 = Cal(result1,result2,op2) ;
                    if(result1 == nan || result2 == nan || result3 == nan)
                        continue;
                    if(result3 == 24){
                        string result;
                        result += "(";
                        result += Int2String(number[0]);
                        result += Operatation2Char(op1);
                        result += Int2String(number[1]);
                        result+= ')';
                        result += Operatation2Char(op2);
                        result += "(";
                        result += Int2String(number[2]);
                        result += Operatation2Char(op3);
                        result += Int2String(number[3]);
                        result+= ')';
                        results.push_back(result);
                    }     
               }while(next_permutation(number.begin(),number.end())) ;
            }
    for(string res:results)
        std::cout << res << std::endl;
     return 1;
}
