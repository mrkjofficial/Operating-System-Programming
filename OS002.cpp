/* Implementation of File Permissions */

#include <fstream>
#include <iostream>
#include <map>
#include <sys/stat.h>
using namespace std;

void setMode(map<int, mode_t> &, int);

int main()
{
    map<int, mode_t> uMode;
    map<int, mode_t> gMode;
    map<int, mode_t> oMode;
    setMode(uMode, 1);
    setMode(gMode, 2);
    setMode(oMode, 3);
    char path[] = "File.txt";
    fstream fout;
    fout.open(path, ios::out);
    fout << "Karan Jaiswal" << endl;
    fout.close();
    int user, group, others;
    cout << "Enter file permission (Ex: rwx|rwx|rwx = 777): ";
    cin >> user >> group >> others;
    if (chmod(path, uMode[user] | gMode[group] | oMode[others]) != -1)
    {
        cout << "File Permissions Set Successfully!" << endl;
    }
    else
    {
        cout << "File Permissions Set Failed!" << endl;
    }
}

void setMode(map<int, mode_t> &mode, int type)
{
    if (type == 1)
    {
        mode[7] = S_IRWXU;
        mode[6] = S_IRUSR | S_IWUSR;
        mode[5] = S_IRUSR | S_IXUSR;
        mode[4] = S_IRUSR;
        mode[3] = S_IWUSR | S_IXUSR;
        mode[2] = S_IWUSR;
        mode[1] = S_IXUSR;
        mode[0] = 0;
    }
    else if (type == 2)
    {
        mode[7] = S_IRWXG;
        mode[6] = S_IRGRP | S_IWGRP;
        mode[5] = S_IRGRP | S_IXGRP;
        mode[4] = S_IRGRP;
        mode[3] = S_IWGRP | S_IXGRP;
        mode[2] = S_IWGRP;
        mode[1] = S_IXGRP;
        mode[0] = 0;
    }
    else if (type == 3)
    {
        mode[7] = S_IRWXO;
        mode[6] = S_IROTH | S_IWOTH;
        mode[5] = S_IROTH | S_IXOTH;
        mode[4] = S_IROTH;
        mode[3] = S_IWOTH | S_IXOTH;
        mode[2] = S_IWOTH;
        mode[1] = S_IXOTH;
        mode[0] = 0;
    }
}