/* Implementation of C-Scan (Circular-Elevator) Disk Scheduling Algorithm

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

void cscan(vector<int> &, int, int);

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
	cscan(rQueue, head, reqCount);
}

void cscan(vector<int> &rQueue, int head, int reqCount)
{
	int seekCount = 0, curTrack;
	vector<int> left, right, seekSequence;
	left.push_back(0);
	right.push_back(DISKSIZE - 1);
	for (int i = 0; i < reqCount; i++)
	{
		if (rQueue[i] < head)
		{
			left.push_back(rQueue[i]);
		}
		if (rQueue[i] > head)
		{
			right.push_back(rQueue[i]);
		}
	}
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());
	for (int i = 0; i < right.size(); i++)
	{
		curTrack = right[i];
		seekSequence.push_back(curTrack);
		seekCount += abs(curTrack - head);
		head = curTrack;
	}
	head = 0;
	seekCount += (DISKSIZE - 1);
	for (int i = 0; i < left.size(); i++)
	{
		curTrack = left[i];
		seekSequence.push_back(curTrack);
		seekCount += abs(curTrack - head);
		head = curTrack;
	}
	cout << "Seek Movements: " << seekCount << endl;
	cout << "Seek Sequence: ";
	copy(seekSequence.begin(), seekSequence.end(), ostream_iterator<int>(cout, " "));
}