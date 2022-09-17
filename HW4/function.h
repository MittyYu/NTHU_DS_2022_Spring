#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <queue>

using namespace std;

class Node{
    private:
        int idx;
        string name;
        int ps; //preference score
        bool closed;

    public:
        Node(int idx, string name, int ps, bool closed);

        int get_idx(){return idx;};
        string get_name(){return name;};
        int get_ps(){return ps;};
        bool get_status(){return closed;};

        void set_status(bool isClosed){closed = isClosed;};

};

bool operator== (Node& node, string str){
    return node.get_name() == str;
}

class Graph{
    private:
        int numVertice;
        int** adjMatrix;
        long double** tendMatrix;
    public:
        Graph(int numVertice);
        string set_adjMatrix();
        string set_tendMatrix();
        void display_matrix();
};



Graph::Graph(int numVertice){
    this->numVertice = numVertice;
    adjMatrix = new int*[numVertice];
    tendMatrix = new long double*[numVertice];

    for (int i = 0; i < numVertice; i++) {
        adjMatrix[i] = new int[numVertice];
        tendMatrix[i] = new long double[numVertice];
        for (int j = 0; j < numVertice; j++){
            adjMatrix[i][j] = 0;
            tendMatrix[i][j] = 0;
        }
    }
}

string Graph::set_adjMatrix(){
    for(int i=0; i<numVertice; i++){
        for(int j=0; j<numVertice; j++){
            int cost;
            cin >> cost;
            adjMatrix[i][j] = cost;
        }
    }
    return "finished\n\n";
}

string Graph::set_tendMatrix(){
    for(int i=0; i<numVertice; i++){
        for(int j=0; j<numVertice; j++){
            long double tend;
            cin >> tend;
            tend = abs(log(tend));
            tendMatrix[i][j] = tend;
        }
    }
    return "finished\n\n";
}

void Graph::display_matrix(){
    for(int i=0; i<numVertice; i++){
        for(int j=0; j<numVertice; j++)
            cout << adjMatrix[i][j] << " ";
        cout << "\n";
    }

    for(int i=0; i<numVertice; i++){
        for(int j=0; j<numVertice; j++)
            cout << tendMatrix[i][j] << " ";
        cout << "\n";
    }
}

#endif