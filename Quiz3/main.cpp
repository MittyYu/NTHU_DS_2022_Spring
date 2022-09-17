#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    std::priority_queue<int> pq;
    

    int n_room = 0;
    int vacant= 0;
    int cmdCnt = 0;
    string command;
    cin >> n_room;
    cin >> cmdCnt;
    vacant = n_room;

    for(int i = 0; i < n_room; i++){
        pq.push(i);
    }

    std::vector<int> result;

    for(int j=0;j < cmdCnt;j++){
        cin >> command;
        std::vector<int> tmp;
        if(command == "RESERVE"){
            int n;
            cin >> n;
            if(n <= pq.size()){
                while(n--){
                    int i = pq.top();
                    pq.pop();
                    result.push_back(i);
                    tmp.push_back(i);
                }
                cout << "RESERVE: reserve room ";
                for (unsigned i=0; i < tmp.size(); ++i)
                    if(i != tmp.size()-1)
                        std::cout << tmp[i] << ",";
                    else {
                        std::cout << tmp[i];
                    }
                std::cout << '\n';
            } else {
                cout <<"RESERVE: no vacant rooms\n";
            }
        }
        else if(command == "UNRESERVE"){
            int id;
            cin >> id;
            std::vector<int>::iterator position = std::find(result.begin(), result.end(), id);
            if (position != result.end()){ // == myVector.end() means the element was not found
                result.erase(position);
                pq.push(id);
                cout << "UNRESERVE: unreserved room " << id << "\n";
            }
            else{
                cout << "UNRESERVE: "<< id << " has not been reserved\n";
            }
            
        }
    }
    
    return 0;
}
