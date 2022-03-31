#include "dragon.h"

Dragon::Dragon(string name, int health, double stamina) : //****************** 9. Initializer list
    Enemy(name, health, stamina) {} //****************** 2. Inheritance and cascading constructors

void Dragon::typeOfAttack(){ //****************** 8. Abstract classes and pure virtual functions
    cout << "The dragon breathes fire" << endl;
}

void Dragon::Attack(Character * a, Enemy * b){  //****************** 7. Virtual functions and polymorphism
    int random = rand() % 40 + 41;
    b->setStat(b->health - random, "health"); //****************** 3. Templates //****************** 6. Friends
    a->typeOfAttack();
    cout << "You damaged the " << b->name << " for " << random << " health" << endl << endl; //****************** 6. Friends

    random = rand() % 30 + 51;

    b->typeOfAttack();
    a->setStat(a->health - random, "health"); //****************** 3. Templates //****************** 6. Friends
    cout << b->getName() << " damaged the " << a->name<< " for " << random << " health" << endl; //****************** 6. Friends
    if (b->health <= 0) //****************** 6. Friends
    {
        cout << endl << "You killed the " << b->name << endl; //****************** 6. Friends
            a->addItem(new Item("key"));
            cout << "You picked up a key off the " << b->name << endl; //****************** 6. Friends
        }
    }

void Dragon::printName() //****************** 10. Dynamic and static dispatch
{
    cout << getName();
}
