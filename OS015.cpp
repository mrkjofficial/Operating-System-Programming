/* Implementation of Deadlock */

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex m1, m2;

void fun1();
void fun2();

int main()
{
    thread t1(fun1);
    thread t2(fun2);
    printf("Threads Created!\n");
    t1.join();
    t2.join();
    printf("Threads Executed: %d\n", counter);
}

void fun1()
{
    m1.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m2.lock();
    counter++;
    printf("Critical Section Function 1 Executed!");
    m2.unlock();
    m1.unlock();
}

void fun2()
{
    m2.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m1.lock();
    counter++;
    printf("Critical Section Function 2 Executed!");
    m1.unlock();
    m2.unlock();
}