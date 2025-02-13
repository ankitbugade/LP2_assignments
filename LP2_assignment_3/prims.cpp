#include <bits/stdc++.h>
using namespace std;
#define V 6

int findKey(vector <int>& key, vector<bool>& mstSet){
    int minKey = INT_MAX, min_index;
    for(int i=0;i<V;i++){
        if(mstSet[i]==false && key[i]<minKey){
            minKey = key[i];
            min_index = i;
        }
    }
    return min_index;
}


void printMst(vector<int>& parent,vector<vector<int>>& graph ){
    cout<<"Edge\tWeight"<<endl;
    for(int i=1;i<V;i++){
        cout<<parent[i]<<" --- "<<i<<"\t"<<graph[parent[i]][i]<<endl;
    }
}


void primMST(vector<vector<int>>& graph){
    vector <bool> mstSet(V,false);
    vector <int> parent(V);
    vector <int> key(V,INT_MAX);

    key[0] = 0;
    parent[0] = -1;

    for(int count = 0;count < V ; count++){
        int u = findKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
        {
            if(mstSet[v] == false && graph[u][v]!=0 && graph[u][v] < key[v]){
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    printMst(parent, graph);

}


int main(){
    vector<vector<int>> graph = { { 0, 1, 3, 6, 0, 0 },
                                  { 1, 0, 5, 3, 4, 0 },
                                  { 3, 5, 0, 3, 0, 0 },
                                  { 0, 3, 0, 0, 4, 4 },
                                  { 0, 2, 3, 4, 0, 3 },
                                  { 0, 0, 0, 4, 3, 0 } };

    primMST(graph);
    return 0;
}