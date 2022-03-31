#include "character.h"

#include "eventmanager.h"

Character::Character(string name) : name(name), health(150), stamina(100) { //****************** 9. Initializer list //****************** 2. Inheritance and cascading constructors
    currentRoom = nullptr;
}

Character::Character(string name, int health, double stamina) : name(name), health(health), stamina(stamina) { //****************** 9. Initializer list //****************** 2. Inheritance and cascading constructors
    currentRoom = nullptr;
}

string Character::getName()
{
    return name;
}

int Character::getHealth()
{
    return health;
}

double Character::getStamina()
{
    return stamina;
}

Room *Character::getCurrentRoom()
{
    return currentRoom;
}

void Character::setName(string name)
{
    this->name = name;
}

void Character::setCurrentRoom(Room *next)
{
    currentRoom = next;
}

void Character::addItem(Item *item)
{
    items.push_back(*item);
}

bool Character::getItem(string inString)
{
    int x = 0;
    for (int n = items.size(); n > 0; n--)
    {
        if (inString.compare(items[x].getDescription()) == 0)
        {
            return true;
        }
        x++;
    }
    return false;
}

void Character::dropItem(string inString)
{
    int x = 0;
    for (int n = items.size(); n > 0; n--)
    {
        if (inString.compare(items[x].getDescription()) == 0)
        {
            items.erase(items.begin() + x);
        }
        x++;
    }
}
