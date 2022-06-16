/* Implementation of Dinning Philosophers Problem */

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#define N 5
using namespace std;

vector<mutex> chopsticks(N);

void philosopher(int);
void eat(int);
void think(int);

int main()
{
    vector<thread> threads;
    for (int i = 0; i < N; i++)
    {
        threads.push_back(thread(philosopher, i));
    }
    for (auto &t : threads)
    {
        t.join();
    }
}

void philosopher(int id)
{
    think(id);
    this_thread::sleep_for(chrono::seconds(1));
    while (true)
    {
        if (id & 1)
        {
            chopsticks[(id + 1) % 5].lock();
            printf("Philosopher %d Picked Up Chopstick!\n", id, (id + 1) % 5);
            chopsticks[id].lock();
            printf("Philosopher %d Picked Up Chopstick!\n", id, id);
        }
        else
        {
            chopsticks[id].lock();
            printf("Philosopher %d Picked Up Chopstick!\n", id, id);
            chopsticks[(id + 1) % 5].lock();
            printf("Philosopher %d Picked Up Chopstick!\n", id, (id + 1) % 5);
        }
        eat(id);
        this_thread::sleep_for(chrono::seconds(1));
        chopsticks[id].unlock();
        printf("Philosopher %d Put Down Chopstick!\n", id, id);
        chopsticks[(id + 1) % 5].unlock();
        printf("Philosopher %d Put Down Chopstick!\n", id, (id + 1) % 5);
        think(id);
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void eat(int id)
{
    printf("Philosopher %d is Eating!\n", id);
}

void think(int id)
{
    printf("Philosopher %d is Thinking!\n", id);
}