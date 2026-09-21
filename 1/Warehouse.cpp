#include "Warehouse.h"
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

// Создание склада
Warehouse::Warehouse()
{
    zones = {"А", "Б", "В"};
    initialize();
}

// Создание всех ячеек склада
void Warehouse::initialize()
{
    for (const string& zone : zones)
    {
        for (int rack = 1; rack <= RACKS; ++rack)
        {
            for (int section = 1; section <= SECTIONS; ++section)
            {
                for (int shelf = 1; shelf <= SHELVES; ++shelf)
                {
                    string address = zone +
                                     to_string(rack) +
                                     to_string(section) +
                                     to_string(shelf);

                    cells[address] = Cell{};
                    addressOrder.push_back(address);
                }
            }
        }
    }
}

// Проверка адреса ячейки
string Warehouse::normalizeAddress(const string& address) const
{
    if (address.length() < 4)
        return "";

    string zone(1, address[0]);

    if (zone != "А" && zone != "Б" && zone != "В")
        return "";

    string numbers = address.substr(1);

    for (const char c : numbers)
    {
        if (!isdigit(static_cast<unsigned char>(c)))
            return "";
    }

    if (numbers.length() != 4)
        return "";

    int rack = stoi(numbers.substr(0, 2));
    int section = stoi(numbers.substr(2, 1));
    int shelf = stoi(numbers.substr(3, 1));

    if (rack < 1 || rack > RACKS)
        return "";

    if (section < 1 || section > SECTIONS)
        return "";

    if (shelf < 1 || shelf > SHELVES)
        return "";

    return zone +
           to_string(rack) +
           to_string(section) +
           to_string(shelf);
}

// Добавление товара
bool Warehouse::add(const string& product,
                    int quantity,
                    const string& address)
{
    string normalizedAddress = normalizeAddress(address);

    if (normalizedAddress.empty())
    {
        cout << "Ошибка: неверный адрес ячейки\n";
        return false;
    }

    if (quantity <= 0)
    {
        cout << "Ошибка: количество должно быть положительным\n";
        return false;
    }

    Cell& cell = cells[normalizedAddress];

    if (!cell.product.empty() && cell.product != product)
    {
        cout << "Ошибка: в ячейке находится другой товар\n";
        return false;
    }

    if (cell.quantity + quantity > CELL_CAPACITY)
    {
        cout << "Ошибка: превышена вместимость ячейки\n";
        return false;
    }

    cell.product = product;
    cell.quantity += quantity;

    return true;
}

// Удаление товара
bool Warehouse::remove(const string& product,
                       int quantity,
                       const string& address)
{
    string normalizedAddress = normalizeAddress(address);

    if (normalizedAddress.empty())
    {
        cout << "Ошибка: неверный адрес ячейки\n";
        return false;
    }

    if (quantity <= 0)
    {
        cout << "Ошибка: количество должно быть положительным\n";
        return false;
    }

    Cell& cell = cells[normalizedAddress];

    if (cell.product != product)
    {
        cout << "Ошибка: такого товара нет в ячейке\n";
        return false;
    }

    if (cell.quantity < quantity)
    {
        cout << "Ошибка: недостаточно товара в ячейке\n";
        return false;
    }

    cell.quantity -= quantity;

    if (cell.quantity == 0)
        cell.product.clear();

    return true;
}

// Вывод информации о складе
void Warehouse::printInfo() const
{
    const int cellsPerZone = RACKS * SECTIONS * SHELVES;
    const int totalCells = static_cast<int>(cells.size());

    int occupiedCells = 0;

    for (const auto& [address, cell] : cells)
    {
        if (cell.quantity > 0)
            ++occupiedCells;
    }

    double overallPercentage = 0.0;

    if (totalCells > 0)
    {
        overallPercentage =
            static_cast<double>(occupiedCells) /
            totalCells * 100.0;
    }

    cout << fixed << setprecision(2);

    cout << "Общая заполненность: "
         << overallPercentage << "%\n";

    for (const string& zone : zones)
    {
        int zoneOccupied = 0;

        for (const auto& [address, cell] : cells)
        {
            if (!address.empty() &&
                address[0] == zone[0] &&
                cell.quantity > 0)
            {
                ++zoneOccupied;
            }
        }

        double zonePercentage =
            static_cast<double>(zoneOccupied) /
            cellsPerZone * 100.0;

        cout << "Зона " << zone << ": "
             << zonePercentage << "%\n";
    }

    cout << "\nЗанятые ячейки:\n";

    for (const string& address : addressOrder)
    {
        const Cell& cell = cells.at(address);

        if (cell.quantity > 0)
        {
            cout << address << " - "
                 << cell.product << ": "
                 << cell.quantity << "\n";
        }
    }

    cout << "\nПустые ячейки:\n";

    for (const string& address : addressOrder)
    {
        const Cell& cell = cells.at(address);

        if (cell.quantity == 0)
            cout << address << '\n';
    }
}

// Обработка команд пользователя
void Warehouse::processCommand(const string& command)
{
    istringstream input(command);

    string operation;
    input >> operation;

    if (operation == "ADD")
    {
        string product;
        int quantity;
        string address;

        input >> product >> quantity >> address;

        add(product, quantity, address);
    }
    else if (operation == "REMOVE")
    {
        string product;
        int quantity;
        string address;

        input >> product >> quantity >> address;

        remove(product, quantity, address);
    }
    else if (operation == "INFO")
    {
        printInfo();
    }
    else
    {
        cout << "Ошибка: неизвестная команда\n";
    }
}
