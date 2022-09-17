/*
In partial judge problem, you need to compile two .cpp files and a header file together.
For compile multiple .cpp files and .h headers, please refer to the following tutorial.
Chinese:
https://github.com/htchen/i2p-nthu/blob/master/%E7%A8%8B%E5%BC%8F%E8%A8%AD%E8%A8%88%E4%B8%80/%E5%A6%82%E4%BD%95compile%E5%A4%9A%E5%80%8B%E6%AA%94%E6%A1%88/%E5%A6%82%E4%BD%95%20compile%20%E5%A4%9A%E5%80%8B%E6%AA%94%E6%A1%88.md
English (terminal command):
https://stackoverflow.com/questions/3202136/using-g-to-compile-multiple-cpp-and-h-files

For Dev C++ or other IDE, please search on the Internet.
*/

#include <iostream>
#include "function.h"
#include <string>
// #include <algorithm>
using namespace std;

typedef struct active_people{
	int p;
	int t;	// time
}active_people;

bool operator>(active_people A, active_people B){
    return A.t > B.t;
}

bool operator>=(active_people A, active_people B){
    return A.t >= B.t;
}


// int *P;
int *A;
active_people *people_cnt;
string *S;

void qsort (void* base, size_t num, size_t size, int (*compar)(const void*, const void*))
{
    std::cout << "Please don't cheat.\n";
}

template <class RandomAccessIterator>
void sort (RandomAccessIterator first, RandomAccessIterator last)
{
    std::cout << "Please don't cheat.\n";
}

template <class RandomAccessIterator, class Compare>
void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    std::cout << "Please don't cheat.\n";
}
// TODO: Implement the sorting algorithm

unsigned int n;
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

void solve(){
	
	cin >> n;
	
	// P = new int[n];
	A = new int[n];
	S = new string[n];
	people_cnt = new active_people[2*n];

	int flag = 0;

	
	for(int i = 0 ; i < n ; i++){
		int p, a, l;
		string str;
		cin >> p >> a >> l >> S[i];
		// P[i] = p;
		A[i] = a;
		people_cnt[2*i] = {p, a};
		people_cnt[2*i+1] = {-p, l};
	}
	
	mySort<int>(A, 0, n-1);
	mySort<string>(S, 0, n-1);
	mySort<active_people>(people_cnt, 0, 2*n-1);

	unsigned int m;
	cin >> m;
	string command;
	
	while(m--){
		cin >> command;
		if(command == "TIME_ARRIVE")
		{
			unsigned int k;
			cin >> k;
            cout << A[k-1] << "\n";
        }
		else if(command == "TRAFFIC_AT") 
		{
			unsigned int t;
			cin >> t;

			if (t < people_cnt[0].t || t >= people_cnt[2*n - 1].t){
				cout << 0 << "\n";
			}
            else {
                int t_0 = people_cnt[0].t;
                int n_p = people_cnt[0].p;	// number of people
                for (int i = 1 ; i < 2*n ; i++) {
                    if(t_0 != people_cnt[i].t){
                        if(t <= t_0) {
                            cout << n_p << "\n";
                            break;
                        }
                        t_0 = people_cnt[i].t;
                    }
                    n_p += people_cnt[i].p;
                }
            }
			
		} 
		else if(command == "MAX_TRAFFIC")
		{
			int m_t, m_p = 0;
			if(flag){
				cout << m_t << " " << m_p << "\n";
				continue;
			}

			int t_0 = people_cnt[0].t;
			int n_p = people_cnt[0].p;
			for (int i = 1 ; i < 2*n ; i++) {
				if(t_0 != people_cnt[i].t){
					if(n_p > m_p) {
						m_p = n_p;
						m_t = t_0;
					}
					t_0 = people_cnt[i].t;
				}
				n_p += people_cnt[i].p;
			}
			flag = 1;
			cout << m_t << " " << m_p << "\n";
		}
		else if(command == "STORE_LIST")
		{
			string s_0 = S[0];
            cout << s_0;
            for (int i = 1 ; i < n ; i++)
				if(s_0 != S[i]) {
                    cout << " " << S[i];
                    s_0 = S[i];
                }
            cout << "\n";
		}
	}

    // delete[] P;
    delete[] A;
    delete[] S; 
}

int main() {

    solve();

    return 0;
}

