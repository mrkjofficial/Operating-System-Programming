/* Implementation of Priority Scheduling Algorithm (Non-Pre-emptive)

Sample Input
P0: 1 0 5
P1: 2 1 4
P3: 3 2 2
P4: 4 4 1
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

class Process
{
private:
    int id, priority, arrival, burst, completion, remaining, response, turnaround, waiting;

public:
    void setID(int id)
    {
        this->id = id;
    }
    void setPriority(int priority)
    {
        this->priority = priority;
    }
    void setArrival(int arrival)
    {
        this->arrival = arrival;
    }
    void setBurst(int burst)
    {
        this->burst = burst;
    }
    void setCompletion(int completion)
    {
        this->completion = completion;
    }
    void setRemaining(int remaining)
    {
        this->remaining = remaining;
    }
    void setResponse(int response)
    {
        this->response = response;
    }
    void setTurnaround(int turnaround)
    {
        this->turnaround = turnaround;
    }
    void setWaiting(int waiting)
    {
        this->waiting = waiting;
    }
    int getID() const
    {
        return id;
    }
    int getPriority() const
    {
        return priority;
    }
    int getArrival() const
    {
        return arrival;
    }
    int getBurst() const
    {
        return burst;
    }
    int getCompletion() const
    {
        return completion;
    }
    int getRemaining() const
    {
        return remaining;
    }
    int getResponse() const
    {
        return response;
    }
    int getTurnaround() const
    {
        return turnaround;
    }
    int getWaiting() const
    {
        return waiting;
    }
    friend bool operator<(const Process &, const Process &);
    friend bool operator==(const Process &, const Process &);
};

bool operator<(const Process &p1, const Process &p2)
{
    if (p1.getPriority() == p2.getPriority())
    {
        if (p1.getArrival() == p2.getArrival())
        {
            return p1.getID() > p2.getID();
        }
        else
        {
            return p1.getArrival() > p2.getArrival();
        }
    }
    else
    {
        return (p1.getPriority() < p2.getPriority());
    }
}

bool operator==(const Process &p1, const Process &p2)
{
    return (p1.id == p2.id);
}

void input(vector<Process> &);
void execute(vector<Process> &);
void print(vector<Process> &);

int main()
{
    int interval, n;
    cout << "Enter the no. of Processes: ";
    cin >> n;
    vector<Process> proc(n);
    input(proc);
    execute(proc);
    print(proc);
}

void input(vector<Process> &proc)
{
    cout << "Enter Priority (1-5), Arrival Time & Burst Time:" << endl;
    for (int i = 0; i < proc.size(); i++)
    {
        int priority, atime, btime;
        cout << "P" << i << ": ";
        cin >> priority >> atime >> btime;
        proc[i].setID(i);
        proc[i].setPriority(priority);
        proc[i].setArrival(atime);
        proc[i].setBurst(btime);
        proc[i].setCompletion(0);
        proc[i].setRemaining(btime);
        proc[i].setResponse(0);
        proc[i].setTurnaround(0);
        proc[i].setWaiting(0);
    }
}

void execute(vector<Process> &proc)
{
    int complete = 0, time = 0;
    vector<Process>::iterator itr;
    vector<bool> flags(proc.size());
    priority_queue<Process> rQueue;
    while (complete < proc.size())
    {
        for (int i = 0; i < proc.size(); i++)
        {
            if (proc[i].getArrival() <= time && flags[i] == false)
            {
                rQueue.push(proc[i]);
                flags[i] = true;
            }
        }
        if (!rQueue.empty())
        {
            itr = find(proc.begin(), proc.end(), rQueue.top());
            rQueue.pop();
            itr->setCompletion(time + itr->getBurst());
            itr->setResponse(time - itr->getArrival());
            itr->setTurnaround(itr->getCompletion() - itr->getArrival());
            itr->setWaiting(itr->getTurnaround() - itr->getBurst());
            complete++;
            time += itr->getBurst();
        }
        else
        {
            time++;
        }
    }
}

void print(vector<Process> &proc)
{
    double totalTaT = 0, totalWT = 0;
    cout << endl;
    cout << "Process ID\tPriority\tArrival Time\tBurst Time\tCompletion Time\tResponse Time\tTurnaround Time\tWait Time" << endl;
    for (int i = 0; i < proc.size(); i++)
    {
        cout << "P" << proc[i].getID() << "\t\t" << proc[i].getPriority() << "\t\t" << proc[i].getArrival() << "\t\t" << proc[i].getBurst() << "\t\t" << proc[i].getCompletion() << "\t\t" << proc[i].getResponse() << "\t\t" << proc[i].getTurnaround() << "\t\t" << proc[i].getWaiting() << endl;
        totalTaT += proc[i].getTurnaround();
        totalWT += proc[i].getWaiting();
    }
    cout << endl;
    cout << "Average Turnaround Time = " << fixed << setprecision(3) << totalTaT / proc.size() << endl;
    cout << "Average Waiting Time = " << fixed << setprecision(3) << totalWT / proc.size() << endl;
}