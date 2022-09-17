#include <iostream>
#include "function.h"
#include <string>

using namespace std;
typedef struct people_active{
    int p;
    int t;
}people_active;


bool operator>(people_active A, people_active B){
    return A.t > B.t;
}

bool operator>=(people_active A, people_active B){
    return A.t >= B.t;
}

int *A;
people_active *p_cnt;
string *S;
    

template < class T >
void mySort(T arr[], int l, int r){
    if (l >= r) return;
    else {
        int mid = (l + r)/2;
        mySort(arr, l, mid);
        mySort(arr, mid + 1, r);
        T* tmp = (T*)malloc((r-l+1) * sizeof(T));
        int idl = l, idr = mid + 1, i = 0;
        while(1) {
            if (idl > mid || idr > r || i > r-l+1) break;
            if (arr[idl] >= arr[idr]) tmp[i++] = arr[idr++];
            else if (arr[idr] > arr[idl]) tmp[i++] = arr[idl++];
        }
        while(idl > mid && idr <= r) tmp[i++] = arr[idr++];
        while(idr > r && idl <= mid) tmp[i++] = arr[idl++];

        for (int i = 0 ; i < r - l + 1 ; i++) arr[l + i] = tmp[i];
    }
}

int main(void) {
    solve();
    return 0;
}

// TODO: Implement the function to read iput, process data, and output answers.

void solve() {
    int n, m, ar, le, p;
    cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> p >> ar >> le >> S[i];
        A[i] = ar;
        p_cnt[2 * i] = {p, ar};
        p_cnt[2 * i + 1] = {-p, le};
    }

    mySort<string>(S, 0, n - 1);
    mySort<int>(A, 0, n - 1);
    mySort<people_active>(p_cnt, 0, 2*n - 1);


    int max_t, max_peo = 0;
    int ti = p_cnt[0].t;
    int nup = p_cnt[0].p;
    for (int i = 1 ; i < 2*n ; i++) {
        if(ti != p_cnt[i].t){
            if(nup > max_peo) {
                max_peo = nup;
                max_t = ti;
            }
            ti = p_cnt[i].t;
        }
        nup += p_cnt[i].p;
    }

    cin >> m;
    string instrction;
    for (int i = 0 ; i < m ; i ++) {
        cin >> instrction;
        if(instrction == "TIME_ARRIVE") {
            int k;
            cin >> k;
            cout << A[k - 1] << endl;
        }
        else if(instrction == "TRAFFIC_AT") {
            int t;
            cin >> t;
            if (t < p_cnt[0].t) cout << 0 << endl;
            else if (t >= p_cnt[2*n - 1].t) cout << 0 << endl;
            else {
                int ti = p_cnt[0].t;
                int nup = p_cnt[0].p;
                for (int i = 1 ; i < 2*n ; i++) {
                    if(ti != p_cnt[i].t){
                        if(t <= ti) {
                            cout << nup << endl;
                            break;
                        }
                        ti = p_cnt[i].t;
                    }
                    nup += p_cnt[i].p;
                }
            }
        }
        else if(instrction == "MAX_TRAFFIC") {
            cout << max_t << " " << max_peo << endl;
        }
        else if(instrction == "STORE_LIST") {
            string name = S[0];
            cout << name;
            for (int i = 1 ; i < n ; i++) {
                if(name != S[i]) {
                    cout << " " << S[i];
                    name = S[i];
                }
            }
            cout << endl;
        }
    }
}