#include "attacklistener.h"

AttackListener::AttackListener(Game *game)
{
    this->game = game;
}

void AttackListener::run(void *args_ptr)
{
    if (game->is_over())
    {
        return;
    }

    vector<string> *args = (vector<string> *)args_ptr;
    if (args->size() > 1)
    {
        this->game->Attack(args->at(1));
    }
}
