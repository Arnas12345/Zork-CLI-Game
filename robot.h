#ifndef ROBOT_H
#define ROBOT_H

#include "enemy.h"

class Robot : public Enemy //****************** 2. Inheritance and cascading constructors
{
public:
    Robot(string name, int health, double stamina);
    void Attack(Character *, Enemy *) override; //****************** 7. Virtual functions and polymorphism
    void typeOfAttack() override; //****************** 8. Abstract classes and pure virtual functions
    void printName() override; //****************** 10. Dynamic and static dispatch
};

#endif // ROBOT_H
