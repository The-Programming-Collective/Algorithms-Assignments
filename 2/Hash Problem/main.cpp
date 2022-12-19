#include <iostream>
#include <fstream>
#include "Server.h"

using namespace std;

int main()
{
    Server s("credentials.txt");
    int choice;
    bool flag = true;
    string userName;
    string password;
    string secretNote;
    while (flag)
    {
        cout << "Please choose an action to continue :\n";
        cout << "1. Insert secret notes\n";
        cout << "2. Show secret notes\n";
        cout << "3. Delete secret notes\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:

            cout << "Enter existing or new username (up to 9 characters): ";
            cin >> userName;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter secret note belonging to username " + userName + " : ";
            cin >> secretNote;
            s.insert_secret_notes(userName, password, secretNote);
            break;
        case 2:
            cout << "Enter existing username: ";
            cin >> userName;
            cout << "Enter password: ";
            cin >> password;
            s.show_secret_notes(userName, password);
            break;
        case 3:
            cout << "Enter username belonging to the note you wish to delete: ";
            cin >> userName;
            cout << "Enter password: ";
            cin >> password;
            s.delete_secret_notes(userName, password);
            break;
        case 4:
            flag = false;
            break;
        }
    }
    return 0;
}