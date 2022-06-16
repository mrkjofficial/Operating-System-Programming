/* Implementation of Least Recently Used Page Replacement Algorithm

Sample Input
Pages: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
Frames: 4
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

void mru(vector<int> &, vector<int> &, int, int);

int main()
{
    int pageCount, frameCount;
    cout << "Enter the No. of Pages: ";
    cin >> pageCount;
    cout << endl;
    vector<int> pages(pageCount);
    cout << "Enter Page References: ";
    for (int i = 0; i < pageCount; i++)
    {
        cin >> pages[i];
    }
    cout << endl;
    cout << "Enter the No. of Frames: ";
    cin >> frameCount;
    cout << endl;
    vector<int> frames(frameCount, INT_MIN);
    mru(pages, frames, pageCount, frameCount);
}

void mru(vector<int> &pages, vector<int> &frames, int pageCount, int frameCount)
{
    int pageFaults = 0, pageHits = 0;
    for (int i = 0; i < pageCount; i++)
    {
        auto itr = find(frames.begin(), frames.end(), pages[i]);
        if (itr != frames.end())
        {
            pageHits++;
        }
        else
        {
            int mDistance = INT_MAX, fIndex;
            for (int j = 0; j < frameCount; j++)
            {
                int distance = find(pages.rbegin() + (pages.size() - i - 1), pages.rend(), frames[j]).base() - pages.begin() - 1;
                if (distance < mDistance)
                {
                    mDistance = distance;
                    fIndex = j;
                }
            }
            frames[fIndex] = pages[i];
            pageFaults++;
        }
    }
    cout << "Page Hits: " << pageHits << endl;
    cout << "Page Faults: " << pageFaults << endl;
    cout << setprecision(2) << fixed << "Page Hit Ratio: " << (double)pageHits / pageCount << endl;
    cout << setprecision(2) << fixed << "Page Fault Ratio: " << (double)pageFaults / pageCount << endl;
}