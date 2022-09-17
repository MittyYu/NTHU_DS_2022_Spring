#include <iostream>
#include <cstdlib>
using namespace std;

class LinkedList;
class Node;

class Node
{
public:
    friend class LinkedList;

    // constructor
    Node(int ball)
    {
        this->ball = ball;
        next = nullptr;
    }

private:
    int ball;
    Node *next;
};

class LinkedList
{
public:
    /// constructor
    LinkedList()
    {
        head = nullptr;
    }

    /// member function
    void add(int ball)
    {

        Node *newNode = new Node(ball);
        if (head == 0)
        { // 若list沒有node, 令newNode為first
            head = newNode;
            return;
        }

        Node *current = head;
        while (current->next != 0)
        { // Traversal
            current = current->next;
        }
        current->next = newNode; // 將newNode接在list的尾巴
    }

    void reverse(int left, int right){
        // Node *tmp = head;
        if (head == 0 || head->next == 0) return;
        
        if (left == right) return;
 
        Node* revs = 0, *revs_prev = 0;
        Node* revend = 0, *revend_next = 0;
    
        int i = 1;
        Node* curr = head;
        while (curr && i <= right) {
            if (i < left)
                revs_prev = curr;
    
            if (i == left)
                revs = curr;
    
            if (i == right) {
                revend = curr;
                revend_next = curr->next;
            }
    
            curr = curr->next;
            i++;
        }
        revend->next = 0;
        Node* prev = 0;   
        Node* cur_sub = revs;
    
        while (cur_sub) {
            struct Node* next = cur_sub->next;
            cur_sub->next = prev;
            prev = cur_sub;
            cur_sub = next;
        }

        revend = prev;
    
        if (revs_prev)
            revs_prev->next = revend;    
        // If starting position was head
        else
            head = revend;
    
        revs->next = revend_next;
        
    }

    void show()
    {
        while (head != NULL)
        {
            cout << head->ball << " ";
            head = head->next;
        }
        return;
    }

private:
    Node *head;
};
