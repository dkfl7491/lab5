#include "Queue.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int windowCount;

    cout << "Введите количество окон: ";
    cin >> windowCount;

    if (windowCount <= 0)
    {
        cout << "Ошибка: количество окон должно быть положительным\n";
        return 1;
    }

    cin.ignore();

    QueueSystem queue(windowCount);

    string command;

    while (true)
    {
        cout << "> ";
        getline(cin, command);

        if (queue.processCommand(command))
            break;
    }

    return 0;
}
