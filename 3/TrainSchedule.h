#ifndef TRAIN_SCHEDULE_H
#define TRAIN_SCHEDULE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// Тип команды
enum class Type
{
    CREATE_TRAIN,
    TRAINS_FOR_TOWN,
    TOWNS_FOR_TRAIN,
    TRAINS,
    UNKNOWN
};

// Информация о поезде
struct Train
{
    string name;
    vector<string> towns;
};

class TrainSchedule
{
private:
    map<string, Train> trains;

    Type getCommandType(const string& command) const;

public:
    void createTrain(const string& name,
                     const vector<string>& towns);

    void trainsForTown(const string& town) const;
    void townsForTrain(const string& trainName) const;
    void showAllTrains() const;

    void processCommand(const string& command);
};

#endif
