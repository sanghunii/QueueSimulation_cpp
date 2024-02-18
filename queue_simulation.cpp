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
    Queue line(qs);                                 //Queue대기열 생성.

    cout << "시뮬레이션 시간: ";
    int hours;
    cin >> hours;

    long cyclelimit = MIN_PER_HOUR * hours;

    Item temp;                                      //Item은 구조체 데이터형 Customer의 alias
    long turnaways = 0;
    long customers = 0;
    long served = 0;
    long sum_line = 0;
    long wait_time = 0;
    long line_wait = 0;


//##Simulation 
    double perhour;                            
    double cust_per_min;
    double aver_wait_time = 0.0;               
    for (perhour = 1 ; aver_wait_time < 1; perhour++) 
    {    
        cust_per_min = perhour / (double)MIN_PER_HOUR;          //고객당 분. (고객)

        turnaways = 0;
        customers = 0;
        served = 0;
        sum_line = 0;
        wait_time = 0;
        line_wait = 0;
        for (int cycle = 0; cycle < cyclelimit; cycle++)
        {
            if (newcustomer(cust_per_min))
            {
                if (line.isfull())                      //꽉 차 있으면
                    turnaways++;                        //돌려보낸다.
                else
                {
                    customers++;                        //손님 추가
                    temp.set(cycle);
                    line.enqueue(temp);
                }
            }
            if (wait_time <= 0 && !line.isempty())          //드갈 시간이 되면
            {
                line.dequeue(temp);
                wait_time = temp.ptime();                   //wait_time에 지금 입장하는 고객의 proccess_time 대입.
                line_wait += cycle - temp.when();           //입장시간 - 도착시간 == 대기시간       
                served++;                                   //받은 사람 수 +1
            }

            if (wait_time > 0)
                wait_time--;
            sum_line += line.queuecount();              //꽉차서 돌려 보낸게 아니라면 line 길이를 갱신한다.
        }
        aver_wait_time = (double) line_wait / served;
    }


//##print out simulation result
    if (customers > 0)
    {
        cout << "-------------------------------\n";
        cout << "   평균 대기 시간: " << (double) line_wait / served << "분\n";
        cout << "-------------------------------\n";
        cout << "   시간당 평균 고객 수 가" << perhour << "명이면 평균 대기 시간이 1분이 넘어간다.!!\n";
    }
    else
        cout << "고객이 한명도 없습니다!\n";
    cout << "완료!\n";

    return 0;
}

bool newcustomer(double x) {
    return (std::rand() /(RAND_MAX * x) < 1);
}            