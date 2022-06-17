/* Implementation of First Come First Serve Disk Scheduling Algorithm

Sample Input
Requests: 82 170 43 140 24 16 190
Head: 50
*/

#include <iostream>
#include <vector>
#include <iterator>
#define DISKSIZE 200
using namespace std;

void sstf(vector<int> &, int, int);

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
    sstf(rQueue, head, reqCount);
}

void sstf(vector<int> &rQueue, int head, int reqCount)
{
    int seekCount = 0, curTrack;
    for (int i = 0; i < reqCount; i++)
    {
        curTrack = rQueue[i];
        seekCount += abs(curTrack - head);
        head = curTrack;
    }
    cout << "Seek Movements: " << seekCount << endl;
    cout << "Seek Sequence: ";
    copy(rQueue.begin(), rQueue.end(), ostream_iterator<int>(cout, " "));
}