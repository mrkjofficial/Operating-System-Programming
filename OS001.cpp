/* Implementation of System Calls */

#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    pid_t procID, curProcID, curParProcID;
    procID = getpid();
    cout << "Process ID: " << procID << endl;
    // procID = fork();
    if (procID < 0)
    {
        cout << endl;
        cout << "Process Creation Failed!" << endl;
    }
    else if (procID == 0)
    {
        cout << endl;
        cout << "Child Process:" << endl;
        cout << endl;
        // curProcID = getpid();
        // curParProcID = getppid();
        cout << "Process ID: " << curProcID << " & Parent Process ID: " << curParProcID << endl;
        cout << endl;
        cout << "Process Terminated! " << endl;
        exit(0);
    }
    else
    {
        sleep(5);
        cout << endl;
        cout << "Parent Process:" << endl;
        cout << endl;
        // curProcID = getpid();
        cout << "Process ID: " << curProcID << " & Child Process ID: " << procID << endl;
        cout << endl;
        cout << "Process Terminated! " << endl;
        exit(0);
    }
}