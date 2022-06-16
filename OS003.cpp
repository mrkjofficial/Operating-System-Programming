/* Implementation of File Operations */

#include <iostream>
#include <fstream>
using namespace std;

void createFile(string&);
void editFile(string&);
void renameFile(string&);
void moveFile(string&);
void copyFile(string&);
void deleteFile(string&);

bool created = false;

int main()
{
    bool flag;
    int choice;
    string filename;
    while (true)
    {
        cout << "FILE OPERATIONS" << endl;
        cout << endl;
        cout << "1) Create" << endl;
        cout << "2) Edit" << endl;
        cout << "3) Move" << endl;
        cout << "4) Copy" << endl;
        cout << "5) Rename" << endl;
        cout << "6) Delete" << endl;
        cout << "7) Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (created)
            {
                cout << "\nFile already created!\n" << endl;
                break;
            }
            cout << "\nEnter a filename: ";
            cin >> filename;
            createFile(filename);
            created = true;
            break;
        case 2:
            if (!created)
            {
                cout << "\nFile not yet created!\n" << endl;
                break;
            }
            editFile(filename);
            break;
        case 3:
            if (!created)
            {
                cout << "\nFile not yet created!\n" << endl;
                break;
            }
            moveFile(filename);
            break;
        case 4:
            if (!created)
            {
                cout << "\nFile not yet created!\n" << endl;
                break;
            }
            copyFile(filename);
            break;
        case 5:
            if (!created)
            {
                cout << "\nFile not yet created!\n" << endl;
                break;
            }
            renameFile(filename);
            break;
        case 6:
            if (!created)
            {
                cout << "\nFile not yet created!\n" << endl;
                break;
            }
            deleteFile(filename);
            created = false;
            break;
        case 7:
            exit(0);
            break;
        default:
            cout << "\nInvalid Input!\n" << endl;
        }
    }
}

void createFile(string& filename)
{
    string content;
    ofstream fout;
    fout.open(filename, ios::out);
    if (fout.is_open())
    {
        cout << "\nEnter the file contents: ";
        cin.sync();
        getline(cin, content);
        fout << content;
        fout.close();
        cout << "\nFile creation suceeded!\n" << endl;
    }
    else
    {
        cout << "\nFile creation failed!\n" << endl;
    }
}

void editFile(string& filename)
{
    string content;
    ofstream fout;
    fout.open(filename, ios::app);
    if (fout.is_open())
    {
        cout << "\nEnter the file contents: ";
        cin.sync();
        getline(cin, content);
        content = "\n" + content;
        fout << content;
        fout.close();
        cout << "\nFile updation suceeded!\n" << endl;
    }
    else
    {
        cout << "\nFile updation failed!\n" << endl;
    }
}

void moveFile(string& filename)
{
    int created = 0, deleted = 1;
    string newfilename;
    cout << "\nEnter a new filename: ";
    cin >> newfilename;
    ofstream fout;
    ifstream fin;
    fout.open(newfilename, ios::out);
    fin.open(filename, ios::in);
    if (fout.is_open() && fin.is_open())
    {
        string line;
        while (getline(fin, line))
        {
            fout << line << endl;
        }
        fout.close();
        fin.close();
        created = 1;
    }
    deleted = remove(filename.c_str());
    if (!created && deleted)
    {
        cout << "\nFile move failed!\n" << endl;
    }
    else
    {
        cout << "\nFile move suceeded!\n" << endl;
        filename = newfilename;
    }
}

void copyFile(string& filename)
{
    string newfilename;
    cout << "\nEnter a new filename: ";
    cin >> newfilename;
    ofstream fout;
    ifstream fin;
    fout.open(newfilename, ios::out);
    fin.open(filename, ios::in);
    if (fout.is_open() && fin.is_open())
    {
        string line;
        while (getline(fin, line))
        {
            fout << line << endl;
        }
        fout.close();
        fin.close();
        cout << "\nFile copy suceeded!\n" << endl;
    }
    else
    {
        cout << "\nFile copy failed!\n" << endl;
    }
}

void renameFile(string& filename)
{
    string newfilename;
    cout << "\nEnter a new filename: ";
    cin >> newfilename;
    int value = rename(filename.c_str(), newfilename.c_str());
    if (value)
    {
        cout << "\nFile rename failed!\n" << endl;
    }
    else
    {
        cout << "\nFile rename suceeded!\n" << endl;
    }
    filename = newfilename;
}

void deleteFile(string& filename)
{
    int value = remove(filename.c_str());
    if (value)
    {
        cout << "\nFile deletion failed!\n" << endl;
    }
    else
    {
        cout << "\nFile deletion suceeded!\n" << endl;
    }
}