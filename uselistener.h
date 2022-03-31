#ifndef USELISTENER_H
#define USELISTENER_H

#include "eventlistener.h"
#include "eventmanager.h"
#include "game.h"
#include <vector>

class Game;

// A listener for the exit command
class UseListener : public EventListener
{
public:
    UseListener(Game *game);
    void run(void *args) override;

private:
    Game *game;
};

#endif // USELISTENER_H
