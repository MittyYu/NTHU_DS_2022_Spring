#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

template <class T>
static bool compare(vector<T> a, vector<T> b)
{
    if (a.empty() && b.empty()) {
        return true;
    }
    if (a.size() != b.size())
    {
        return false;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    return (a == b);
}


class emo {
public:
    emo() {
        num = 0;
    }
    void input(string e) {
        emotion.push_back(e);
        num += 1;
    }
    string get(int id) {
        if (emotion.empty()) {
            return "empty";
        }
        else {
            return emotion[id];
        }
    }
    int size() {
        return num;
    }
private:
    vector<string> emotion;
    int num;
};

int main()
{
    int a1, n1, a2, n2;
    cin >> a1 >> n1;
    
    vector<emo> person1(a1 + 1);
    for (int i = 0; i < n1; i++) {
        int t;
        string e;
        cin >> t >> e;
        person1[t].input(e);
    }

    cin >> a2 >> n2;
    vector<emo> person2(a2 + 1);
    for (int i = 0; i < n2; i++) {
        int t;
        string e;
        cin >> t >> e;
        person2[t].input(e);
    }

    int age = min(a1, a2);
    int total = 0;
    vector<int> match;

    vector<string> p1, p2;
    for (int i = 0; i < age + 1; i++) {
        int size1 = person1[i].size();
        if(size1 != 0){
            for (int j = 0; j < size1; j++) {
                p1.push_back(person1[i].get(j));
            }  
        }
        int size2 = person2[i].size();
        if (size2 != 0) {
            for (int j = 0; j < size2; j++) {
                p2.push_back(person2[i].get(j));
            }
        }
        if (compare(p1, p2) && size1 == 0 && size2 == 0) {
            match.push_back(i);
            total += 1;
        }
        //  || size1 == 0 && size2 == 0
        else if (compare(p1, p2) && !(size1 == 0 && size2 == 0)) {
            match.push_back(i);
            total += 1;
        }
    }
    if (match.empty()) {
        cout << 0 << "\n";
    }
    else {
        cout << total << "\n";
        cout << match[0];
        for (int i = 1; i < match.size(); i++) {
            cout << " " << match[i];
        }
        cout << "\n";
    }
    
}
