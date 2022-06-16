/* Implementation of Producer-Consumer Problem (Mutex Method) */

#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
using namespace std;

mutex m;
condition_variable cv;
deque<int> buffer;
const int maxBufferSize = 50;

void consumer()
{
    while (true)
    {
        unique_lock<mutex> locker(m);
        cv.wait(locker, [](){ return buffer.size() > 0; });
        printf("Consumed: %d\n", buffer.front());
        buffer.pop_front();
        locker.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void producer()
{
    int stock = 1;
    while (true)
    {
        unique_lock<mutex> locker(m);
        cv.wait(locker, [](){ return buffer.size() <= maxBufferSize; });
        buffer.push_back(stock);
        printf("Produced: %d\n", stock);
        stock++;
        locker.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main()
{
    thread pro(producer);
    thread con(consumer);
    pro.join();
    con.join();
}