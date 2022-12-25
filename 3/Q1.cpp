#include<iostream>
#include <bits/stdc++.h>
using namespace std;

struct node{
    int cost;
    int prev;
    int id;
    node(){};
    node(int id, int cost,int prev){
        this->cost=cost;
        this->prev=prev;
        this->id=id;
    }
};

bool alreadyIn(const vector<node>& visited , int id){
    for(int i=0 ; i<visited.size() ; i++){
        if(visited[i].id==id)
            return true;
    }
    return false;
}

void printNodes(const vector<node> vec){
    cout<<"=============================\n";
    int weight=0;
    for(int i=0 ; i<vec.size() ; i++){
        weight+=vec[i].cost;
        cout<<"id: v"<<vec[i].id+1<<" prev: v"<<vec[i].prev+1<<" cost: "<<vec[i].cost<<endl;
    }
    cout<<"=============================\n";
    cout<<"Total weight of the spanning tree: "<<weight<<endl;
    cout<<"=============================\n";
}

int main(){
    int mSize = 7;
    int adjMatrix[mSize][mSize]={
    {0,2,4,1,0,0,0},
    {2,0,0,3,10,0,0},
    {4,0,0,2,0,5,0},
    {1,3,2,0,7,8,4},
    {0,10,0,7,0,0,6},
    {0,0,5,8,0,0,1},
    {0,0,0,4,6,1,0},
    };
    vector<node> visited;
    int startNode=0;
    visited.push_back({startNode,0,-1});

    
    while(visited.size()!=mSize){

        node temp={-1,INT_MAX,-1};

        for(int i=0 ; i<visited.size() ; i++){

            for(int j=1 ; j<mSize ; j++){

                if(alreadyIn(visited,j))
                    continue;
                    
                if(temp.cost>adjMatrix[visited[i].id][j]&&adjMatrix[visited[i].id][j]>0){
                    temp.id=j;
                    temp.cost=adjMatrix[visited[i].id][j];
                    temp.prev=visited[i].id;
                }
            }
        }
        visited.push_back(temp);
    }
    printNodes(visited);
}