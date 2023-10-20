#include<iostream>
#include<vector>
#include<algorithm>

class Graph 
{
    int V;
    std::vector<std::vector<int>> adj;
    std::vector<bool> visited;
    std::vector<int> parent;
public:
   Graph(int v);
   void addEdge(int v, int w);
   void DFS(int s);
   void retrace(int e);
};

Graph::Graph(int v){
    this->V = v;
    adj.resize(V);
    visited.resize(V);
    parent.resize(V);
    for (int i = 0; i < V; i++)
    {
        visited[i]=false;
        parent[i]=-1;
    }
    
}

void Graph::addEdge(int v, int w){

    adj[v].push_back(w);

}

void Graph::DFS(int s){  //using recursion to visit other nodes 
    if(visited[s]==true){
        return;
    }
    visited[s]=true; 

    for (auto &&i : adj[s])
    {    
        if(!visited[i]){
            DFS(i);
            parent[i]=s;
        }
    }
}

void Graph::retrace(int e){
   int current=e;
   std::vector<int> path;
   for (int i = current; i!= -1; i = parent[i])
   {
     path.push_back(i);
   }
   std::reverse(path.begin(),path.end());
   std::cout<<"Your path: ";
   for (auto i = path.begin(); i != path.end(); i++)
   {
      std::cout<<*i<<" ";
   }
   
   std::cout << std::endl;
}

int main(){
      Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 0);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(2, 1);
    g.addEdge(2, 5);
    g.addEdge(3, 0);
    g.addEdge(3, 4);
    g.addEdge(3, 6);
    g.addEdge(4, 1);
    g.addEdge(4, 3);
    g.addEdge(4, 5);
    g.addEdge(5, 2);
    g.addEdge(5, 4);
    g.addEdge(6, 3);
    g.DFS(0);

    g.retrace(6);
    return 0;
}
