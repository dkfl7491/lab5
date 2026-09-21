#include "Friends.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    FriendshipSystem system;

    int commandCount;

    cout << "Введите количество запросов (N): ";
    cin >> commandCount;
    cin.ignore();

    vector<int> commands(commandCount);

    for (const int commandNumber : commands)
    {
        (void)commandNumber;

        string command;

        cout << "> ";
        getline(cin, command);

        system.processCommand(command);
    }

    return 0;
}
