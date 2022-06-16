/* Implementation of Worst Fit Memory Allocation Algorithm

Sample Input
Holes: 100 500 200 300 600
Processes: 212 417 112 426
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> holes;
vector<int> procs;

void getHoles(int);
void getProcs(int);
void worstFit(int, int);

int main()
{
    int holeCount, proCount;
    cout << "Enter the No. of Holes: ";
    cin >> holeCount;
    cout << endl;
    getHoles(holeCount);
    cout << endl;
    cout << "Enter the No. of Processes: ";
    cin >> proCount;
    cout << endl;
    getProcs(proCount);
    cout << endl;
    worstFit(holeCount, proCount);
}

void getHoles(int holeCount)
{
    cout << "Enter the size of each Hole: ";
    for (int i = 0; i < holeCount; i++)
    {
        int size;
        cin >> size;
        holes.push_back(size);
    }
}

void getProcs(int proCount)
{
    cout << "Enter the size of each Process: ";
    for (int i = 0; i < proCount; i++)
    {
        int size;
        cin >> size;
        procs.push_back(size);
    }
}

void worstFit(int holeCount, int proCount)
{
    int extFrag = 0, intFrag = 0;
    vector<bool> loaded(proCount, false);
    cout << "Process\t\tSize\t\tHole\t\tLeft Space" << endl;
    for (int i = 0; i < proCount; i++)
    {
        int difference = INT_MIN, index;
        for (int j = 0; j < holes.size(); j++)
        {
            if (holes[j] - procs[i] > difference && holes[j] - procs[i] >= 0)
            {
                difference = holes[j] - procs[i];
                index = j;
            }
        }
        if (difference == INT_MIN)
        {
            extFrag += procs[i];
            cout << "P" << i << "\t\t" << procs[i] << "\t\t" << "Not Allocated!" << endl;
        }
        else
        {
            holes[index] -= procs[i];
            intFrag += holes[index];
            cout << "P" << i << "\t\t" << procs[i] << "\t\t" << index << "\t\t" << holes[index] << endl;
            loaded[i] = true;
        }
    }
    cout << endl;
    cout << "Total Internal Fragmentation: " << intFrag << endl;
    cout << "Total External Fragmentation: " << extFrag << endl;
}