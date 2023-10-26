#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>


#define INF 0x3f3f3f3f  // defining infinity 

typedef std::pair<int,int> pair;  // changing the name to pair 

class dijkstra
{
    int V;
    std::vector<std::vector<std::pair<int,int>>> adj;
public:
   dijkstra(int V);
   void addEdge(int s, int n , int w);
   void algorithm(int s, int e);
   void retrace(std::vector<int>& parent  , int e);
};

dijkstra::dijkstra(int V)
{
   this->V=V;
   adj.resize(V);
}

void dijkstra::addEdge(int s, int n, int w)
{
   
   adj[s].push_back(std::make_pair(n,w));  
   adj[n].push_back(std::make_pair(s,w));
}

void dijkstra::algorithm(int s,int e)
{

   std::vector<int>dist(V,INF);  //initializing all values as infinity
   std::vector<int>parent(V,-1);  // initializing all values as -1 
   std::priority_queue< pair, std::vector<pair> , std::greater<pair> > pq; // initializing priority queue 
   pq.push(std::make_pair(s,0));  // adding the start node with its weight to priority queue
   dist[s]=0;  // assigning the weights to dist vector

   while(!pq.empty()){
       
       int u = pq.top().first;  //getting the first / smallest element in the queue and removing it
       pq.pop();

       for (auto &&i : adj[u])  // checking the adjacent nodes 
       {
       
          int v=i.first;   // gets the node 
          int weight=i.second; // gets the nodes weight
          if(dist[v] >dist[u]+weight){  // if the current adjacent nodes weight is larger assign the smallest weight
             dist[v]=dist[u]+weight;  
             pq.push(std::make_pair(v,dist[v])); // adding the current adjacent node and weight to queue
             parent[v]=u; // tracking the path by adding the parent node 
     } 
       }
   }
 std::cout<<"Vertex distance from source "<<std::endl; //it prints the smallest weight from start node for each other node 
   for (int i = 0; i < V; i++)
   {
    std::cout<< i <<"   "<<dist[i]<<std::endl;
   }

   retrace(parent,e);
   
}

void dijkstra::retrace(std::vector<int>& parent, int e) // retraces the path 
{
    std::vector<int>path;
    for (int i = e; i != -1; i= parent[i])
    {
       path.push_back(i);
    }
    
    std::reverse(path.begin(),path.end());
   
   std::cout<<"your shortest path : "<<std::endl;

    for (auto i = path.begin(); i != path.end(); i++)
    {
        std::cout<<*i<< " ";
    }
    
    std::cout<<std::endl;
    
}


 
int main(){
 
 dijkstra g(9); // give your vertex here
 
    g.addEdge(0, 1, 4);  // node , its adjacent node , its weight 
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
 
 
 g.algorithm(0,8); // give your start and end node here
 

}
