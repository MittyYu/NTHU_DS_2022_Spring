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

int main(){
    Manager<Node> taskManager = Manager<Node>();
    int cmdCnt = 0;
    string command;
    cin >> cmdCnt;
    for(int j=0;j<cmdCnt;j++){
        cin >> command;
        if(command == "SET_ENDTIME"){
            u32 endTime;
            cin >> endTime;
            taskManager.cmd_set_endTime(endTime);
        }
        else if(command == "ADD_TA"){
            std::string id;
            u32 begin;
            cin >> id >> begin;
            taskManager.cmd_add_ta(id,begin);
            taskManager.result();
        }
        else if(command == "ADD_TASK"){
            std::string taskName;
            u32 costTime;
            cin >> taskName >> costTime;
            taskManager.cmd_add_task(taskName,costTime);
        }
        else if(command == "CHECK_SCHEDULE"){
            u32 costTime, endTime;
            cin >> costTime >> endTime;
            taskManager.cmd_check_schedule(costTime,endTime);
        }
    }
    taskManager.result();
    return 0;
}

u32 Node::get_time(){ return time;}
std::string Node::get_id(){ return id;}

void Node::set_time(u32 time){
    Node::time = time; 
}

// Check if the time of node1 is equal to the time of node2.
bool operator== (Node& node1, Node& node2){
    return node1.get_time() == node2.get_time();
}
// Check if the time of node1 is not equal to the parameter time.
bool operator== (Node& node1, u32 time){
    return node1.get_time() == time;
}

// Check if the time of node1 is not equal to the time of node2.
bool operator!= (Node& node1, Node& node2){
    return node1.get_time() != node2.get_time();
}
// Check if the time of node1 is not equal to the parameter time.
bool operator!= (Node& node1, u32 time){
    return node1.get_time() != time;
}

/* 
Check if the time of node1 is less than the time of node2.
If the time of node1 is equal to node2, check if the id of node1 is less than the id of node2.
*/
bool operator< (Node& node1, Node& node2){
    if(node1 == node2)
	    return node1.get_id() < node2.get_id();
	else return node1.get_time() < node2.get_time();
}
// Check if the time of node1 is less than the parameter time.
bool operator< (Node& node1, u32 time){
    return node1.get_time() < time;
}
/* 
Check if the time of node1 is greater than node2.
If the time of node1 is equal to node2, check if the id of node1 is greater than the id of node2.
*/
bool operator> (Node& node1, Node& node2){
    if(node1 == node2)
	    return node1.get_id() > node2.get_id();
	else return node1.get_time() > node2.get_time();
}
// Check if the time of node1 is greater than the parameter time.
bool operator> (Node& node1, u32 time){
    return node1.get_time() > time;
}

// Check if the time of node1 is not greater than node2.
bool operator<= (Node& node1, Node& node2){
    return node1.get_time() <= node2.get_time();
}
// Check if the time of node1 is not greater than the parameter time.
bool operator<= (Node& node1, u32 time){
    return node1.get_time() <= time;
}

// Check if the time of node1 is not less than node2.
bool operator>= (Node& node1, Node& node2){
    return node1.get_time() >= node2.get_time();
}
// Check if the time of node1 is not less than the parameter time.
bool operator>= (Node& node1, u32 time){
    return node1.get_time() >= time;
}

// Add the parameter time to the time of node.
void operator+= (Node& node1,u32 time){
    node1.set_time(node1.get_time() + time);
}


template <class T>
u32 BinaryHeap<T>::parent_idx(u32 idx){
    int p = idx/2;
    if(idx == 1) return 1;
    else return p;
}

template <class T>
u32 BinaryHeap<T>::left_idx(u32 idx){
    return idx*2;
}

template <class T>
u32 BinaryHeap<T>::right_idx(u32 idx){
    return idx*2+1;
}

