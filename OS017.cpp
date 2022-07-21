/* Implementation of Readers-Writers Problem */

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int readCount = 0, sharedMemLoc = 0;
mutex rMutex, wMutex;

void reader();
void writer();

int main()
{
    thread r(reader);
    thread w(writer);
    r.join();
    w.join();
}

void reader()
{
    while(true)
    {
        rMutex.lock();
        readCount++;
        if(readCount == 1)
        {
            wMutex.lock();
        }
        rMutex.unlock();
        printf("Reader reads %d!\n", sharedMemLoc);
        rMutex.lock();
        readCount--;
        if(readCount == 0)
        {
            wMutex.unlock();
        }
        rMutex.unlock();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void writer()
{
    while(true)
    {
        wMutex.lock();
        sharedMemLoc++;
        printf("Writer writes %d!\n", sharedMemLoc);
        wMutex.unlock();
        this_thread::sleep_for(chrono::seconds(1));
    }
}