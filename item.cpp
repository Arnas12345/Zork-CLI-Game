#include "item.h"

Item::Item(string description) : description(description) {} //***** 9. Initializer list

string Item::getDescription()
{
    return description;
}

void Item::setDescription(string a)
{
    this->description = a;
}
