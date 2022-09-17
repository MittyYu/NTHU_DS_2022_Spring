#include <iostream>
#include <string>
#include "function.h"
#include <utility>

using namespace std;

/*
In partial judge problem, you need to compile two .cpp files and a header file together.
For compile multiple .cpp files and .h headers, please refer to the following tutorial.
Chinese:
https://github.com/htchen/i2p-nthu/blob/master/%E7%A8%8B%E5%BC%8F%E8%A8%AD%E8%A8%88%E4%B8%80/%E5%A6%82%E4%BD%95compile%E5%A4%9A%E5%80%8B%E6%AA%94%E6%A1%88/%E5%A6%82%E4%BD%95%20compile%20%E5%A4%9A%E5%80%8B%E6%AA%94%E6%A1%88.md
English (terminal command):
https://stackoverflow.com/questions/3202136/using-g-to-compile-multiple-cpp-and-h-files

For Dev C++ or other IDE, please search for the Internet.
*/

enum class bullet
{
    SG,
    P,
    SB
};


BaseQueue < bullet > Q;
BaseStack < pair<int, char> > *S;

int main()
{
    int W, H, M;
    int col;
    string command;

    cin >> W >> H;
    cin >> M;

    InitialzeStage(W, H);

    for (int i=0; i<M; i++){
        cin >> command;
        if(command == "SHOOT"){
            cin >> col;
            ShootNormal(col, W);
        }
        else if(command == "SPECIAL"){
            cin >> col;
            ShootSpecial(col, W);
        }
        else if(command == "FRONT_ROW"){
            FrontRow(W);
        }
    }

    ShowResult(W);
    deleteStage();

    return 0;
}

void InitialzeStage(int W, int H){
    if(S == NULL){
        S = new BaseStack < pair<int, char> > [W];
    }
    
    for(int i = 1; i <= H; i++){
        for(int j = 0; j < W; j++){
            char tmp;
            cin >> tmp;
            if(tmp != '_')
                S[j].push(make_pair(i, tmp));
        }
    }
}

// Function for shooting a normal bullet
void ShootNormal(int col, int W){
    if(col < 0 || col >= W || S[col].empty()){
        return;
    }
    //cout << S[col].top().second << '\n';
    switch(S[col].top().second){
        case '5':{
            S[col].pop();
            int p = 0;
            for(int i = max(col-2, 0); i <= col+2 && i < W; i++)
                p = max(p, S[i].size()? S[i].top().first: 0);

            for(int i = max(col-2, 0); i <= col+2 && i < W; i++){
                for(int j = 1; j <= 3; j++){
                    S[i].push(make_pair(p+j, '1'));
                }
            }
            return;
        }
        case '4':
        case '3':
        case '2':
            Q.push(bullet(S[col].top().second - '2'));
    }
    S[col].pop();
    return;
}

// Function for shooting a special bullet
void ShootSpecial(int col, int W){
    if(Q.empty())   return;
    switch(Q.front()){
        case bullet::SG:
            // cout << "bullet SG\n";
            for(int i = max(col-2, 0); i <= col+2 && i <W; i++)
                ShootNormal(i, W);
            break;
        case bullet::P:
            // cout << "bullet P\n";
            for(int i = 0; i < 3; i++){
                ShootNormal(col, W);
            }
            break;
        case bullet::SB:
            // cout << "bullet SB\n";
            if(S[col].empty())  break;
            char t = S[col].top().second;
            while(S[col].size() && S[col].top().second == t )
                ShootNormal(col, W);
    }
    Q.pop();
    return;
}

void FrontRow(int W){
    if(S == NULL){
        S = new BaseStack < pair<int, char> > [W];
    }
    int level = 0;
    string result = "";

    for(int i = 0; i < W; i++){
        level = max(level, S[i].size()? S[i].top().first : 0);
    }

    if(!level) return;
    for(int i = 0; i < W; i++){
        if(S[i].top().first == level)
            result += S[i].top().second;
        else 
            result += '_';
        if(i < W-1)
            result += " ";
    }

    
    if(result == "") return;
    else cout << "FRONT_ROW, LEVEL:" << level << "\n" << result << "\n";
}

// Print the end result of the stage.
void ShowResult(int W){
    int l = 0;
    string result = "";
    for (int i = 0; i < W; i++)
        l = max(l, S[i].size()? S[i].top().first:0);
  
    for(int j = l; j > 0; j--){
        string subresult = "";
        for(int k = 0; k < W; k++){
            if(S[k].size() && S[k].top().first == j){
                subresult += S[k].top().second;
                S[k].pop();
            }
            else 
                subresult += "_";
            if(k < W-1)
                subresult += " ";
        }

        subresult += '\n';

        result = subresult + result;

    }
    cout << "END_RESULT:\n";
    cout << result;
           // cout << (itrs[i] != stks[i].end() && itrs[i]->first == j ? itrs[i]++->second : '_') << "\n "[i + 1 < W];
    return;
}

void deleteStage(){
    return;
}


template < class T >
BaseStack < T >::BaseStack(){
    _capacity = 10; 
    _stack = new T[_capacity];
    _top = 0;
}

template < class T >
BaseStack < T >::~BaseStack(){  delete[] _stack;}


// Check if the stack is empty
template < class T >
bool BaseStack < T >::empty(){
    return _top == 0;
}


// Return the size of the stack
template < class T >
int BaseStack < T >::size(){
    return _top;
}

// Return the top element
template < class T >
T& BaseStack < T >::top(){
    return _stack[_top-1];
}

// Insert a new element at top
template < class T >
void BaseStack < T >::push(const T& item){
    if(_top == _capacity){
        T* S_new = new T[_capacity*2];
        for(int i = 0; i < _capacity; i++) S_new[i] = _stack[i];
        delete[] _stack;
        _stack = S_new;
        _capacity *= 2;
    }
    _stack[_top++]=item;
}

// Delete one element from top
template < class T >
void BaseStack < T >::pop(){
    _top--;
    _capacity++;
}


template < class T >
BaseQueue < T >::BaseQueue(){
    _capacity = 10;
    _queue = new T[_capacity];
    _front = 0;
    _rear = 0;
}

template < class T >
BaseQueue < T >::~BaseQueue(){
    delete[] _queue;
}

template < class T >
bool BaseQueue < T > ::empty(){
    return _rear == _front;
}

// Return the size of the queue
template < class T >
int BaseQueue<T>::size(){
    // if(_rear > _front) return _rear - _front;
    // else return _capacity - (_front - _rear);
    return _rear - _front;
}

// Return the front element
template < class T >
T& BaseQueue<T>::front(){
    return _queue[_front];
}

// Insert a new element at rear
template < class T >
void BaseQueue<T>::push(const T& item){
    if(_rear == _capacity){
        T* Q_new = new T[2*_capacity];
        for(int i = 0; i < _rear - _front; i++) Q_new[i] = _queue[_front+i];
        delete[] _queue;
        _queue = Q_new;
        _rear -= _front;
        _front = 0;
        _capacity *= 2;
    }
    _queue[_rear]=item;
    // cout << "insert:" << _queue[_rear] << "\n";
    _rear++;
}

// Delete one element from front
template < class T >
void BaseQueue<T>::pop(){
    _front++;
}