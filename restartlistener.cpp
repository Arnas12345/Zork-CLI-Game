#include "restartlistener.h"

#include "game.h"

RestartListener::RestartListener(Game *game)
{
    this->game = game;
}

void RestartListener::run(void *)
{
    game->reset(false);
    game->clearRooms();
    game->rooms[0]->addItem(new Item("potion"));
    game->rooms[4]->addItem(new Item("potion"));
    game->rooms[7]->addItem(new Item("potion"));
    game->rooms[1]->addItem(new Item("cursed item"));
    game->rooms[4]->addItem(new Item("cursed item"));
    game->getPlayer().items.clear();
}
