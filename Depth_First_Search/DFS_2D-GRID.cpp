#include<iostream>
#include<vector>
#include<algorithm>

class Graph{
    int R;  // no of rows 
    int C;  // mo of columns 
    std::vector<std::vector<int>> adj; // for finding adjacent nodes
    std::vector<bool> visited; // to track visited nodes
    std::vector<int> parent; // to find the path 
public: 
    void creatematrix(int r,int c,std::vector<std::vector<int>>& a);  // creates the matrix
    void initialize(int m,std::vector<std::vector<int>>& a,int sr, int sc, int r, int c); // inintializes the vectors 
    void DFS(std::vector<std::vector<int>>& a,int startIndex);   // does dfs algorithm 
    void retrace (int er, int ec , std::vector<std::vector<int>>& a);  // to find the path 
};

void Graph::creatematrix(int r,int c,std::vector<std::vector<int>>& a){
    std::cout<<"Enter the values in matrix 0 for free space and 1 for obstacle "<<std::endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            std::cin>>a[i][j];
        }
        
    }
    std::cout<<"--------Your matrix----------"<<std::endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            std::cout<<a[i][j];
        }
        std::cout<<std::endl;
    }
    
}

void Graph::initialize(int m,std::vector<std::vector<int>>& a,int sr, int sc ,int r, int c){

    visited.resize(m); // resizing to m 
    parent.resize(m);

   for (int i = 0; i < m; i++)
   {
     visited[i]=false; // setting everytinng false and -1 
     parent[i]=-1;
   }
 int startIndex = sc * c + sr; // converting the coordinates to index
 this->R=r;
 this->C=c;
 DFS( a,startIndex);

}

void Graph::DFS(std::vector<std::vector<int>>& a,int startIndex){

    int rvector[]={1,-1,0,0}; // these 2 are for moving to adjacent nodes 
    int cvector[]={0,0,1,-1};

    if(visited[startIndex]==true){  // if visited comes out of function
        return;
    }

    visited[startIndex]=true; // setting the node visited 
    int currentx=startIndex % C;  // converting the index to coordinates 
    int currenty=startIndex / C;

    for (int  i = 0; i < 4; i++)
    { 
        int NewX = currentx + rvector[i]; // moving the node to adjacent sides 
        int Newy = currenty + cvector[i];

        if ((NewX >=0 && NewX < R )&& (Newy >= 0 && Newy < C))  // checking if its valid 
        {
            int Newindex= Newy * C + NewX; // converting the new coordinates to index 
            if (!visited[Newindex] && a[NewX][Newy]!= 1) // checking if the new index is visited or not and if the node has obstacles 
            {
                parent[Newindex]= startIndex;  // updating the start node to parent 
                DFS(a,Newindex);  // calling the function again 
            }
            
        }
        
        
    }

}

void Graph::retrace(int er, int ec, std::vector<std::vector<int>>& a){
    int endIndex = ec * C + er;
    std::vector<int> path;
    for (auto i = endIndex; i != -1; i = parent[i])
    {
       path.push_back(i);
    }
    std::reverse(path.begin(),path.end());

    std::cout<<"------Your path : -------"<<std::endl;

    for (auto i = path.begin(); i != path.end(); i++)
    {
        int x=*i%C;
        int y=*i/C;
        std::cout<<"( "<< x <<" , "<< y << " )"<<std::endl;
        a[x][y] = -1;
    }
    
    std::cout<<"---------Updated matrix with path : -------"<<std::endl;
    
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if(a[i][j]== -1){
                std::cout<<"#";
            }
            if(a[i][j]== 1){
                std::cout<<"1";
            }
            if(a[i][j]== 0){
                std::cout<<"0";
            }
            
        }
        std::cout<<std::endl;
    }
}

int main(){
    Graph g;
    int r, c, m ; // rows , columns , size of matrix 
    std::cout<<"Enter the rows of the matrix : ";
    std::cin>>r;
    std::cout<<"Enter the columns of the matrix : ";
    std::cin>>c;
    m= r*c;
    std::vector<std::vector<int>> a(r, std::vector<int>(c));
    g.creatematrix(r,c,a);

    int sr, sc, er, ec; // start row , column end row, column
    std::cout<<"Enter your starting coordinate : "<<std::endl;
    std::cin>>sr>>sc;
    std::cout<<"Enter your ending coordinate : "<<std::endl;
    std::cin>>er>>ec;
    
    g.initialize(m,a,sr, sc, r ,c);

    g.retrace(er, ec , a);

}