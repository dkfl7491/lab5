#ifndef FRIENDS_H
#define FRIENDS_H

#include <map>
#include <set>
#include <string>

using namespace std;

class FriendshipSystem
{
private:
    // Человек -> множество его друзей
    map<string, set<string>> friends;

public:
    void addFriendship(const string& first,
                       const string& second);

    void countFriends(const string& person) const;

    void question(const string& first,
                  const string& second) const;

    void processCommand(const string& command);
};

#endif
