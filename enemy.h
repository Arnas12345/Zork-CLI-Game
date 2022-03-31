#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
class Enemy : public Character //****************** 2. Inheritance and cascading constructors
{

public:
    Enemy(string name, int health, double stamina);
    virtual void Attack(Character *, Enemy *); //****************** 7. Virtual functions and polymorphism
    void typeOfAttack() override; //****************** 8. Abstract classes and pure virtual functions
    Enemy operator +(Enemy); //****************** 5. Binary operator overloading
    Enemy operator -(); //****************** 4. Unary operator overloading
    virtual void printName(); //****************** 10. Dynamic and static dispatch

};
#endif // ENEMY_H
