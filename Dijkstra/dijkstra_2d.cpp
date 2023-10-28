#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

#define INF 0x3f3f3f3f
 
class GRAPH_2D {
   int R; // rows 
   int C;  // columns
   
public:
   
   void algorithm(int m, int sr, int sc, int er, int ec, int c, int r,std::vector<std::vector<int>>& a);
   void trace(std::vector<int>& parent, int endindex,std::vector<std::vector<int>>& a);
   void Newmatrix(std::vector<int>& path,std::vector<std::vector<int>>& a);
};

void GRAPH_2D::algorithm(int m, int sr, int sc, int er, int ec, int c, int r,std::vector<std::vector<int>>& a) // implementing dijkstra algorithm 
 { 
    this->R = r;
    this->C = c;
    int startindex = sc * c + sr;  // converting coordinates to index 
    int endindex = ec * c + er;
    int grvector[] = {1, -1, 0, 0};  // for moving to adjacent cells 
    int gcvector[] = {0, 0, 1, -1};
  
    std::vector<int> parent(m, -1);  // initializing parent vector will all element -1 for tracking the path 
    std::vector<std::vector<int>> dist(r,std::vector<int> (c,INF)); 
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;
    pq.push(std::make_pair(a[0][0],startindex));
    dist[0][0]=a[0][0];
  
    while (!pq.empty()) {
        int cost = pq.top().first;
        int currentIndex = pq.top().second;
        int currentX = currentIndex % c;
        int currentY = currentIndex / c;
        pq.pop();
        for (int i = 0; i < 4; i++) {
            int NewX = currentX + grvector[i];
            int NewY = currentY + gcvector[i];

            if ((NewX >= 0 && NewX < r) && (NewY >= 0 && NewY < c) && a[NewX][NewY]!=-1) {

                int NewIndex = NewY * c + NewX;
                if (dist[NewX][NewY] > cost + a[NewX][NewY]) {
                    dist[NewX][NewY] = cost + a[NewX][NewY];
                    pq.push(std::make_pair(dist[NewX][NewY],NewIndex));
                    parent[NewIndex] = currentIndex;
                }
            }
        }
    }

   trace(parent, endindex, a);
}
void GRAPH_2D::trace(std::vector<int>& parent, int endindex, std::vector<std::vector<int>>& a)
 {
    
    int currentx = endindex;
    std::vector<int> path;
    
    for (int i = currentx; i != -1; i = parent[i]) {
        path.push_back(i);
    }

    std::reverse(path.begin(), path.end());

    std::cout << "Your path to the goal: " << std::endl;
    for (auto i = path.begin(); i != path.end(); i ++) {
        std::cout << *i%C << "," << *i/C << std::endl;
        a[*i%C][*i/C]=-2;
    }
    std::cout<<std::endl;
    Newmatrix(path,a);
}
void GRAPH_2D::Newmatrix(std::vector<int>& path,std::vector<std::vector<int>>& a){
   
     std::cout<<"Your updated matrix is : "<< std::endl;
    
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (a[i][j] == -2) {

                std::cout << "*";
            }
            else{
                std::cout<<"1";
            } 
        } std::cout<<std::endl;
            }
          
        }


int main() {

    GRAPH_2D g;

    int r = 5, c = 5 , m;  // rows, columns , total elements
    
    m = r * c;
    
    std::vector<std::vector<int>> a(r,std::vector<int>(c));  //  initializing the 2d array 

     a = {
            {3, 1, 3, 9, 2},         // -1 for obstacles 
            {-1, 5, -1, 2, 2},
            {1, 2, 2, 1, 3}, 
            {4, 2, 2, 2, 1},
            {1, 7, 3, 1, 6}
        };

    int sr, sc, er, ec; // start row, column , end row, column

    std::cout << "Enter your starting coordinates: " << std::endl;
    std::cin >> sr >> sc;

    std::cout << "Enter your ending coordinates: " << std::endl;
    std::cin >> er >> ec;

    g.algorithm(m, sr, sc, er, ec, c, r,a);

    return 0;
}
