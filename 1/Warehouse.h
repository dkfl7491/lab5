#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Параметры склада
const int RACKS = 20;
const int SECTIONS = 5;
const int SHELVES = 2;
const int CELL_CAPACITY = 10;

struct Cell
{
    string product;
    int quantity = 0;
};

class Warehouse
{
private:
    vector<string> zones;
    map<string, Cell> cells;
    vector<string> addressOrder;

    void initialize();

    string normalizeAddress(const string& address) const;

    bool add(const string& product,
             int quantity,
             const string& address);

    bool remove(const string& product,
                int quantity,
                const string& address);

    void printInfo() const;

public:
    Warehouse();

    void processCommand(const string& command);
};

#endif
