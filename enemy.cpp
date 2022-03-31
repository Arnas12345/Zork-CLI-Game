#include "enemy.h"

Enemy::Enemy(string name, int health, double stamina) : //****************** 9. Initializer list
    Character(name, health, stamina) {} //****************** 2. Inheritance and cascading constructors

void Enemy::Attack(Character * a, Enemy * b){ //****************** 7. Virtual functions and polymorphism
    int random = rand() % 40 + 41;
    b->setStat(b->getHealth() - random, "health"); //****************** 3. Templates
    a->typeOfAttack();
    cout << "You damaged the " << b->getName() << " for " << random << " health" << endl << endl;

    random = rand() % 30 + 31;

    b->typeOfAttack();
    a->setStat(a->getHealth() - random, "health"); //****************** 3. Templates
    cout << b->getName() << " damaged the " << a->getName()<< " for " << random << " health" << endl;
    if (b->getHealth() <= 0)
    {
        cout << endl << "You killed the " << b->getName() << endl;
            a->addItem(new Item("key"));
            cout << "You picked up a key off the " << b->getName() << endl;
        }
}

void Enemy::typeOfAttack(){ //****************** 8. Abstract classes and pure virtual functions
    cout << "You got hit by a monster" << endl;
}

Enemy Enemy::operator+ (Enemy a){ //****************** 5. Binary operator overloading
    string name = this->getName()+ "-" + a.getName();
    int health = this->getHealth() + a.getHealth();
    double stamina = this->getStamina() + a.getStamina();
    Enemy temp = * new Enemy(name, health, stamina);
    return temp;
}

Enemy Enemy::operator-(){ //****************** 4. Unary operator overloading
    setName("weaker-" + this->getName());
    setStat(this->getHealth() * 0.5, "health"); //****************** 3. Templates
    setStat(this->getStamina() * 0.5, "stamina"); //****************** 3. Templates
    Enemy temp = * new Enemy(this->getName(),this->getHealth(),this->getStamina());
    return temp;
}

void Enemy::printName() //****************** 10. Dynamic and static dispatch
{
    cout << "Enemy";
}
