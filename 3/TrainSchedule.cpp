#include "TrainSchedule.h"

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

// Определяем тип команды
Type TrainSchedule::getCommandType(const string& command) const
{
    istringstream input(command);

    string commandName;
    input >> commandName;

    if (commandName == "CREATE_TRAIN")
        return Type::CREATE_TRAIN;

    if (commandName == "TRAINS_FOR_TOWN")
        return Type::TRAINS_FOR_TOWN;

    if (commandName == "TOWNS_FOR_TRAIN")
        return Type::TOWNS_FOR_TRAIN;

    if (commandName == "TRAINS")
        return Type::TRAINS;

    return Type::UNKNOWN;
}

// Создание поезда
void TrainSchedule::createTrain(const string& name,
                                const vector<string>& towns)
{
    if (name.empty())
    {
        cout << "Ошибка: не указано название поезда\n";
        return;
    }

    if (trains.count(name) > 0)
    {
        cout << "Ошибка: поезд уже существует\n";
        return;
    }

    if (towns.size() < 2)
    {
        cout << "Ошибка: поезд должен проходить минимум через два города\n";
        return;
    }

    // Проверяем повторение городов
    set<string> uniqueTowns;

    for (const string& town : towns)
        uniqueTowns.insert(town);

    if (uniqueTowns.size() != towns.size())
    {
        cout << "Ошибка: город не может повторяться в одном маршруте\n";
        return;
    }

    Train train;
    train.name = name;
    train.towns = towns;

    trains[name] = train;

    cout << "Поезд " << name << " создан\n";
}

// Поиск поездов, проходящих через город
void TrainSchedule::trainsForTown(const string& town) const
{
    bool found = false;

    for (const auto& pair : trains)
    {
        const Train& train = pair.second;

        for (const string& currentTown : train.towns)
        {
            if (currentTown == town)
            {
                cout << train.name << '\n';
                found = true;
                break;
            }
        }
    }

    if (!found)
        cout << "Поездов не найдено\n";
}

// Вывод городов поезда
void TrainSchedule::townsForTrain(const string& trainName) const
{
    auto trainIt = trains.find(trainName);

    if (trainIt == trains.end())
    {
        cout << "Ошибка: поезд не найден\n";
        return;
    }

    const Train& train = trainIt->second;

    cout << "Поезд " << trainName << " проходит через:\n";

    for (const string& town : train.towns)
    {
        cout << town << ": ";

        bool found = false;

        for (const auto& [otherTrainName, otherTrain] : trains)
        {
            // Сам поезд не учитываем
            if (otherTrainName == trainName)
                continue;

            for (const string& otherTown : otherTrain.towns)
            {
                if (otherTown == town)
                {
                    if (found)
                        cout << ", ";

                    cout << otherTrainName;
                    found = true;
                    break;
                }
            }
        }

        if (!found)
            cout << "нет других поездов";

        cout << '\n';
    }
}

// Вывод всех поездов
void TrainSchedule::showAllTrains() const
{
    if (trains.empty())
    {
        cout << "Поездов нет\n";
        return;
    }

    for (const auto& pair : trains)
    {
        const Train& train = pair.second;

        cout << train.name << ": ";

        for (const string& town : train.towns)
            cout << town << ' ';

        cout << '\n';
    }
}

// Разбор и выполнение команды
void TrainSchedule::processCommand(const string& command)
{
    const Type type = getCommandType(command);

    istringstream input(command);

    string commandName;
    input >> commandName;

    switch (type)
    {
        case Type::CREATE_TRAIN:
        {
            string trainName;
            int townCount;

            if (!(input >> trainName >> townCount))
            {
                cout << "Ошибка: неверный формат команды CREATE_TRAIN\n";
                return;
            }

            if (townCount < 1)
            {
                cout << "Ошибка: количество городов должно быть положительным\n";
                return;
            }

            // Создаём STL-контейнер нужного количества элементов
            vector<int> townNumbers(townCount);

            vector<string> towns;

            for (const int number : townNumbers)
            {
                (void)number;

                string town;

                if (!(input >> town))
                {
                    cout << "Ошибка: указано недостаточно городов\n";
                    return;
                }

                towns.push_back(town);
            }

            string extra;

            if (input >> extra)
            {
                cout << "Ошибка: лишние данные в команде\n";
                return;
            }

            createTrain(trainName, towns);
            break;
        }

        case Type::TRAINS_FOR_TOWN:
        {
            string town;

            if (!(input >> town))
            {
                cout << "Ошибка: не указан город\n";
                return;
            }

            string extra;

            if (input >> extra)
            {
                cout << "Ошибка: лишние данные в команде\n";
                return;
            }

            trainsForTown(town);
            break;
        }

        case Type::TOWNS_FOR_TRAIN:
        {
            string trainName;

            if (!(input >> trainName))
            {
                cout << "Ошибка: не указан поезд\n";
                return;
            }

            string extra;

            if (input >> extra)
            {
                cout << "Ошибка: лишние данные в команде\n";
                return;
            }

            townsForTrain(trainName);
            break;
        }

        case Type::TRAINS:
        {
            string extra;

            if (input >> extra)
            {
                cout << "Ошибка: команда TRAINS не принимает параметры\n";
                return;
            }

            showAllTrains();
            break;
        }

        case Type::UNKNOWN:
        {
            cout << "Ошибка: неизвестная команда\n";
            break;
        }
    }
}
