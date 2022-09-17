#include <bits/stdc++.h>
using namespace std;

//Struct define
typedef pair<int, int> p;
typedef priority_queue<p, vector<p>, greater<p> > pq;

typedef struct Place
{
    bool open;
    string name;
    int PS;
}Place;

typedef struct Edge
{
    int time;
    float flow;
}Edge;

typedef struct Route
{
    vector<int> route;
    int time;
    float flow;
    int PS;
}Route;

//Global variable
map<string, int> nti;
Place *place_list;
Edge adjmatirx[100][100];
int origin, time_flow;
int n = 0, target;
Route min_route{vector<int>{}, INT_MAX, 200, 0};

//Operator overload
bool operator>(const Route& lhs, const Route& rhs){

    if (time_flow == 0) {
        if (lhs.time == rhs.time && lhs.PS == rhs.PS){
            int min_size = min(lhs.route.size(), rhs.route.size());
            for (int i = 0 ; i < min_size ; i++)
                if (lhs.route[i] != rhs.route[i]) return lhs.route[i] > rhs.route[i];
        }
        if (lhs.time == rhs.time) return lhs.PS < rhs.PS;
        return lhs.time > rhs.time;
    }

    if (lhs.flow == rhs.flow && lhs.PS == rhs.PS){
            int min_size = min(lhs.route.size(), rhs.route.size());
            for (int i = 0 ; i < min_size ; i++)
                if (lhs.route[i] != rhs.route[i]) return lhs.route[i] > rhs.route[i];
    }
    if (lhs.flow == rhs.flow) return lhs.PS < rhs.PS;
    return lhs.flow > rhs.flow;
}

ostream& operator<<(ostream& os, Route& ro){
    os << ro.time << " " << ro.PS << " ";
    for (vector<int>::iterator it = ro.route.begin() ; it != ro.route.end() ; it++)
        os << *it << " ";
    return os;
}


void dfs(int index, Route value, set<int> pass, int limit){
    if (index == target){
        if (min_route > value){
            min_route = value;
        }
        return;
    }
    if (limit == 0) return;
    for (int i = 0 ; i < n ; i++){
        if (adjmatirx[index][i].time != 0 && place_list[i].open && !pass.count(i) ){
            Route nv = value;
            nv.flow += adjmatirx[index][i].flow;
            nv.PS += place_list[i].PS;
            nv.route.push_back(i);
            nv.time += adjmatirx[index][i].time;
            pass.insert(i);
            if (min_route > nv)
                dfs(i, nv, pass, limit - 1);
            pass.erase(i);
        }
    }
}


int main(void) {

    
    cin >> n;
    place_list = new Place[n];
    //adjmatirx = new Edge[100][100];
    for (int i = 0 ; i < n ; i++) place_list[i].open = false;

    //initial place_list
    for (int i = 0 ; i < n ; i++) {
        int index, ps;
        string name;
        cin >> index >> name >> ps;
        nti.insert(pair<string, int>(name, index));
        place_list[index].name = name;
        place_list[index].PS = ps;
        place_list[index].open = true;
    }

    //initial adj matrix
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < n ; j++)
            cin >> adjmatirx[i][j].time;

    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < n ; j++) {
            float flow;
            cin >> flow;
            adjmatirx[i][j].flow = -log2(flow);
        }

    string command;
    while(cin >> command){
        if (command == "SET_ORIGIN"){
            string name;
            cin >> name;
            int index = nti[name];
            if (!place_list[index].open) cout << "Fail to reset the origin" << endl;
            else {
                cout << name << " is the new origin" << endl;
                origin = index;
            }
        }

        else if (command == "MARK_STATE"){
            string status, name;
            cin >> status;
            bool open = (status == "OPEN") ? true : false;
            
            while(getchar() != '\n'){
                cin >> name;
                int index = nti[name];
                if (!(place_list[index].open != open && (origin != index || open != false)))
                    cout << "Failed to " << (open ? "open " : "close ") << command << '\n';
                else place_list[index].open = open;
            }
        }
        
        else if (command == "OPTIMAL_PATH"){
            string name, consider;
            cin >> name >> consider;
            target = nti[name];

            if (origin == target){
                cout << "Optimal " << consider << " : " << name << endl;
            }
            else if (!place_list[target].open){
                cout << "No such optimal path to " << name << endl;
            }
            else{
                time_flow = (consider == "TIME") ? 0: 1;
                min_route.flow = adjmatirx[origin][target].flow;
                min_route.time = adjmatirx[origin][target].time;
                min_route.PS = place_list[target].PS;
                min_route.route = {target};
                dfs(origin, {{}, 0, 0, 0}, {}, 150);

                vector<int>::iterator it = min_route.route.begin();

                cout << "Optimal " << consider << " : " << place_list[origin].name << " -> ";
                for(it ; it != min_route.route.end() - 1 ; it++)
                    cout << place_list[*it].name << " -> ";
                cout << place_list[*it].name << endl;
            }
        }
        else if (command == "LIMITED_PATH"){
            string name, consider;
            int limit;
            cin >> name >> consider >> limit;
            target = nti[name];

            if (origin == target)
                cout << "Limited " << consider << " : " << name << endl;
            else if (!place_list[target].open)
                cout << "No such limited path to " << name << endl;
            else{
                time_flow = (consider == "TIME") ? 0: 1;
                min_route.flow = adjmatirx[origin][target].flow;
                min_route.time = adjmatirx[origin][target].time;
                min_route.PS = place_list[target].PS;
                min_route.route = {target};
                dfs(origin, {{}, 0, 0, 0}, {}, limit - 1);

                if (min_route.route.size() == 0) cout << "No such limited path to " << name << endl;
                else{
                    vector<int>::iterator it = min_route.route.begin();
                    cout << "Limited " << consider << " : " << place_list[origin].name << " -> ";
                    for(it ; it != min_route.route.end() - 1 ; it++)
                        cout << place_list[*it].name << " -> ";
                    cout << place_list[*it].name << endl;
                }
            }
        }
        else if(command == "END_OF_INSTRUCTION"){
            cout << "Stop receiving instructions" << endl;
            break;
        }
    }

    return 0;
}