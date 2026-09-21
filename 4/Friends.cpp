#include "Friends.h"

#include <iostream>
#include <sstream>

using namespace std;

// Создание взаимной дружбы
void FriendshipSystem::addFriendship(const string& first,
                                     const string& second)
{
    // Дружба с самим собой ничего не меняет
    if (first == second)
        return;

    if (friends[first].count(second) > 0)
    {
        cout << "Уже друзья\n";
        return;
    }

    friends[first].insert(second);
    friends[second].insert(first);

    cout << first << " и " << second
         << " теперь друзья\n";
}

// Количество друзей
void FriendshipSystem::countFriends(const string& person) const
{
    const auto iterator = friends.find(person);

    if (iterator == friends.end())
    {
        cout << 0 << '\n';
        return;
    }

    cout << iterator->second.size() << '\n';
}

// Проверка, являются ли люди друзьями
void FriendshipSystem::question(const string& first,
                                const string& second) const
{
    if (first == second)
    {
        cout << "Yes\n";
        return;
    }

    const auto iterator = friends.find(first);

    if (iterator != friends.end() &&
        iterator->second.count(second) > 0)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

// Обработка команды
void FriendshipSystem::processCommand(const string& command)
{
    istringstream input(command);

    string commandName;
    input >> commandName;

    if (commandName == "FRIENDS")
    {
        string first;
        string second;

        if (!(input >> first >> second))
        {
            cout << "Ошибка: неверный формат команды FRIENDS\n";
            return;
        }

        string extra;

        if (input >> extra)
        {
            cout << "Ошибка: лишние данные в команде\n";
            return;
        }

        addFriendship(first, second);
    }
    else if (commandName == "COUNT")
    {
        string person;

        if (!(input >> person))
        {
            cout << "Ошибка: не указан человек\n";
            return;
        }

        string extra;

        if (input >> extra)
        {
            cout << "Ошибка: лишние данные в команде\n";
            return;
        }

        countFriends(person);
    }
    else if (commandName == "QUESTION")
    {
        string first;
        string second;

        if (!(input >> first >> second))
        {
            cout << "Ошибка: неверный формат команды QUESTION\n";
            return;
        }

        string extra;

        if (input >> extra)
        {
            cout << "Ошибка: лишние данные в команде\n";
            return;
        }

        question(first, second);
    }
    else
    {
        cout << "Ошибка: неизвестная команда\n";
    }
}
