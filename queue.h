#ifndef QUEUE_H_
#define QUEUE_H_

class Customer {
    private :
        long arrive;                                            //고객이 큐에 도착하는 시간
        int processtime;                                        //고객의 고래를 처리하는 시간
    public :
        Customer() {arrive = processtime = 0;}
        void set(long when);                                    //setting value of Customer instance.
        long when() const {return arrive;}                      //해당 클래스 인스턴스(고객)의 도착 시간을 리턴
        int ptime() const  {return processtime;}                //해당 클래스 인스턴스(고객)의 업무 시간을 리턴
};

typedef Customer Item;                                          //Customer class 자체를 typedef를 이용해서 Item alias를 만들어서 사용.

class Queue {
    private:
        struct Node {Item item; struct Node * next;};
        //클래스 내부 멤버들이 새로운 Node형 데이터 타입 (구조체 템플릿)을 사용할 수 있다.
        enum {Q_SIZE = 10};
        Node * front;
        Node * rear;
        int items;
        const int qsize;
        Queue(const Queue & q) : qsize(0) {}
        Queue operator=(const Queue & q) {return *this;}
    public :
        Queue (int qs = Q_SIZE);
        ~Queue();
        bool isempty() const;
        bool isfull() const;
        int queuecount() const;
        bool enqueue(const Item & item);
        bool dequeue(Item & item);
};

#endif