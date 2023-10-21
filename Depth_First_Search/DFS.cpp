#include<iostream>
#include<vector>
#include<algorithm>

class Graph 
{
    int V;  //no of vertices 
    std::vector<std::vector<int>> adj; // for storing adjacent nodes 
    std::vector<bool> visited; // to keep track of visited nodes
    std::vector<int> parent;  // to track the path 
public:
   Graph(int v);  // for initializing 
   void addEdge(int v, int w); // adding edges 
   void DFS(int s); // implementation of dfs algorithm 
   void retrace(int e); // finding the path 
};

Graph::Graph(int v){
    this->V = v;
    adj.resize(V); // resizing it to no of vertices 
    visited.resize(V);
    parent.resize(V);
    for (int i = 0; i < V; i++)
    {
        visited[i]=false;  // making all node false 
        parent[i]=-1;  // making all node -1 , will be useful to find the end of the node while finding the path 
    }
    
}

void Graph::addEdge(int v, int w){

    adj[v].push_back(w);  // adding the edges

}

void Graph::DFS(int s){  //using recursion to visit other nodes 
    if(visited[s]==true){
        return;    // comes out the function if the node is visited already
    }
    visited[s]=true;  // making the node visited 

    for (auto &&i : adj[s])  // checking the adjacent nodes 
    {    
        if(!visited[i]){   // if not visited
            DFS(i);      // calling the funtion again 
            parent[i]=s;  // adding the node to parent for tracking the path 
        }
    }
}

void Graph::retrace(int e){
   int current=e;
   std::vector<int> path;
   for (int i = current; i!= -1; i = parent[i])  // adding the nodes to path vector
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
      Graph g(7); // no of vertices 
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
    g.DFS(0); // give start node 

    g.retrace(6); // give your end node
    return 0;
}
