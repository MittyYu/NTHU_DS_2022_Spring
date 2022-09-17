
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
using namespace std;

#define FLT_MAX numeric_limits<float>::max()
#define N 100

int n, origin;

int minDistance(float dist[], bool set[])
{
    float min = FLT_MAX;
    int min_index;
    for (int i = 0; i < n; i++)
        if (set[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;
    return min_index;
}

void printPath(int parent[], int j, int target)
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j], target);
    if(j != target)
        cout << j << " -> ";
    else 
        cout << j;
}

void Result(float dist[], int n, int parent[])
{
    for (int i = 0; i < n; i++) {
        if(i != origin){
            cout << origin << " -> ";
            printPath(parent, i, i);
            cout << "\n";
        }
    }
}

void dijkstra(float **graph, int src)
{
    float *dist = new float[n];
    bool *set = new bool[n];
    int *parent = new int[n];

    for(int i = 0; i < n; i++){
        set[i]=false;
        parent[i]=-1;
    }
 
    for (int i = 0; i < n; i++)
        dist[i] = FLT_MAX;
    dist[src] = 0.0;
 
    for (int i = 0; i < n - 1; i++) {
        int u = minDistance(dist, set);
        set[u] = true;
        for (int v = 0; v < n; v++)
            if (!set[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }
    Result(dist, n, parent);
}


int main(){
    cin >> n >> origin;
    float** adjMatrix = new float*[n];
    for(int i = 0; i < n; ++i)
        adjMatrix[i] = new float[n];
    
    for(int i = 0; i < n; i++){
        for(int j =0; j < n; j++){
            float tmp;
            cin >> tmp;
            adjMatrix[i][j] = abs(round(log2(tmp)*100)/100.0);
        }
    }
    cout << "The origin is: " << origin << "\n";
    dijkstra(adjMatrix, origin);
    return 0;
}