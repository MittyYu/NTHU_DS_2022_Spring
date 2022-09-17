# include <iostream>
# include <utility>
# include <string>
# include <algorithm>
# include <cstring>
# include <stack>
# include <queue>

using namespace std;

stack <char> *S;

int maxLayer(int left, int right){
    int ret = 0;
    for(int i = left; i < right; i++)
        ret = max(ret, S[i].size()? S[i].top(): 0);
    return ret;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int spot, inst;
        cin >> spot >> inst;
        S = new stack<char>[spot];

        while(inst --){
            int col, num;
            cin >> col >> num;
            char c;

            while(num--){
                cin >> c;
                S[col].push(c);
                // cout << S[col].top() << "\n";
            }

        }

        int layer = 0;
        cin >> layer;
        int preT = 1;
        int target;
        while(layer--){
            cin >> target;

            for(int col = 0; col < spot; col++){
                for(int i = preT; i < target; i++){
                    if(!S[col].empty())
                        S[col].pop();
                }
            }
            
            
            for(int col = 0; col < spot; col++){
                if(S[col].empty()){
                    cout << "0";
                }
                else cout << S[col].top();
                if(col != spot - 1) cout << " ";
            }

            cout << "\n";
            preT = target;            
        }
    }
}