#include <iostream>
#include <string>
#include "function.h"

using namespace std;


enum class bullet
{
    SG,
    P,
    SB
};


BaseQueue < bullet > Q;
BaseStack < char > *S;

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


// Loading the stage
void InitialzeStage(int W, int H){
    if(S == NULL){
        S = new BaseStack < char > [W];
    }

    char tmp;    
    for(int row = 1; row <= H; row++){
        for(int col = 0; col < W; col++){
            cin >> tmp;
            if(tmp != '_')
                S[col].push(tmp);
        }
    }
}

// Function for shooting a normal bullet
void ShootNormal(int col, int W){
    if(col < 0 || col >= W || S[col].empty())
        return;

    char target = S[col].top();
    

    while (!S[col].empty() && S[col].top() == '_')
        S[col].pop();

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
    // Check the enemy first (#1, #2, #3, #4, #5), 
    // then match the effects.

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
    // for(int j = 0; j < S[col].size(); j++)
    //     cout << S[col]._stack[j];
    // cout << '\n';
    return;
}

// Function that show the front row of the current stage
// Here, as the description on the OJ, you need to find the maximum level that contains any enemy.
// print the enemy types at that level for each column.
// print a underline "_" for a column that does not have a enemy at that level.
void FrontRow(int W) {
	int level = 0;
    for(int i = 0; i < W; i++){
        level = max(level, S[i].size()? S[i].top().first : 0);
    }
	
    cout << "FRONT_ROW, LEVEL:" << level << '\n';
    if (level) {
        for (int i = 0; i < W; i++) {
            if (S[i].size() == level)
                cout << S[i].top().second;
            else
                cout << '_';
            if (i != W - 1) cout << ' ';
        }
        cout << '\n';
    }
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
        subresult += "\n";
        result = subresult + result;

    }
    cout << "END_RESULT:\n";
    cout << result;
    return;
}


// free the memory that allocated in the program.
void deleteStage(){
    delete[] S;
}


template < class T >
BaseStack < T >::BaseStack(){
    _capacity = 1000; 
    _stack = new T[1000];
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
}


template < class T >
BaseQueue < T >::BaseQueue(){
    _capacity = 1000;
    _queue = new T[1000];
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