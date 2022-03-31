#include "takelistener.h"
#include "eventmanager.h"

#include "game.h"

TakeListener::TakeListener(Game *game)
{
    this->game = game;
}

void TakeListener::run(void *args_ptr)
{
    if (game->is_over())
    {
        return;
    }

    vector<string> *args = (vector<string> *)args_ptr;

    if (args->size() == 2)
    {
        if (args->at(1) == "key")
        {
            if (game->getPlayer().getCurrentRoom()->getItem("key"))
            {
                game->takeItem(args->at(1));
                cout << " You can now unlock and enter room J " << endl;
            }
            else
                cout << "key"
                     << " is not in this room" << endl;
        }
        else
        {
            game->takeItem(args->at(1));
        }
    }
    else if (args->size() == 3)
    {
        if (args->at(1) == "cursed" && args->at(2) == "item")
        {
            if (game->getPlayer().getCurrentRoom()->getItem("cursed item"))
            {
                game->takeItem("cursed item");
                cout << "You took 50 damage, your health is HP:" << game->getPlayer().getHealth() - 50 << endl;
                game->getPlayer().setStat(game->getPlayer().getHealth() - 50, "health"); //****************** 3. Templates
            }
            else
                cout << "cursed item"
                     << " is not in this room" << endl;
        }
    }
}
