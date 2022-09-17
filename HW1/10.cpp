#include <iostream>
#include <string>
#include "function.h"

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
BaseStack < char > *S;
// BaseQueu


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


// void show_stack(int H, int W){
//     for(int i = 0; i < W; i++){
//         for(int j = 0; j < H; j++)
//             cout << S[i]._stack[j];
//         cout << '\n';
//     }
// }

// Loading the stage
void InitialzeStage(int W, int H){
    if(S == NULL){
        S = new BaseStack < char > [W];
    }
    
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            char tmp;
            cin >> tmp;
            S[j].push(tmp);
            // cout << Q[i].back() << "\n";    
        }
        // cout << "next line\n";
    }
    // cout >> Q;
    // show_stack(H, W);
}

// Function for shooting a normal bullet
void ShootNormal(int col, int W){
    if(col < 0 || col >= W || S[col].empty()){
        return;
    }
    // cout << S[col].top() << '\n';
    switch(S[col].top()){
        case '5':{
            S[col].pop();
            int p = 0;
            for(int i = max(col-2, 0); i <= col+2 && i < W; i++)
                p = max(p, S[i].size());
            
            //cout << "p: " << p << "\n";

            for(int i = max(col-2, 0); i <= col+2 && i < W; i++){
                while(S[i].size() < p){
                    S[i].push('0');
                    // cout << "at " << i << " push a 0\n";
                }
            }

            for(int i = max(col-2, 0); i <= col+2 && i < W; i++){
                for(int j = 0; j < 3; j++){
                    S[i].push('1');
                }
                // cout << i << ": size --> " << S[i].size() << "\n";
            }

            return;

        }
        case '4':
        case '3':
        case '2':
            Q.push(bullet(S[col].top() - '2'));
    }
    S[col].pop();
    // for(int j = 0; j < S[col].size(); j++)
    //     cout << S[col]._stack[j];
    // cout << '\n';

    // cout << Q.front() << '\n';
    
    return;
}

// Function for shooting a special bullet
void ShootSpecial(int col, int W){
    // Check the enemy first (#1, #2, #3, #4, #5), 
    // then match the effects.

    if(Q.empty())   return;
    switch(Q.front()){
        case bullet::SG:
            // cout << "bullet SG\n";
            for(int i = max(col-2, 0); i <= col+2 && i <W; i++)
                if(S[col].top() != '0') ShootNormal(i, W);
                else{
                    while(S[col].top() == '0')
                        ShootNormal(i, W);
                }
            break;
        case bullet::P:
            // cout << "bullet P\n";
            for(int i = 0; i < 3; i++){
                if(S[col].top() == '0'){
                    i -= 1;
                    continue;
                }
                else ShootNormal(col, W);
            }
            break;
        case bullet::SB:
            // cout << "bullet SB\n";
            if(S[col].empty())  break;
            char t = S[col].top();
            while(S[col].size() && (S[col].top() == t || S[col].top() == '0'))
                ShootNormal(col, W);
    }
    Q.pop();
    // for(int j = 0; j < S[col].size(); j++)
    //     cout << S[col]._stack[j];
    // cout << '\n';
    return;
}

// Function that show the front row of the current stage
// Here, as the description on the OJ, you need to find the maximum level that contains any enemy.
// print the enemy types at that level for each column.
// print a underline "_" for a column that does not have a enemy at that level.
void FrontRow(int W){
    if(S == NULL){
        S = new BaseStack <char> [W];
    }
    int level = 0;
    string result = "";

    for(int i = 0; i < W; i++){
        level = max(level, S[i].size());
    }

    // cout << level<< "\n";

    for(int i = 0; i < W; i++){
        if(S[i].size() < level || (S[i].size() == level && S[i].top() == '0'))
            result += '_';
        else 
            result += S[i].top();
        if(i < W-1)
            result += " ";
    }

    // for(int i = 0; i < W; i++){
    //     if(S[i].empty()){
    //         continue;
    //     }
    //     else{
    //         result = "";
    //         for(int j = 0; j < W; j++){
    //             if(S[i].top() == 0){
    //                 result += '_';
    //             }
    //             else{
    //                 result += S[i].top();
    //             }
    //         }
            
    //         level = i+1;
    //     }
    // }
    
    if(result == "") cout << "0\n";
    else cout << "FRONT_ROW, LEVEL:" << level << "\n" << result << "\n";
}

// Print the end result of the stage.
void ShowResult(int W){
    int l = 0;
    string result = "";
    for (int i = 0; i < W; i++)
        l = max(l, S[i].size());
    // cout << "END_RESULT:\n";
    // if (!l)
    //     return;
    // for(int j = 0; j <l; j++){
    //     for(int i = 0; i < W; i++){
    //         if(S[i].size() < l-i || S[i].top() == '0'){
    //             result += "_";
    //         }
    //         else{
    //             result += S[i].top();
    //         }
    //     }
    //     result += "\n";
    // }
    // cout << l << "\n";
    for(int i = 0; i < l; i++){

        if(S == NULL)
            S = new BaseStack <char> [W];
        
        int level = 0;
        string subresult = "";

        for(int i = 0; i < W; i++){
            level = max(level, S[i].size());
        }
        for(int i = 0; i < W; i++){
            if(S[i].size() < level || (S[i].size() == level && S[i].top() == '0'))
                subresult += '_';
            else 
                subresult += S[i].top();
            if(i < W-1)
                subresult += " ";
        }

        subresult += '\n';

        result = subresult + result;
        for(int row = 0; row < W; row++){
            if(S[row].size() == l - i)
                S[row].pop();
            // cout << S[row].top() << "\n";
        }
        // show_stack(l, W);
    }
    cout << "END_RESULT:\n";
    cout << result;
           // cout << (itrs[i] != stks[i].end() && itrs[i]->first == j ? itrs[i]++->second : '_') << "\n "[i + 1 < W];
    return;
}

// free the memory that allocated in the program.
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