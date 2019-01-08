/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-29 11:09
#
# Filename: Tree.hpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include <vector>
#include <string>
#include <stack>
#include <array>
#ifndef TREE
#define TREE
#define TURE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define OBJECT      1
#define STRING      0
typedef int Status;
typedef std::string TElemType;
typedef std::vector<std::string>::iterator info_point;
typedef class TNode{
public:
    bool                    NodeType;
    TElemType               data = {};
    TElemType               value= {};
    TElemType               key= {};
    TNode            *first_child = NULL,*next_sibling = NULL;
    int                     depth = 0;
    TNode(std::string info);
    TNode(){};
    Status OUT(std::vector<std::string> & info,bool flags[96]);
    //TNode*                  alloc_sibling(info_point info);
    //TNode*                  alloc_child(info_point info);
}TNode,*Tree;
typedef struct Tool{
    std::vector<std::string> Info;
    friend Status Translate(TNode * Node,Tool &T);
}Tool;
//TNode* TNode::alloc_child(info_point info){
//    TNode * first_child = new TNode; 
//    first_child->data = *info;
//    this->first_child = first_child;
//    return first_child;
//}
//TNode* TNode::alloc_sibling(info_point info){
//    TNode * next_sibling = new TNode; 
//    next_sibling ->data = *info;
//    this->next_sibling = first_child;
//    return next_sibling ;
//}
Status TNode::OUT(std::vector<std::string> & info,bool flags[96]){
//    if(this->key.empty())
//        return ERROR;
    std::string line;
    for(int r = 0;r<this->depth;r++){
        if(flags[r])    
            line += "    ";
        else
            line += "│   ";
    }
    //index end 
    if(!this->next_sibling)
        line += "└── ";
    else
        line += "├── ";
    line += this->key;
    info.push_back(line);
    return OK;
}
TNode::TNode(std::string info){
    std::stack<char> S;
    std::string word;
    if(this->NodeType == OBJECT){
        for(auto ch : info){
            if(ch == '"' && S.empty()){
                S.push(ch);
                continue;
            }
            if(ch == '"' && !S.empty()){
                S.pop();
                this->key = word;
                word.clear();
                break;
            }
            if(ch != '"' && !S.empty())
                word+=ch;
        }
    }
    else if(this->NodeType == STRING){
        for(auto ch : info){
            if(ch == '"' && S.empty()){
                S.push(ch);
                continue;
            }
            if(ch == '"' && !S.empty()){
                S.pop();
                if(this->key.empty())
                    this->key = word;
                else
                    this->value = word;
                word.clear();
            }
            if(ch != '"' && !S.empty())
                word+=ch;
        }
    }
}
Status Translate(TNode * Node,Tool &T){
    static std::size_t pos = 1;
    if(!Node)
        return ERROR;
    if(pos > (T.Info.size()-1))
        return ERROR;
    //Ending situation
    if(T.Info[pos].find('}') != std::string::npos){
        pos++;
        if(pos > (T.Info.size()-1))
            return ERROR;
        else
            return OK;
    }
    //empty OBJECT
    if(Node->data.find('{') != std::string::npos &&
       Node->data.find('}') != std::string::npos){
        Node->NodeType = OBJECT;
        auto * sibling = new TNode(T.Info[pos]);
        Node->next_sibling = sibling;
        sibling->depth = Node->depth;
        pos++;
        if(Translate(Node->next_sibling,T))
            return OK;
    }
    //ordinary OBJECT
    if(Node->data.find('{') != std::string::npos){
        Node->NodeType = OBJECT;
        auto * child = new TNode(T.Info[pos]);
        Node->first_child = child;
        child->depth = Node->depth + 1;
        child -> data = T.Info[pos];
        pos++;
        if(!Translate(Node->first_child,T))
            return ERROR;
        else if(pos <= (T.Info.size()-1)){
            auto * sibling = new TNode(T.Info[pos]);
            Node->next_sibling = sibling;
            sibling->depth = Node->depth;
            sibling -> data = T.Info[pos];
            pos++;
            if(Translate(Node->next_sibling,T))
                return OK;
        }
    }
    //ordinary STRING
    if(Node->data.find('{') == std::string::npos &&
       Node->data.find('}') == std::string::npos){
        Node->NodeType = STRING;
        auto * sibling = new TNode(T.Info[pos]);
        Node->next_sibling = sibling;
        sibling->depth = Node->depth;
        sibling -> data = T.Info[pos];
        pos++;
        if(Translate(Node->next_sibling,T))
            return OK;
    }
    return OK;
}
TNode* BFS_Search(TNode *tree,std::vector<std::string> info,std::size_t deepth = 1){
    tree = tree->first_child;
    if(tree){
        while(tree->next_sibling){
            if(tree->key == info[deepth-1]){
                if(deepth == info.size())
                    return tree;
                else
                    return BFS_Search(tree,info,++deepth);
            }
            else
                tree = tree->next_sibling;
        }
        return NULL;
    }
    else return NULL;
}
Status Search(TNode * tree,std::string info){
    std::vector<std::string> INFO;
    std::string word = {};
    for(auto ch : info){
        if(ch == '.'){
            if(!word.empty()) {
                INFO.push_back(word);
                word.clear();
            }
        }
        else
            word+=ch;
    }
    if(!word.empty())
        INFO.push_back(word);
    BFS_Search(tree,INFO);
    return OK;
}
Status DFS_Out(TNode * tree,std::vector<std::string> & info){
    static bool flags[96] = {0};
    if(tree){
        if(!tree->next_sibling) //no next_sibling
            flags[tree->depth] = 1;
        if(tree->OUT(info,flags)){
            if(DFS_Out(tree->first_child,info))
                if(DFS_Out(tree->next_sibling,info))
                    return OK;
        }
        return ERROR;
    }
    else
        return OK;
}
#endif
