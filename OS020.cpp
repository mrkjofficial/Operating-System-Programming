/* Implementation of Banker's Algorithm

Sample Input
Process   Allocation    Max Need    Remaining Need      Available Resources        Execution Order
  P0:       0 1 0        7 5 3           7 4 3                  4 3 2                    P1
  P1:       2 0 0        3 2 2           1 2 2                  6 4 3                    P3
  P2:       3 0 2        9 0 2           6 0 2                  9 4 5                    P2
  P3:       2 1 1        4 2 2           2 1 1                  9 5 5                    P0
  P4:       0 0 2        5 3 3           5 3 1                  9 5 7                    P4

Total Resources:        9 5 7
Allocated Resources:    7 2 5
Available Resources:    2 3 2
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

vector<int> totalRes;
vector<vector<int>> allocations;
vector<vector<int>> maxNeed;
vector<vector<int>> remNeed;
vector<int> availableRes;

void getTotalRes(int);
void getAllocations(int, int);
void getMaxNeed(int, int);
void calcRemNeed(int, int);
void calcAvailableRes(int, int);
bool checkDeadlock(int, int);

int main()
{
    int proCount, resCount;
    cout << "Enter the No. of Processes: ";
    cin >> proCount;
    cout << endl;
    cout << "Enter the No. of Resources: ";
    cin >> resCount;
    cout << endl;
    getTotalRes(resCount);
    getAllocations(proCount, resCount);
    getMaxNeed(proCount, resCount);
    calcRemNeed(proCount, resCount);
    calcAvailableRes(proCount, resCount);
    if (checkDeadlock(proCount, resCount))
    {
        cout << endl;
        cout << "Sequence Execution Failed! Deadlock Found!" << endl;
    }
    else
    {
        cout << endl;
        cout << "Sequence Execution Completed! No Deadlock Found!" << endl;
    }
}

void getTotalRes(int resCount)
{
    cout << "Enter the Total Available Resources: ";
    for (int i = 0; i < resCount; i++)
    {
        int value;
        cin >> value;
        totalRes.push_back(value);
    }
    cout << endl;
}

void getAllocations(int proCount, int resCount)
{
    cout << "Enter Already Aloocated Resources for each Process:" << endl;
    cout << endl;
    for (int i = 0; i < proCount; i++)
    {
        vector<int> values;
        cout << "P" << i << ": ";
        for (int j = 0; j < resCount; j++)
        {
            int value;
            cin >> value;
            values.push_back(value);
        }
        allocations.push_back(values);
    }
    cout << endl;
}

void getMaxNeed(int proCount, int resCount)
{
    cout << "Enter Max Need for each Process:" << endl;
    cout << endl;
    for (int i = 0; i < proCount; i++)
    {
        vector<int> values;
        cout << "P" << i << ": ";
        for (int j = 0; j < resCount; j++)
        {
            int value;
            cin >> value;
            values.push_back(value);
        }
        maxNeed.push_back(values);
    }
    cout << endl;
}

void calcRemNeed(int proCount, int resCount)
{
    for (int i = 0; i < proCount; i++)
    {
        vector<int> values;
        for (int j = 0; j < resCount; j++)
        {
            int value;
            value = maxNeed[i][j] - allocations[i][j];
            values.push_back(value);
        }
        remNeed.push_back(values);
    }
}

void calcAvailableRes(int proCount, int resCount)
{
    vector<int> busyRes(resCount, 0);
    for (int i = 0; i < proCount; i++)
    {
        for (int j = 0; j < resCount; j++)
        {
            busyRes[j] += allocations[i][j];
        }
    }
    for (int i = 0; i < resCount; i++)
    {
        int value;
        value = totalRes[i] - busyRes[i];
        availableRes.push_back(value);
    }
}

bool checkDeadlock(int proCount, int resCount)
{
    int n = proCount;
    vector<bool> executed(proCount, false);
    cout << "Total Resources: ";
    copy(totalRes.begin(), totalRes.end(), ostream_iterator<int>(cout, " "));
    cout << endl << endl;
    cout << "Available Resources: ";
    copy(availableRes.begin(), availableRes.end(), ostream_iterator<int>(cout, " "));
    cout << endl << endl;
    cout << "Execution\tResources" << endl;
    while (n--)
    {
        bool deadlock = true;
        for (int i = 0; i < proCount; i++)
        {

            if (remNeed[i] <= availableRes && executed[i] == false)
            {
                transform(availableRes.begin(), availableRes.end(), allocations[i].begin(), availableRes.begin(), plus<int>());
                fill(allocations[i].begin(), allocations[i].end(), 0);
                cout << "    P" << i << "\t\t  ";
                copy(availableRes.begin(), availableRes.end(), ostream_iterator<int>(cout, " "));
                cout << endl;
                executed[i] = true;
                deadlock = false;
                break;
            }
        }
        if (deadlock == true)
        {
            break;
        }
    }
    return n == -1 ? false : true;
}