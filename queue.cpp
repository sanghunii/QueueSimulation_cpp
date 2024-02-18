#include "queue.h"
#include <cstdlib>

//Queue Class Method
Queue::Queue (int qs) : qsize(qs) {
    front = rear = nullptr;
    items = 0;
}

Queue::~Queue() {
    Node * temp;
    while (front != nullptr)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}


bool Queue::isempty() const {
    return items == 0;
}


bool Queue::isfull() const {
    return items == Q_SIZE;
}


int Queue::queuecount() const {
    return items;
}


bool Queue::enqueue(const Item & item) {       
    if (isfull())
        return false;
    Node * add = new Node;
    add->item = item;
    add->next = nullptr;
    items++;
    if (front == nullptr)
        front = add;
    else
        rear->next = add;
    rear = add;
    return true;
}


bool Queue::dequeue(Item & item)            
{
    if (front == nullptr)
        return false;                       
    item = front->item;                    
    items--;
    Node * temp = front;
    front = front->next;
    delete temp;
    if (items == 0)
        rear = 0;
    return true;
}


//Cutomer Class Method
void Customer::set(long when) {
    processtime = std::rand() % 3 + 1;  //고객이 업무를 처리하는 시간 (1분 ~ 3분 사이의 무작위 값을 가진다.)
    arrive = when;                      //도착 시간
}