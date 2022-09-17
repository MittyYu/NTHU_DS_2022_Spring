#include <iostream>
#include <vector>
#include "function.h"
#include <sstream>
#include <cmath>

using namespace std;

// In the system, a map will be represented as a graph, 
// nodes: the places listed by the user
// edges: the accesses between every two places. 
// every node is adjacent to each other. 

// Between every two nodes exists two edges with opposite directions. 
// There are two kinds of graphs. The first graph is about the travel time. 
// In this graph, the edge weights are the time consumption of people traveling from one place to another. 
// The second graph is about the tourist flow. 
// In real life, tourist flow records the amount of people traveling from one place to another. 
// Here we take tourist flow as the tendency of people traveling to different places. 
// In this graph, the edge weights are the tendency values, 
// where higher values stand for the higher tendency that people to travel from one place to another.


int main(){
    // spend less time traveling around tourist attractions.
    int placeCnt = 0;
    string command, ori;    //ori: original
    cin >> placeCnt;

    int idx;
    string plc_name;
    int plc_ps; // preference score
    vector<Node> Node_list;

    Graph Graph(placeCnt);

    for(int i = 0; i < placeCnt; i++){
        cin >> idx >> plc_name >> plc_ps;
        Node_list.push_back(Node(idx, plc_name, plc_ps, false));
    }

    Graph.set_adjMatrix();
    Graph.set_tendMatrix();

    while(true){
        cin >> command;
        if(command == "SET_ORIGIN"){
            string place;
            cin >> place;
            vector<Node>::iterator it;
            it = find(Node_list.begin(), Node_list.end(), place);
            if(it->get_status()){
                cout << "Fail to reset the origin\n";
            }
            else{
                cout << place << " is the new origin\n";
                ori = place;
            }
            
        }
        else if(command == "MARK_STATE"){
            cin >> command; // to close or open            
            bool status = command.front() == 'C';

            getline(cin, command);
            stringstream ss(command);
            while (ss >> command){
                vector<Node>::iterator it;
                it = find(Node_list.begin(), Node_list.end(), command);
                if(it->get_status() != status && (it->get_name() != ori || !status))
                    it->set_status(status);
                else cout << "Failed to " << (status ? "close " : "open ") << command << '\n';
                // cout << command << " Closed? " << it->get_status() << "\n";
            }
        }
        else if(command == "OPTIMAL_PATH"){
            cin >> command;
            
        }
        else if(command == "LIMITED_PATH"){
            cout << "Limit_path";
        }
        else if(command == "END_OF_INSTRUCTION"){
            cout << "Stop receiving instructions\n";
            break;
        }
    }



    return 0;
}

Node::Node(int idx, std::string name, int ps, bool closed):idx(idx), name(name), ps(ps), closed(false){}