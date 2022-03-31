
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "item.h"
#include "eventmanager.h"

using namespace std;

// No need to include room since we're only working with pointers.
// This is how we tell the compiler "there will be a room eventually".
// This is called a "forward declaration".
class Room;

class Character
{
    friend class Dragon; //****************** 6. Friends can touch your private parts
    friend class Robot; //****************** 6. Friends
    friend class Demon; //****************** 6. Friends

public:
    Character(string name);
    Character(string name, int health, double stamina);
    string getName();
    int getHealth();
    double getStamina();
    Room *getCurrentRoom();
    void setName(string name);
    void setCurrentRoom(Room *next);
    void addItem(Item *items);
    vector<Item> items;
    bool getItem(string);
    void dropItem(string);
    virtual void typeOfAttack() = 0 ; //****************** 8. Abstract classes and pure virtual functions


    template <typename Stat> //****************** 3. Templates
    void setStat(Stat a, string stat)
    {
        if (stat == "health")
        {
            if (a <= 0)
            {
                a = 0;
                EventManager::getInstance().trigger("characterDeath", this);
            }
            this->health = a;
        }

        else if (stat == "stamina")
        {
            if (a <= 0)
            {
                a = 0;
                EventManager::getInstance().trigger("characterDeath", this);
            }
            this->stamina = a;
        }
    }

private:
    string name;
    int health;
    double stamina;
    Room *currentRoom;
};

#endif // CHARACTER_H
