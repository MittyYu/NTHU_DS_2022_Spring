#include <iostream>
#include <string>
#include <cstring>
#include "function.h"

using namespace std;

enum class bullet{
    SG,
    P,
    SB
};

BaseStack < char > *S;
BaseQueue < bullet > Q;

void InitialzeStage(int W, int H) {
    if(S == NULL){
        S = new BaseStack < char > [W];
    }

    char c;
    for (int row = 0; row < H; row++) {
        for (int col = 0; col < W; col++) {
            cin >> c;
            S[col].push(c);
        }
    }

}

void ShootNormal(int col, int W) {
    if (col >= W || col < 0 || S[col].empty())
        return;

    char target = S[col].top();
    S[col].pop();

    while (!S[col].empty() && S[col].top() == '_')
        S[col].pop();
    
    switch (target) {
        case '5': {
            int level = 0;
            for (int i = max(col - 2, 0); i <= col+2 && i < W; i++)
                level = max(level, S[i].size());

            for (int i = max(col - 2, 0); i <= col+2 && i < W; i++) {
                while (S[i].size() < level)
                    S[i].push('_');
                S[i].push('1');
                S[i].push('1');
                S[i].push('1');
            }
            break;
        } 
        case '2':
        {
            Q.push(bullet::SG); 
            break;
        }
        case '3':
        {
            Q.push(bullet::P); 
            break;
        }
        case '4': 
        {
            Q.push(bullet::SB); 
            break;
        }
    }
}

void ShootSpecial(int col, int W) {
    if (col < 0 || col >= W || Q.empty())
        return;
        
    bullet b = Q.front();
    
    switch(b){
        case bullet::SG:
        {
            for (int i = max(col-2, 0); i <= col+2 && i <W; i++)
                ShootNormal(i, W);
            break;
        }
        case bullet::P:
        {
            for(int i = 0; i < 3; i++)
                ShootNormal(col, W);
            break;
        }
        case bullet::SB:
        {
            if(S[col].empty())  break;
            char t = S[col].top();
            while (!S[col].empty() && S[col].top() == t)
                ShootNormal(col, W);
            break;
        }
    }

    Q.pop();
}

void FrontRow(int W) {
    int level = 0;
    for (int i = 0; i < W; i++)
        level = max(level, S[i].size());
    
    cout << "FRONT_ROW, LEVEL:" << level << '\n';
    if (level) {
        for (int i = 0; i < W; i++) {
            if (S[i].size() == level)
                cout << S[i].top();
            else
                cout << '_';
            if (i < W - 1)
                cout << ' ';
        }
        cout << '\n';
    }
}

void ShowResult(int W) {
    cout << "END_RESULT:\n";

    int level = 0;
    for (int i = 0; i < W; i++)
        level = max(level, S[i].size());

    if (level) {
        BaseStack<char> *tmp = new BaseStack<char>[W];
        for (int i = 0; i < W; i++) {
            while (!S[i].empty()) {
                tmp[i].push(S[i].top());
                S[i].pop();
            }
        }
        
        for (int l = 1; l <= level; l++) {
            for (int i = 0; i < W; i++) {
                char ch = !tmp[i].empty() ? tmp[i].top() : '_';
                tmp[i].pop();
                cout << ch;
                if (i != W - 1)
                    cout << ' ';
            }
            cout << '\n';
        }

        delete[] tmp;
    }
}

void deleteStage() { delete[] S; }


template <class T>
BaseStack<T>::BaseStack() {
    _stack = new T[1000];
    _top = -1;
    _capacity = 1000;
}

template<class T>
BaseStack<T>::~BaseStack() { delete[] _stack; }

template <class T>
bool BaseStack<T>::empty() { return _top == -1; }

template <class T>
int BaseStack<T>::size() { return _top + 1; }

template <class T>
T& BaseStack<T>::top() {
    return _stack[_top];
}

template <class T>
void BaseStack<T>::push(const T& item) {
    // resize; changing '*2' into '+1000' doesn't affact
    if (size() >= _capacity) {
        int Cap_new = _capacity <= 100000 ? _capacity * 2 : _capacity + 1000;
        T *S_new = new T[Cap_new];
        memcpy(S_new, _stack, _capacity * sizeof(T));
        
        delete[] _stack;
        _stack = S_new;
        _capacity = Cap_new;
    }
    _stack[++_top] = item;
}

template <class T>
void BaseStack<T>::pop() {
    _top--;
}

template <class T>
BaseQueue<T>::BaseQueue() {
    _queue = new T[1000];
    _front = _rear = -1;
    _capacity = 1000;
}

template <class T>
BaseQueue<T>::~BaseQueue() { delete[] _queue; }

template <class T>
bool BaseQueue<T>::empty() { return size() == 0; }

template <class T>
int BaseQueue<T>::size() {
    return (_rear < _front) ? (_rear + _capacity - _front) : (_rear - _front);
}

template <class T>
T& BaseQueue<T>::front() { return _queue[(_front + 1) % _capacity]; }

template <class T>
void BaseQueue<T>::push(const T& item) {
    if (size() >= _capacity) {
        int Cap_new = _capacity <= 100000 ? _capacity * 2 : _capacity + 1000;
        T* Q_new = new T[Cap_new];
        int Size = size(), index = _front + 1;
        for (int i = 0; i < Size; i++) {
            Q_new[i] = _queue[index];
            index = index == _capacity ? 0 : index + 1;
        }

        delete[] _queue;
        _queue = Q_new;
        _capacity = Cap_new;
    }

    if ((_rear + 1) % _capacity != _front) {
        _rear = (_rear + 1) % _capacity;
        _queue[_rear] = item;
    }
}

template <class T>
void BaseQueue<T>::pop() {
    if (!empty())
        _front = (_front + 1) % _capacity;
}





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
