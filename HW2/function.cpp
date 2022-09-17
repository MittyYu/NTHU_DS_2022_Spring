#include <iostream>
#include <cstdlib>
#include "function.h"

using namespace std;

template <class T> class LinkedList;
template <class T> class Node;

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
    first = NULL;
};

template <class T>
void LinkedList<T>::insert(T x, T y, T fence){
    Node<T> *newNode = new Node<T>(x, y, fence);
    Node<T> *current = first;
    Node<T> *previous = NULL;

    if(first == NULL){
        first = newNode;
        return;
    }

    while(current){
        if(current->compare(x, y) == r){
            previous = current;
            current = current->next;
        } else if(current->compare(x, y) == equal){
            // update fence
            if(current->fence == 0 && fence == 1)
                current->fence = 1;
            return;
        } else if(current->compare(x, y) == l)
            break;
        
        previous->next = newNode;
        newNode->next = current;
        length ++;
    }


    // previous = current;
    // current->next = current->next;
    // if(current == NULL){
    //     previous->next = newNode;
    //     return;
    // }

}

template <class T>
void LinkedList<T>::deletion(T x, T y){
    Node<T> *pre = first;
    Node<T> *cur = first->next;
    while(cur){
        if(cur->compare(x, y) == equal){
            if(cur->fence == 1){    // fence
                return;
            }

            pre->next = cur->next;
            length--;
            return;
        }
        pre = pre->next;
        cur = cur->next;
    }
}

template <class T>
void LinkedList<T>::show(){
    cout << "Display\n";
    if(length == 0) return;
    Node<T> *tmp = first->next;
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

void thief(long long x,long long y);

void superThief(long long x,long long y);

void display(){
    linkedlist.show();
}