/*=============================================================================
#
# Author:Yuxiu Zeng
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified: 2018-12-25 00:31
#
# Filename: ShortestPath_DIJ.cpp
#
# Description: 
#
=============================================================================*/
#include<stdio.h>
#include<iomanip>
#include<array>
#include <vector>
#include <queue>
#include "mgraph.h"
typedef struct Arc:public ArcCell{
    int Start_Dest_Vex[2];
    Arc(ArcCell arc_cell,int Start,int Dest){
        this->assign(arc_cell);
        this->Start_Dest_Vex[0] = Start;
        this->Start_Dest_Vex[1] = Dest;
    }
    void operator = (ArcCell arc_cell){
        this->assign(arc_cell);
    }
    int & operator [](int i){
        return this->Start_Dest_Vex[i];
    }
}Arc;
typedef std::vector<Arc> Path;
typedef struct ShortPathTable{
    VertexType                      current_vex = 0;
    int                             VexNum;
    std::vector<Path>               ShortPath;
    VRType                          Length[MAX_VERTEX_NUM];
    bool                            finish[MAX_VERTEX_NUM];
    VertexType                      current_new_vex;
    ShortPathTable(int VexNum){
        this->VexNum = VexNum;
        //this->ShortPath.assign(VexNum,{{0,0}});
        for(int i = 0;i<VexNum;++i){
            Path            init_path;
            init_path.clear();
            this->ShortPath.push_back(init_path);
        }
        //this->Length = new int[VexNum];
        //this->finish = new bool[VexNum] {FALSE};
    }
    int Add(VertexType &v,MGraph &G);
    double  Cc(){
        double sum = 0;
        for(int r = 0;r<VexNum;r++) 
            sum += this->Length[r];
        return ((double)(this->VexNum-1)/sum);
    }
    int & operator ()(int v,MGraph &G){
        int i = LocateVex(G,v);
        return this->Length[i];
    }
}ShortPathTable;
int ShortPathTable::Add(VertexType &v, MGraph &G){
    std::vector<VRType> path_length;
    VRType Length = 0;
    //add new vex
    int i = LocateVex(G,this->current_new_vex);
    int j = LocateVex(G,v);
    Arc new_path(G.arcs[i][j],i,j);
    this->ShortPath[i].push_back(new_path);
    for(auto arc:this->ShortPath[i]){
        auto arc_cell = G.arcs[arc[0]][arc[1]];
        Length += arc_cell.adj;
    }
    //Del new vex
    this->ShortPath[i].pop_back();
    return Length;
}
void ShortestPath_DIJ(MGraph &G, int v0 ,ShortPathTable &D){
    for(int v = 1;v<=G.vexnum;++v) {
        int i = LocateVex(G,v0);
        int j = LocateVex(G,v);
        auto arc_cell = G.arcs[i][j];
        D.finish[j]  = FALSE;
        D(v,G) = arc_cell.adj;
        //D(v,G) = G.arcs[v0][v].adj;
        //for(int w = 0;w<G.vexnum;++w) 
        //   P[v][w] = FALSE;
        if(D(v,G) < INFINITY) {
            Arc v_path(arc_cell,i,j);
            D.ShortPath[j].push_back(v_path);
            //D.ShortPath[j].push_back({i,j});
        }
    }
    D(v0,G) = 0;
    D.finish[LocateVex(G,v0)] = TURE;
    //G.vexnum -1 tmies;
    for(int i = 1;i<G.vexnum;++i){
        VRType min = INFINITY; 
        for(int w = 1;w<=G.vexnum;++w)
            if(!D.finish[LocateVex(G,w)])
                if(D(w,G)<min){
                    D.current_new_vex = w;
                    min = D(D.current_new_vex ,G);
                }
    D.finish[LocateVex(G,D.current_new_vex)] = TURE;
    for(int w = 1;w<=G.vexnum;++w)
        if(!D.finish[LocateVex(G,w)] && D.Add(w,G)<D(w,G)){
            int i = LocateVex(G,D.current_new_vex);
            int j = LocateVex(G,w);
            Arc new_path(G.arcs[i][j],i,j);
            D(w,G) = D.Add(w,G);
            D.ShortPath[j].clear();
            D.ShortPath[j] = D.ShortPath[i];
            D.ShortPath[j].push_back(new_path);
        }
    }
}
int main(){
    int order_number = 0;
    MGraph G;
    CreateUDG(G);
    std::cin >> order_number;
    std::vector<int> order;
    for(int i = 1;i<=order_number;++i){
        int vex;
        std::cin >> vex;
        order.push_back(vex);
    }
    std::vector<ShortPathTable>      tables;
    for(int i = 1;i<=G.vexnum;++i){
        ShortPathTable short_path_table(G.vexnum);
        short_path_table.current_vex = i;
        ShortestPath_DIJ(G,i,short_path_table);
        tables.push_back(short_path_table);
    }
    for(int vex:order){
        std::cout <<"Cc("<<vex<<") = "<<std::setprecision(2)<<tables[LocateVex(G,vex)].Cc()<<std::endl;
    }
    return OK;
}