template <class T>
void BinaryHeap<T>::heapify_up(int idx){
    cout << "Heapify Up" << idx << "\n";
    u32 par = parent_idx(idx);
    
    cout << "par: " << par << "\n";
    if(idx >= 0 && par >= 0 && heap[par] < heap[idx]){
        
        Node tmp = heap[idx];
        heap[idx] = heap[par];
        heap[par] = tmp;
        heapify_up(par);
    }
}

template <class T>
void BinaryHeap<T>::heapify_down(int idx){
    u32 child1 = left_idx(idx);
    u32 child2 = right_idx(idx);
    u32 smallest_idx = idx;

    // find smallest
    if(child1 < heap.size() && heap[child1] < heap[idx]){
        smallest_idx = child1;
    }
    if(child2 < heap.size() && heap[child2] < heap[smallest_idx]){
        smallest_idx = child2;
    }
    if(smallest_idx != idx){
        cout << "SWITCH\n";
        std::swap(heap[idx], heap[smallest_idx]);
        heapify_down(smallest_idx);
    }
}

template <class T>
u32 BinaryHeap<T>::size(){
    return heap.size();
}

template <class T>
void BinaryHeap<T>::insert(T element){
    cout << element.get_id() << " " << element.get_time() << "\n";
    if(!heap.size()) heap.push_back(element);

    heap.push_back(element);
    cout << "heap size: " << heap.size() << "\n";
    u32 back = heap.size()-1;
    u32 par = parent_idx(back);
    while(heap[back] < heap[par]){
        std::swap(heap[back], heap[par]);
        back = par;
    }
}

template <class T>
void BinaryHeap<T>::del_min(){
    std::swap(heap[heap.size()-1], heap[1]);
    heap.pop_back();
    heapify_down(1);
}

template <class T>
T BinaryHeap<T>::get_min(){
    if(heap.size() >= 2) return heap[1];
}

u32 curTime = 0;
int end_flag = 0;   // if endTime is set

template <class T>
// Manager<T>::Manager(): endTime(UINT_MAX){}
Manager<T>::Manager(){};


// new assigned endtime cannot be earlier than any scheduled task
// success message: SET_ENDTIME SUCCESS
// fail message: SET_ENDTIME FAIL
template <class T>
void Manager<T>::cmd_set_endTime(u32 endTime){
    // if new endtime is not earlier than any scheduled task
    // SET_ENDTIME SUCCESS
    if(endTime > curTime){
        end_flag = 1;
        Manager::endTime = endTime;
        cout << "SET_ENDTIME SUCCESS\n";
    }
    else
        cout << "SET_ENDTIME FAIL\n";
}
 
// Assign task with name to TA who is in working time and 
// has the longest available time
// If the task cannot be finished before the end time, the task cannot be assigned
// If multiple TA are equally available, assign to the TA based on lexicographic order of their name
// Task that has been scheduled cannot be rescheduled
// success message: ADD_TASK $TASK_NAME: $TA_NAME AT $FINISH_TIME
// fail message: ADD_TASK $ TASK_NAME FAIL
template <class T>
void Manager<T>::cmd_add_task(string taskName, u32 costTime){

}

//TA csn be added if the corresponding start time is earlier than the end time
// success message: ADD_TA SUCCESS
// fail message: ADD_TA FAIL
template <class T>
void Manager<T>::cmd_add_ta(std::string id, u32 begin){
    if(end_flag == 0){  // No endTime
        curTime = max(curTime, begin);
        Node ta = Node(id, begin);
        Manager::taQue.insert(ta);
        cout << "ADD_TA SUCCESS\n";
    }
    else
        cout << "ADD_TA FAIL\n";
}

template <class T>
void Manager<T>::cmd_check_schedule(u32 costTime, u32 deadLine){

}

template <class T>
void Manager<T>::result(){
    cout << "NUMBER_TA: " << taQue.size() << "\n";
    // cout << "EARLIEST FINISH TA: " << "\n";
}