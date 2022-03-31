#ifndef TAKELISTENER_H
#define TAKELISTENER_H

#include "eventlistener.h"

class Game;

// A listener for the exit command
class TakeListener : public EventListener
{
public:
    TakeListener(Game *game);
    void run(void *args) override;

private:
    Game *game;
};

#endif // TAKELISTENER_H
