#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

class GRAPH_2D {

public:
   void createGraph(int r, int c,std::vector<std::vector<int>>& a);
   void BFS(int m, int sr, int sc, int er, int ec, int c, int r,std::vector<std::vector<int>>& a);
   void trace(std::vector<int>& parent, int endindex, int c,std::vector<std::vector<int>>& a,int r);
   
};

// rows, columns and the vector a is passed inside the function for creating the matrix
void GRAPH_2D::createGraph(int r, int c, std::vector<std::vector<int>>& a) { 
    
    std::cout << "Enter the value in the matrix 0 or 1, 0 for free space and 1 for obstacles: " << std::endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            std::cin >> a[i][j];
        }
    }

    std::cout << "Your matrix: " << std::endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            std::cout << a[i][j];
        }
        std::cout << std::endl;
    }
}

void GRAPH_2D::BFS(int m, int sr, int sc, int er, int ec, int c, int r,std::vector<std::vector<int>>& a) {
    int startindex = sc * c + sr; // converting the coordinates into index 
    int endindex = ec * c + er;
    int grvector[] = {1, -1, 0, 0}; // these two vectors are for moving to adjacent sides that is (top,bottom,left and right)
    int gcvector[] = {0, 0, 1, -1};    
    std::vector<bool> visited(m, false); // vector for tracking the visited nodes
    std::vector<int> parent(m, -1);  // vector for tracking the parent nodes
    std::queue<int> q; // the queue using for the algorithm 
    q.push(startindex); // pushing the starting index to the queue
    visited[startindex] = true; // making the starting index visited

    while (!q.empty()) {   // till the queue is empty the loops runs
        int currentIndex = q.front();  // assigning the first element of the queue to currentIndex
        q.pop();   // removing the first element from the queue
        int currentX = currentIndex % c;  // these 2 program is for converting the index to coodinates 
        int currentY = currentIndex / c;

        for (int i = 0; i < 4; i++) {   // we convert these into coordinates because to access the adjacent node
            int NewX = currentX + grvector[i];// these 2 program as discussed earlier used to make the node move in adjacent direction 
            int NewY = currentY + gcvector[i];

            if ((NewX >= 0 && NewX < r) && (NewY >= 0 && NewY < c)) { // verifying whether its within boundary or not
                int NewIndex = NewY * c + NewX;  // converting the gained coordinates into index

                if (!visited[NewIndex]&& a[NewX][NewY]!=1) {  // normal conditions for bfs algorithm 
                    visited[NewIndex] = true;
                    q.push(NewIndex);
                    parent[NewIndex] = currentIndex;
                }
            }
        }
    }

    trace(parent, endindex, c, a,r); // for creating a new matrix with path shown 
}

void GRAPH_2D::trace(std::vector<int>& parent, int endindex, int c, std::vector<std::vector<int>>& a,int r) {
    int currentx = endindex;
    std::vector<int> path;
    for (int i = currentx; i != -1; i = parent[i]) {  // adding the parent nodes to the path 
        path.push_back(i);
    }

    std::reverse(path.begin(), path.end()); // reversing the path because we are retracing the path form goal to start point 
    std::cout<<"Your path to the goal : "<<std::endl;
    for (auto i = path.begin(); i != path.end(); i++) {
        
        std::cout << *i % c << "," << *i / c << std::endl; //converting the index to coordinates 
        int x = *i % c;
        int y = *i / c;
        a[x][y]=-1;
    }
    std::cout<<"Your updated matrix : "<<std::endl;
   for (int i = 0; i < r; i++)
   {
    for (int j = 0; j < c; j++)
    {   
        if(a[i][j]==1){
            std::cout<<"1";
        }
        if(a[i][j]==-1){
            std::cout<<"*";
        }
        if(a[i][j]==0){
            std::cout<<"0";
        }
    }
    std::cout<<std::endl;
   }
   
 }  



int main() {
    GRAPH_2D g;
    int r, c, m; // rows, columns , total elements 

    std::cout << "Enter the rows of the matrix: ";
    std::cin >> r;
    std::cout << "Enter the columns of the matrix: ";
    std::cin >> c;
    m = r * c;
    
    std::vector<std::vector<int>> a(r,std::vector<int>(c)); // initializing matrix

    g.createGraph(r, c, a); //creates the matrix 

    int sr, sc, er, ec; // starting row, starting column , ending row, ending column
    std::cout << "Enter your starting coordinates: " << std::endl;
    std::cin >> sr >> sc; // coordinates x and y 

    std::cout << "Enter your ending coordinates: " << std::endl;
    std::cin >> er >> ec; // coofdinates x and y 

    g.BFS(m, sr, sc, er, ec, c, r,a); // implimenting the algorithm 

    return 0;
}
