#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;


typedef struct event{
    int age;
    string e;
}event;

typedef struct soulmate{
    int age;
    int n;  // events
    event* events;
}soulmate;

bool operator>(event A, event B){
    return A.age > B.age;
}

bool operator>=(event A, event B){
    return A.age >= B.age;
}

template < class T >
void mySort(T arr[], int l, int r){
    if (l >= r) return;
    else {
        int mid = (l + r)/2;
        mySort(arr, l, mid);
        mySort(arr, mid + 1, r);

        T* tmp_arr = new T[r-l+1];
        int idx_l = l, idx_r = mid + 1, i = 0;
        while(!(idx_l > mid || idx_r > r || i > r-l+1)) {
            if (arr[idx_l] >= arr[idx_r])
				tmp_arr[i++] = arr[idx_r++];
            else if (arr[idx_r] > arr[idx_l]) 
				tmp_arr[i++] = arr[idx_l++];
        }

        while(idx_l > mid && idx_r <= r) 
			tmp_arr[i++] = arr[idx_r++];
		
        while(idx_r > r && idx_l <= mid) 
			tmp_arr[i++] = arr[idx_l++];

        for (int i = 0 ; i < r - l + 1 ; i++) 
			arr[l + i] = tmp_arr[i];
    }
}

int main(){
    soulmate soulmate1;
    soulmate soulmate2;

    set<int> idx;

    cin >> soulmate1.age >> soulmate1.n;
    if(soulmate1.n !=0){
        soulmate1.events = new event[soulmate1.n];
        for(int i=0; i< soulmate1.n; i++){
            cin >> soulmate1.events[i].age >> soulmate1.events[i].e;
            idx.insert(soulmate1.events[i].age);
        }
        mySort<event>(soulmate1.events, 0, soulmate1.n-1);

    }

    cin >> soulmate2.age >> soulmate2.n;
    if(soulmate2.n != 0){
        soulmate2.events = new event[soulmate2.n];
        for(int i=0; i< soulmate2.n; i++){
            cin >> soulmate2.events[i].age >> soulmate2.events[i].e;
            idx.insert(soulmate2.events[i].age);
        }
        mySort<event>(soulmate2.events, 0, soulmate2.n-1);

    }
    
    int max_age = soulmate1.age > soulmate2.age? soulmate1.age:soulmate2.age;

    int map_1[4] = {0, 0, 0, 0};
    int map_2[4] = {0, 0, 0, 0};
    
    set<int>::iterator itr;
   
    int last_1 = 0; // last_idx
    int last_2 = 0;

    vector<int> ans;

   //{"Angry", "Fearful", "Happy", "Sad"}
    for (int i = 0; i <= max_age; itr++)
    {
        //cout << "Time: " << *itr << "\n";
        for(int j=last_1 +1; soulmate1.events[j].age == *itr; j++){
            string tmp = soulmate1.events[j].e;
            cout << tmp << "\n";
            if(tmp == "Angry"){
                map_1[0]++;
            }else if(tmp == "Fearful"){
                map_1[1]++;
            }else if(tmp == "Happy"){
                map_1[2]++;
            }else if(tmp == "Sad"){
                map_1[3]++;
            }
            last_1=j;
        }

        //cout << "map_1:\n";
        //cout << map_1[0] << " "<< map_1[1] << " "<< map_1[2] << " "<< map_1[3] << "\n";

        for(int j=last_2 +1; soulmate2.events[j].age == *itr; j++){
            
            string tmp = soulmate2.events[j].e;
            
            if(tmp == "Angry"){
                map_2[0]++;
            }else if(tmp == "Fearful"){
                map_2[1]++;
            }else if(tmp == "Happy"){
                map_2[2]++;
            }else if(tmp == "Sad"){
                map_2[3]++;
            }
            last_2=j;
        }

        //cout << "map_2:\n";
        //cout << map_2[0] << " "<< map_2[1] << " "<< map_2[2] << " "<< map_2[3] << "\n";

        if(map_1[0] == map_2[0] && map_1[1] == map_2[1] && map_1[2] == map_2[2] && map_1[3] == map_2[3]){
            ans.push_back(*itr);
        }
            
    }

    cout << ans.size() << "\n";
    int ans_0 = ans[0];
    cout << ans_0;
    for (auto it = ++ans.begin(); it != ans.end(); ++it) {
        cout << " " << *it;
    }
    cout << "\n";
    return 0;
}