#include "player.h"

Player::Player(string name) : //****************** 9. Initializer list
    Character(name) {} //****************** 2. Inheritance and cascading constructors

void Player::typeOfAttack(){ //****************** 8. Abstract classes and pure virtual functions
    cout << "You attack with your sword" << endl;
}
