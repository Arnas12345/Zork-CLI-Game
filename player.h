#ifndef PLAYER_H
#define PLAYER_H


#include "character.h"

class Player : public Character //****************** 2. Inheritance and cascading constructors
{
public:
    Player(string name);
    void typeOfAttack() override; //****************** 8. Abstract classes and pure virtual functions
};
#endif // PLAYER_H
