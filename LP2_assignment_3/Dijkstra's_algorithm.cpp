//DIJKSTRA'S Algorithm

#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(vector<vector<pair<int,int>>>& v, int n){
    vector <int> dist(n,100);
    priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    cout<<"Enter start node: ";
    int s ;cin>>s;
    pq.push({0,s});
    dist[s] = 0;
    while (!pq.empty())
    {
        auto [currDist, node] = pq.top();
        pq.pop();
        for (auto i:v[node])
        {
            auto [adjNode,adjDist] = i;
            if(currDist+adjDist< dist[adjNode]){
                dist[adjNode] = currDist+adjDist;
                pq.push({dist[adjNode] , adjNode});
            }
        } 
    }
    return dist;
}

int main(){
    cout<<"Enter number of vertices: ";
    int V;
    cin>>V;
    vector<vector<pair<int,int>>> v(V);

    cout<<"Enter number of edges: ";
    int e;
    cin>>e;
    for (int i = 0; i < e; i++)
    {
        cout << "Enter edge (u v weight): ";
        int x, y, w;
        cin >> x >> y >> w;
        
        v[x].push_back({y, w});
        v[y].push_back({x, w});
    }
    vector<int> path = dijkstra(v,V);
    
    cout << "Shortest distances from the start node:" << endl;
    for (int i = 0; i < V; i++) {
        if (path[i] == INT_MAX) {
            cout << "Node " << i << ": INF" << endl;
        } else {
            cout << "Node " << i << ": " << path[i] << endl;
        }
    }
    return 0;
}
