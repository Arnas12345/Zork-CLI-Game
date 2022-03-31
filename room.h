#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>
#include <vector>
#include "item.h"

using namespace std;

class Room
{
public:
    Room(string name);
    string getName();
    void setExits(Room *north, Room *east, Room *south, Room *west);
    Room *getExit(string direction);
    void addItem(Item *inItem);
    int isItemInRoom(string);
    void removeItemFromRoom(int);
    bool getItem(string);
    vector<Item> itemsInRoom;

private:
    string name;
    map<string, Room *> exits;
};

#endif // ROOM_H
