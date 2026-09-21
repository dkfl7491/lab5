#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <vector>

using namespace std;

// Посетитель электронной очереди
struct Visitor
{
    string ticket;
    int duration;
};

// Окно обслуживания
struct Window
{
    int totalTime = 0;
    vector<string> tickets;
};

class QueueSystem
{
private:
    vector<Visitor> visitors;
    vector<Window> windows;
    int nextTicket = 1;

    string createTicket();

public:
    explicit QueueSystem(int windowCount);

    void enqueue(int duration);

    // Возвращает true, если была команда DISTRIBUTE
    bool processCommand(const string& command);
};

#endif
