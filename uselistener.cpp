#include "uselistener.h"

UseListener::UseListener(Game *game)
{
    this->game = game;
}

void UseListener::run(void *args_ptr)
{
    if (game->is_over())
    {
        return;
    }

    vector<string> *args = (vector<string> *)args_ptr;
    if (args->size() > 1)
    {
        this->game->Use(args->at(1));
    }
}
