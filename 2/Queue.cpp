#include "Queue.h"

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

QueueSystem::QueueSystem(int windowCount)
{
    windows.resize(windowCount);
}

// Создание номера билета: T001, T002, T003...
string QueueSystem::createTicket()
{
    ostringstream output;

    output << 'T'
           << setw(3)
           << setfill('0')
           << nextTicket++;

    return output.str();
}

// Добавление посетителя в очередь
void QueueSystem::enqueue(int duration)
{
    if (duration <= 0)
    {
        cout << "Ошибка: время обслуживания должно быть положительным\n";
        return;
    }

    Visitor visitor;
    visitor.ticket = createTicket();
    visitor.duration = duration;

    visitors.push_back(visitor);

    cout << visitor.ticket << '\n';
}

// Обработка команд
bool QueueSystem::processCommand(const string& command)
{
    istringstream input(command);

    string commandName;
    input >> commandName;

    if (commandName == "ENQUEUE")
    {
        int duration;

        if (!(input >> duration))
        {
            cout << "Ошибка: неверный формат команды ENQUEUE\n";
            return false;
        }

        string extra;

        if (input >> extra)
        {
            cout << "Ошибка: лишние данные в команде\n";
            return false;
        }

        enqueue(duration);
    }
    else if (commandName == "DISTRIBUTE")
    {
        string extra;

        if (input >> extra)
        {
            cout << "Ошибка: команда DISTRIBUTE не принимает параметры\n";
            return false;
        }

        // Очищаем результаты предыдущего распределения
        for (Window& window : windows)
        {
            window.totalTime = 0;
            window.tickets.clear();
        }

        /*
            Распределение по примеру из методички.

            Посетители с одинаковым временем обслуживания
            последовательно попадают в одно окно.
            При изменении времени обслуживания переходим
            к следующему окну.
        */

        int currentWindow = 0;
        int previousDuration = -1;

        for (const Visitor& visitor : visitors)
        {
            if (previousDuration != -1 &&
                visitor.duration != previousDuration &&
                currentWindow + 1 < static_cast<int>(windows.size()))
            {
                ++currentWindow;
            }

            windows[currentWindow].tickets.push_back(visitor.ticket);
            windows[currentWindow].totalTime += visitor.duration;

            previousDuration = visitor.duration;
        }

        int windowNumber = 1;

        for (const Window& window : windows)
        {
            cout << "Окно " << windowNumber
                 << " (" << window.totalTime << " минут): ";

            bool first = true;

            for (const string& ticket : window.tickets)
            {
                if (!first)
                    cout << ", ";

                cout << ticket;
                first = false;
            }

            cout << '\n';

            ++windowNumber;
        }

        return true;
    }
    else
    {
        cout << "Ошибка: неизвестная команда\n";
    }

    return false;
}
