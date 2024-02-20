#include "queue.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

const int MIN_PER_HOUR{60};

bool newcustomer(double x);

int main() {
//시뮬레이션에 필요한 것들을 준비.
    using namespace std;
    srand(time(0));
    cout << "사례 연구: 대기열에서의 제한된 평균 대기 시간을 맞추기 위해 \
                요구되는 시간당 평균 방문인원 수\n";
    cout << "대기열의 길이: ";
    int qs;
    cin >> qs;
    Queue line1(qs);                                //#1번 대기열
    Queue line2(qs);                                //#2번 대기열

//시뮬레이션 변수들
    Item temp1;                                     //#1번 대기열에 찾아온 손님
    Item temp2;                                     //#2번 대기열에 찾아온 손님
    long turnaways = 0;                             //같이 카운팅.
    long customers = 0;                             //같이 카운팅
    long served = 0;                                //같이 카운팅
    long sum_line = 0;                              //같이 카운팅
    long wait_time_1 = 0;                           //1번 대기열에 찾아온 손님
    long wait_time_2 = 0;                           //2번 대기열에 찾아온 손님
    long line_wait = 0;                             //고객이 줄을 서서 대기한 누적시간.                   


    cout << "시뮬레이션 시간: ";
    int hours;
    cin >> hours;
    long cyclelimit = MIN_PER_HOUR * hours;         //루프가 돌아가는 횟수를 여기서 결정


//##Simulation 
    double perhour;                            
    double cust_per_min;
    double aver_wait_time = 0.0;               
    for (perhour = 1 ; aver_wait_time < 1; perhour++) 
    {    
        cust_per_min = perhour / (double)MIN_PER_HOUR;          //고객당 분. (고객)

        turnaways = 0;                          //같이 카운팅.
        customers = 0;                          //같이 카운팅
        served = 0;                             //같이 카운팅
        sum_line = 0;                           //같이 카운팅
        wait_time_1 = 0;                        
        wait_time_2 = 0;                        
        line_wait = 0;                          //고객이 줄을 서서 대기한 누적시간.
        for (int cycle = 0; cycle < cyclelimit; cycle++)
        {
//손님을 대기열에 추가하는 섹션의 코드와                                            //section of enqueue();
//대기열의 wait_time을 갱신하면서 대기열의 손님을 안으로 들여보내는 섹션의 코드            //section of dequeue();
//를 분리해야 한다.

        //##module of add customer in queue
            if (newcustomer(cust_per_min))              //해당 사이클에 손님이 찾아오면 //일단 #1번 대기열과 #2번 대기열의 길이를 비교해서 더 짧은 길이의 대기열을 찾는다. (같으면 1번으로)  
            {
                if (line1.queuecount() <= line2.queuecount())           //#1의 길이가 #2의 길이보다 짧거나같으면
                {
                    if (line1.isfull())
                        turnaways++;
                    else
                    {
                        customers++;
                        temp1.set(cycle);
                        line1.enqueue(temp1);
                    }
                }
                else 
                {
                    if (line2.isfull())
                        turnaways++;
                    else
                    {
                        customers++;
                        temp2.set(cycle);
                        line2.enqueue(temp2);
                    }
                }
            }
        //##from now. module of updating data of customer on #1 & #2
            //update #1 queue data
            if (wait_time_1 <= 0 && !line1.isempty())
            {
                line1.dequeue(temp1);
                wait_time_1 = temp1.ptime();
                line_wait += cycle - temp1.when();
                served++;
            }
            if (wait_time_1 > 0)
                --wait_time_1;
            //update #2 queue date
            if (wait_time_2 <= 0 && !line2.isempty())
            {
                line2.dequeue(temp2);
                wait_time_2 = temp2.ptime();
                line_wait += cycle - temp2.when();
                served++;
            }
            if (wait_time_2 > 0)
                --wait_time_2;
        }//end of cycle roof
        aver_wait_time = (double)line_wait / served;
    }//end of perhour roof


//##print out simulation result
    if (customers > 0)
    {
        cout << "-------------------------------\n";
        cout << "   평균 대기 시간: " << (double) line_wait / served << "분\n";
        cout << "-------------------------------\n";
        cout << "   시간당 평균 고객 수 가" << perhour << "명이면 평균 대기 시간이 1분이 넘어갑니다.\n";
    }
    else
        cout << "고객이 한명도 없습니다!\n";
    cout << "end\n";

    return 0;
}

bool newcustomer(double x) {
    return (std::rand() /(RAND_MAX * x) < 1);
}            