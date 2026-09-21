#include "Warehouse.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    Warehouse warehouse;

    int commandCount;

    cout << "Введите количество команд: ";
    cin >> commandCount;

    // Убираем символ перевода строки после числа
    cin.ignore();

    vector<int> commands(commandCount);

    // Все команды вводятся по одной строке
    for (const int commandNumber : commands)
    {
        (void)commandNumber;

        string command;

        cout << "> ";
        getline(cin, command);

        warehouse.processCommand(command);
    }

    return 0;
}
