#include "room.h"

Room::Room(string name) : name(name) //***** 9. Initializer list
{
    exits["north"] = nullptr;
    exits["east"] = nullptr;
    exits["south"] = nullptr;
    exits["west"] = nullptr;
}

string Room::getName()
{
    return name;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    exits["north"] = north;
    exits["east"] = east;
    exits["south"] = south;
    exits["west"] = west;
}

Room *Room::getExit(string direction)
{
    return exits[direction];
}

void Room::addItem(Item *inItem)
{
    itemsInRoom.push_back(*inItem);
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1)
    {
        return false;
    }
    else if (itemsInRoom.size() > 0)
    {
        int x = 0;
        for (int n = sizeItems; n > 0; n--)
        {
            // compare inString with short description
            int tempFlag = inString.compare(itemsInRoom[x].getDescription());
            if (tempFlag == 0)
            {
                itemsInRoom.erase(itemsInRoom.begin() + x);
                return x;
            }
            x++;
        }
    }
    return -1;
}

bool Room::getItem(string inString)
{ //this method is like isItemInRoom but returns if an item string we pass in is in the room or not
    int x = 0;
    for (int n = itemsInRoom.size(); n > 0; n--)
    {
        if (inString.compare(itemsInRoom[x].getDescription()) == 0)
        {
            return true;
        }
        x++;
    }
    return false;
}
