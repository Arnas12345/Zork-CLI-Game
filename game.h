#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "character.h"
#include "room.h"
#include "enemy.h"
#include "dragon.h"
#include "demon.h"
#include "robot.h"
#include "player.h"

using namespace std;

class Game
{
public:
    Game();
    ~Game();  //****************** 1. Destructors
    void reset(bool show_update = true);
    void map();
    void info();
    void go(string direction);
    void teleport();
    void update_screen();
    Player &getPlayer();
    void setOver(bool over);
    bool is_over();
    void setCurrentRoom(Room *next);
    void takeItem(string);
    void displayInventory();
    vector<Room *> rooms;
    void clearRooms();
    void displayItems();
    void enemyGo(Enemy *);
    void Attack(string);
    void Use(string);
    vector<Enemy> enemiesInGame;
    bool enemyAlive(Enemy *);
    void removeAllEnemies();

private:
    Player player;
    bool gameOver;
    Robot robot;
    Demon demon;
    Dragon dragon;
    void replaceEnemy(Enemy *);
    void removeEnemy(Enemy *);
    bool doorLocked = true;
};
#endif // GAME_H
