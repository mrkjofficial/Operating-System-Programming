/* Implementation of Producer-Consumer Problem (Peterson Method) */

#include <iostream>
#include <thread>
#include <map>
#include <deque>
using namespace std;

char turn;
map<char, bool> interested;
deque<int> buffer;
const int maxBufferSize = 50;

void consumer()
{
    while (true)
    {
        interested['C'] = true;
        turn = 'C';
        while (interested['P'] == true && turn == 'C');
        if (buffer.size() <= 0)
        {
            interested['C'] = false;
        }
        else
        {
            printf("Consumed: %d\n", buffer.front());
            buffer.pop_front();
            interested['C'] = false;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void producer()
{
    int stock = 1;
    while (true)
    {
        interested['P'] = true;
        turn = 'P';
        while (interested['C'] == true && turn == 'P');
        if (buffer.size() >= maxBufferSize)
        {
            interested['P'] = false;
        }
        else
        {
            buffer.push_back(stock);
            printf("Produced: %d\n", stock);
            stock++;
            interested['P'] = false;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

int main()
{
    interested['C'] = false;
    interested['P'] = false;
    thread pro(producer);
    thread con(consumer);
    pro.join();
    con.join();
}