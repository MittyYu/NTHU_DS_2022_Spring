#include <iostream> 
using namespace std;

void Swap1(int a, int b){
    int tmp = a;
    a = b;
    b = tmp;
}

void Swap2(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Swap3(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

int main(){
    int a = 1, b = 2, c = 3, d = 4;
    Swap1(a, b);
    cout << a << " " << b << " ";
    Swap2(&c, &d);
    cout << c << " " << d << " ";
    Swap3(a, b);
    cout << a << " " << b << " ";
    return 0;
}