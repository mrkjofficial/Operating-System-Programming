/* Implementation of Scan (Elevator) Disk Scheduling Algorithm

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

void scan(vector<int> &, int, int, char);

int main()
{
	int reqCount, head;
	char direction;
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
	cout << "Enter Direction (L/R): ";
	cin >> direction;
	cout << endl;
	scan(rQueue, head, reqCount, direction);
}

void scan(vector<int> &rQueue, int head, int reqCount, char direction)
{
	int seekCount = 0, curTrack;
	vector<int> left, right, seekSequence;
	if (toupper(direction) == 'L')
	{
		left.push_back(0);
	}
	if (toupper(direction) == 'R')
	{
		right.push_back(DISKSIZE - 1);
	}
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
	sort(left.begin(), left.end());
	sort(right.begin(), right.end());
	int run = 2;
	while (run--)
	{
		if (toupper(direction) == 'R')
		{
			for (int i = 0; i < right.size(); i++)
			{
				curTrack = right[i];
				seekSequence.push_back(curTrack);
				seekCount += abs(curTrack - head);
				head = curTrack;
			}
			direction = 'L';
		}
		else if (toupper(direction) == 'L')
		{
			for (int i = left.size() - 1; i >= 0; i--)
			{
				curTrack = left[i];
				seekSequence.push_back(curTrack);
				seekCount += abs(curTrack - head);
				head = curTrack;
			}
			direction = 'R';
		}
	}
	cout << "Seek Movements: " << seekCount << endl;
	cout << "Seek Sequence: ";
	copy(seekSequence.begin(), seekSequence.end(), ostream_iterator<int>(cout, " "));
}