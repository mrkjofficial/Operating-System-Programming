/* Implementation of Shortest Seek Time First Disk Scheduling Algorithm

Sample Input
Requests: 82 170 43 140 24 16 190
Head: 50
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
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
	vector<int> seekSequence;
	for (int i = 0; i < reqCount; i++)
	{
		int mDistance = INT_MAX, mIndex = 0;
		for (int j = 0; j < reqCount; j++)
		{
			if (abs(head - rQueue[j]) <= mDistance)
			{
				mDistance = abs(head - rQueue[j]);
				mIndex = j;
			}
		}
		curTrack = rQueue[mIndex];
		rQueue[mIndex] = INT_MIN;
		seekCount += mDistance;
		seekSequence.push_back(curTrack);
		head = curTrack;
	}
	cout << "Seek Movements: " << seekCount << endl;
	cout << "Seek Sequence: ";
	copy(seekSequence.begin(), seekSequence.end(), ostream_iterator<int>(cout, " "));
}