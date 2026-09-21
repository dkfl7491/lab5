#include "TrainSchedule.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    TrainSchedule schedule;

    int commandCount;

    cout << "Введите количество команд: ";
    cin >> commandCount;
    cin.ignore();

    vector<int> commands(commandCount);

    for (const int commandNumber : commands)
    {
        (void)commandNumber;

        string command;

        cout << "> ";
        getline(cin, command);

        schedule.processCommand(command);
    }

    return 0;
}
