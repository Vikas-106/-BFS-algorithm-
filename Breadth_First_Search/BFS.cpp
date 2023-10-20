#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list
    
public:
    Graph(int V);
    void addEdge(int v, int w);
    void BFS(int s,int e);
    void retrace( int e,std::vector<int>& prev);
};

Graph::Graph(int V) { 
    this->V = V;
    adj.resize(V);  // resizing the vector to no of vertices 
}

void Graph::addEdge(int v, int w) { 
    adj[v].push_back(w);  // adding edges
}

void Graph::BFS(int s,int e) {
   std::vector<bool>visited(V, false); // to check the node is visited no not 
    vector<int> prev(V,-1); // to track the parent node , assigning all values as -1
    queue<int> queue;  // this queue is used to push the node to visited vector

    visited[s] = true;  //making the start node visited 
    queue.push(s);    // pushing it to the queue 

    while (!queue.empty()) {  //until the queue is empty the loop should work 
        s = queue.front();   
       // cout << s << " ";   //printing the first element in the queue
        queue.pop();     // removing the first element in the queue

        for (int i : adj[s]) {  
            if (!visited[i]) {  // if the next node is not visited 
                visited[i] = true;  // make it true
                queue.push(i);   // and add it to the queue
                prev[i]=s; // adding the parent node to the vector
            } 
        }
    } 
    
    retrace(e,prev);
}

void Graph::retrace( int e,std::vector<int>& prev) // retraces the path from end node to start 
{
  std::vector<int> path; // created new vector for showing the path 
  for (int i = e; i !=-1;i=prev[i] )
  {
    path.push_back(i);   // adding the path to the vector
  }
  for (auto i = path.rbegin(); i !=path.rend(); i++)
  {
    std::cout<<*i<<" ";   // the path
  }

  std::cout<<std::endl;
  
   
}
int main() {
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
    g.BFS(0,5);
    

    return 0;
}
