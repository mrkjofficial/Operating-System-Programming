/* Implementation of First Come First Serve Disk Scheduling Algorithm

Sample Input
Requests: 82 170 43 140 24 16 190
Head: 50
*/

#include <bits/stdc++.h>
using namespace std;

void fcfs(vector<int> &, int, int);

int main()
{
    int reqCount, head;
    cout << "Enter the No. of Requests: ";
    cin >> reqCount;
    cout << endl;
    vector<int> rQueue(reqCount);
    cout << "Enter Requests: ";
    for (int i = 0; i < reqCount; i++)
    {
        cin >> rQueue[i];
    }
    cout << endl;
    cout << "Enter the R/W Head Position: ";
    cin >> head;
    cout << endl;
    fcfs(rQueue, head, reqCount);
}

void fcfs(vector<int> &rQueue, int head, int reqCount)
{
    int seekTime = 0;
    int curTrack;

    for (int i = 0; i < reqCount; i++)
    {
        curTrack = rQueue[i];
        seekTime += abs(curTrack - head);
        head = curTrack;
    }
    cout << "Seek Time: " << seekTime << endl;
    cout << "Seek Sequence: ";
    copy(rQueue.begin(), rQueue.end(), ostream_iterator<int>(cout, " "));
}