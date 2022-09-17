#include <iostream>
#include <string>
#include "function.h"

using namespace std;
// main function
int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int t;
    cin >> t;

    while(t--)
    {
        string operation;
        cin >> operation;

        if(operation == "PLANT"){
            long long x,y;
            int withFence;
            cin >> x >> y >> withFence;
            plant(x,y,withFence);
        }
        else if(operation == "THIEF"){
            long long x,y;
            cin >> x >> y;
            thief(x,y);
        }
        else if(operation == "SUPER_THIEF"){
            long long x,y;
            cin >> x >> y;
            superThief(x,y);
        }
        else if(operation == "DISPLAY"){
            display();
        }
        else{
            cout << "error" << "\n";
        }
    }
    return 0;
}



# define l 0
# define equal 1
# define r 2


template <class T> 
Node<T>::Node(T x, T y, T fence):x(x), y(y), fence(fence), next(NULL){};

template <class T>
T Node<T>::compare(T x, T y){
    // move left
    if(this->x > x || (this->x == x && this->y > y))
        return l;
    // equal
    else if(this->x == x && this->y == y)
        return equal;
    //move right
    else return r;
}

template <class T>
LinkedList<T>::LinkedList(): length(0){
    first = 0;
};

template <class T>
void LinkedList<T>::insert(T x, T y, T fence){
    Node<T> *newNode = new Node<T>(x, y, fence);
    Node<T> *current = first;
    Node<T> *previous = 0;

    if(first == 0){
        first = newNode;
        length++;
        return;
    }

    while(current){
        if(current->compare(x, y) == r && current->next != NULL){
            //cout << "case1\n";
            previous = current;
            current = current->next;
        } else if(current->compare(x, y) == r && current->next == NULL){
            //cout << "case2\n";
            current->next = newNode;
            length++;
            return;
        } else if(current->compare(x, y) == equal){
            //cout << "case3\n";
            // update fence
            if(current->fence == 0 && fence == 1)
                current->fence = 1;
            return;
        } else if(current->compare(x, y) == l){
            //cout << "case4\n";
            if(current == first){
                newNode->next = first;
                first = newNode;
                return;
            }else break;
        }
    }
        
    previous->next = newNode;
    newNode->next = current;
    length++;

}

template <class T>
void LinkedList<T>::deletion(T x, T y){
    if(length == 0) return;

    Node<T> *pre = 0;
    Node<T> *cur = first;
    
    while(cur != NULL && cur->compare(x, y) != equal){
        pre = cur;
        cur = cur->next;
    }

    if(cur == NULL) return;
    else if (cur == first){
        if(cur->fence == 1) return;
        first = cur->next;
    }else{
        if(cur->fence == 1) return;
        pre->next = cur->next;
    }
    delete cur;
    length--;

    //show();
}

template <class T>
void LinkedList<T>::show(){
    cout << "Display\n";
    if(length == 0) return;
    Node<T> *tmp = first;
    while(tmp){
        cout << "(" << tmp->x << "," << tmp->y << ")\n";
        tmp = tmp->next;
    }
}

/**  solving function  **/

LinkedList<long long> linkedlist;

void plant(long long x,long long y,int withFence){
    linkedlist.insert(x, y, withFence);
}

void thief(long long x,long long y){
    linkedlist.deletion(x, y);
    linkedlist.deletion(x-1, y);
    linkedlist.deletion(x+1, y);
    linkedlist.deletion(x, y-1);
    linkedlist.deletion(x, y+1);
}

void superThief(long long x,long long y){
    linkedlist.deletion(x, y);
    linkedlist.deletion(x-1, y);
    linkedlist.deletion(x+1, y);
    linkedlist.deletion(x, y-1);
    linkedlist.deletion(x, y+1);
    linkedlist.deletion(x-1, y-1);
    linkedlist.deletion(x+1, y+1);
    linkedlist.deletion(x+1, y-1);
    linkedlist.deletion(x-1, y+1);
}

void display(){
    linkedlist.show();
}