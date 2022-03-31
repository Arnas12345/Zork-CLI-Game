#ifndef ATTACKLISTENER_H
#define ATTACKLISTENER_H
#include "eventlistener.h"
#include "eventmanager.h"
#include "game.h"
#include <vector>

class Game;

// A listener for the exit command
class AttackListener : public EventListener
{
public:
    AttackListener(Game *game);
    void run(void *args) override;

private:
    Game *game;
};

#endif // ATTACKLISTENER_H
