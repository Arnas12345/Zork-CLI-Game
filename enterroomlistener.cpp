#include "enterroomlistener.h"

#include "eventmanager.h"
#include "game.h"

EnterRoomListener::EnterRoomListener(Game *game)
{
    this->game = game;
}

void EnterRoomListener::run(void *args)
{
    if (game->is_over())
    {
        return;
    }

    Room *room = (Room *)args;

    if (room->getName() == "J" && game->enemiesInGame.size() == 0)
    {
        EventManager::getInstance().trigger("victory");
    }
}
