#include "game.h"
#include <ctime>
#include <iostream>
#include "eventmanager.h"
#include "golistener.h"
#include "maplistener.h"
#include "infolistener.h"
#include "restartlistener.h"
#include "teleportlistener.h"
#include "attacklistener.h"
#include "exitlistener.h"
#include "characterdeathlistener.h"
#include "enterroomlistener.h"
#include "victorylistener.h"
#include "takelistener.h"
#include "uselistener.h"
#include "defeatlistener.h"

Game::Game() : player("Hero"), robot("robot", 50, 50), demon("demon", 100, 100), dragon("dragon", 250, 250)
{
    srand(time(NULL));

    // Commands
    EventManager::getInstance().listen("go", new GoListener(this));
    EventManager::getInstance().listen("map", new MapListener(this));
    EventManager::getInstance().listen("info", new InfoListener(this));
    EventManager::getInstance().listen("restart", new RestartListener(this));
    EventManager::getInstance().listen("teleport", new TeleportListener(this));
    EventManager::getInstance().listen("take", new TakeListener(this));
    EventManager::getInstance().listen("use", new UseListener(this));
    EventManager::getInstance().listen("attack", new AttackListener(this));
    EventManager::getInstance().listen("exit", new ExitListener(this));

    // State changes
    EventManager::getInstance().listen("characterDeath", new CharacterDeathListener(this));
    EventManager::getInstance().listen("enterRoom", new EnterRoomListener(this));
    EventManager::getInstance().listen("victory", new VictoryListener(this));
    EventManager::getInstance().listen("defeat", new DefeatListener(this));

    rooms.push_back(new Room("A")); // 0
    rooms[0]->addItem(new Item("potion"));
    rooms.push_back(new Room("B")); // 1
    rooms[1]->addItem(new Item("cursed item"));
    rooms.push_back(new Room("C")); // 2
    rooms.push_back(new Room("D")); // 3
    rooms.push_back(new Room("E")); // 4
    rooms[4]->addItem(new Item("cursed item"));
    rooms[4]->addItem(new Item("potion"));
    rooms.push_back(new Room("F")); // 5
    rooms.push_back(new Room("G")); // 6
    rooms.push_back(new Room("H")); // 7
    rooms[7]->addItem(new Item("potion"));
    rooms.push_back(new Room("I")); // 8
    rooms.push_back(new Room("J")); // 9

    //                 N         E         S         W
    rooms[0]->setExits(rooms[4], rooms[2], rooms[7], rooms[1]);
    rooms[1]->setExits(nullptr, rooms[0], nullptr, nullptr);
    rooms[2]->setExits(nullptr, nullptr, nullptr, rooms[0]);
    rooms[3]->setExits(nullptr, rooms[4], nullptr, nullptr);
    rooms[4]->setExits(nullptr, rooms[5], rooms[0], rooms[3]);
    rooms[5]->setExits(nullptr, nullptr, nullptr, rooms[4]);
    rooms[6]->setExits(nullptr, rooms[7], nullptr, nullptr);
    rooms[7]->setExits(rooms[0], rooms[8], rooms[9], rooms[6]);
    rooms[8]->setExits(nullptr, nullptr, nullptr, rooms[7]);
    rooms[9]->setExits(rooms[7], nullptr, nullptr, nullptr);

    reset();
}

Game::~Game()
{ //****************** 1. Destructors
    cout << "Game has ended" << endl;
}

void Game::reset(bool show_update)
{
    gameOver = false;
    removeAllEnemies();

    robot.setCurrentRoom(rooms[3]);
    robot.setName("robot");
    robot.setStat(50, "health"); //****************** 3. Templates
    robot.setStat(50, "stamina"); //****************** 3. Templates

    dragon.setName("dragon");
    dragon.setCurrentRoom(rooms[5]);
    dragon.setStat(250, "health"); //****************** 3. Templates
    dragon.setStat(250, "stamina"); //****************** 3. Templates

    int random = rand() % 9;
    demon.setCurrentRoom(rooms[random]);
    demon.setStat(100, "health"); //****************** 3. Templates

    enemiesInGame.push_back(robot);
    enemiesInGame.push_back(dragon);
    enemiesInGame.push_back(demon);

    player.setCurrentRoom(rooms[0]);
    player.setStat(150, "health");
    player.setStat(100, "stamina");

    if((enemyAlive(&robot) && enemyAlive(&demon)) && (robot.getCurrentRoom() == demon.getCurrentRoom())){
        Enemy temp = robot + demon; //****************** 5. Binary operator overloading
        removeEnemy(&robot);
        robot.setName(temp.getName());
        robot.setStat(temp.getHealth(), "health"); //****************** 3. Templates
        robot.setStat(temp.getStamina(), "stamina"); //****************** 3. Templates
        enemiesInGame.push_back(robot);
        removeEnemy(&demon);
    }

    cout << "Welcome to Zork!" << endl;
    cout << "Kill the dragon to find the key" << endl;
    cout << "Character : " <<player.getName()<< endl;

    Enemy temp = robot; //****************** 10. Dynamic and static dispatch
    temp.printName(); cout << " : "; robot.printName(); cout << " , "; demon.printName(); cout << " , "; dragon.printName(); cout << endl; //****************** 10. Dynamic and static dispatch
    if (show_update)
    {
        update_screen();
    }
}

void Game::setOver(bool over)
{
    this->gameOver = over;
}

void Game::map()
{
    cout << "Key: [player] !enemy! !enemy+player] $bossEnemy$" << endl;
    string mapArray[7][11] = {{" ", "D", " ", "-", " ", "E", " ", "-", " ", "F", " "},
                              {" ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " "},
                              {" ", "B", " ", "-", " ", "A", " ", "-", " ", "C", " "},
                              {" ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " "},
                              {" ", "G", " ", "-", " ", "H", " ", "-", " ", "I", " "},
                              {" ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " "},
                              {" ", " ", " ", " ", " ", "J", " ", " ", " ", " ", " "}};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if ((mapArray[i][j] == robot.getCurrentRoom()->getName() && enemyAlive(&robot)) ||
                (mapArray[i][j] == dragon.getCurrentRoom()->getName() && enemyAlive(&dragon)) ||
                (mapArray[i][j] == demon.getCurrentRoom()->getName() && enemyAlive(&demon)))
            {
                mapArray[i][j + 1] = "!";
                mapArray[i][j - 1] = "!";
            }
            if (mapArray[i][j] == player.getCurrentRoom()->getName())
            {
                mapArray[i][j + 1] = "]";
                mapArray[i][j - 1] = "[";
            }
            if ((mapArray[i][j] == robot.getCurrentRoom()->getName() && enemyAlive(&robot) && mapArray[i][j] == player.getCurrentRoom()->getName()) ||
                (mapArray[i][j] == dragon.getCurrentRoom()->getName() && enemyAlive(&dragon) && mapArray[i][j] == player.getCurrentRoom()->getName()) ||
                (mapArray[i][j] == demon.getCurrentRoom()->getName() && enemyAlive(&demon) && mapArray[i][j] == player.getCurrentRoom()->getName()))
            {
                mapArray[i][j + 1] = "]";
                mapArray[i][j - 1] = "!";
            }
        }
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            cout << mapArray[i][j] << " ";
        }
        cout << endl;
    }
}
void Game::info()
{
    cout << "Available commands:" << endl;
    cout << " - go <direction>" << endl;
    cout << " - teleport" << endl;
    cout << " - map" << endl;
    cout << " - info" << endl;
    cout << " - attack <enemy>" << endl;
    cout << " - use <item>" << endl;
    cout << "Inventory : ";
    displayInventory();
}

void Game::go(string direction)
{
    Room *next = player.getCurrentRoom()->getExit(direction);
    if (next != nullptr && next != rooms[9])
    {
        player.setCurrentRoom(next);
        player.setStat(player.getStamina() - 2.5, "stamina"); //****************** 3. Templates
        if(enemyAlive(&robot)) enemyGo(&robot);
        if(enemyAlive(&dragon)) enemyGo(&dragon);
        if((enemyAlive(&robot) && enemyAlive(&demon)) && (robot.getCurrentRoom() == demon.getCurrentRoom())){
            Enemy temp = robot + demon; //****************** 5. Binary operator overloading
            removeEnemy(&robot);
            robot.setName(temp.getName());
            robot.setStat(temp.getHealth(), "health"); //****************** 3. Templates
            robot.setStat(temp.getStamina(), "stamina"); //****************** 3. Templates
            enemiesInGame.push_back(robot);
            removeEnemy(&demon);
        }

    }
    else if (next == rooms[9])
    {
        if (doorLocked == false)
        {
            player.setCurrentRoom(next);
            player.setStat(player.getStamina() - 2.5, "stamina"); //****************** 3. Templates
            EventManager::getInstance().trigger("enterRoom", next);
        }
        else
        {
            cout << "You can't enter, you don't have a key" << endl;
        }
    }
    else
    {
        cout << "You hit a wall" << endl;
    }
}

void Game::enemyGo(Enemy *a)
{
    int random = rand() % 4;
    string direction = "";
    if (random == 0) direction = "north";
    if (random == 1) direction = "south";
    if (random == 2) direction = "west";
    if (random == 3) direction = "east";
    Room *next = a->getCurrentRoom()->getExit(direction);
    if (next != nullptr)
    {
        a->setCurrentRoom(next);
        replaceEnemy(a);
    }
    else
        enemyGo(a);
}

void Game::displayInventory()
{
    int x = 0;
    for (int n = player.items.size(); n > 0; n--)
    {
        cout << player.items[x].getDescription() + " ";
        x++;
    }
    cout << endl;
}

void Game::teleport()
{
    int selected = rand() % rooms.size();
    player.setCurrentRoom(rooms[selected]);
    player.setStat(player.getStamina() - 30, "stamina"); //****************** 3. Templates
    EventManager::getInstance().trigger("enterRoom", rooms[selected]);
}

void Game::Use(string item)
{
    if (player.getItem(item))
    {
        if (item == "potion")
        {
            player.setStat(player.getHealth() + 100, "health"); //****************** 3. Templates
            cout << "You drank a potion and got 100 HP" << endl;
            player.dropItem(item);
        }

        else  if(item == "key"){
            if(player.getCurrentRoom()->getName() == "H"){
            doorLocked = false;
            cout << "You unlocked the door to J" << endl;
            player.dropItem(item);
            }
            else cout << "You aren't in H so you can't unlock door to J" << endl;
        }
    }
    else
        cout << "This is not in your invetory" << endl;
}

bool Game::is_over()
{
    return gameOver;
}

Player &Game::getPlayer()
{
    return player;
}

void Game::update_screen()
{
    if (!gameOver)
    {
        Room *currentRoom = player.getCurrentRoom();

        cout << endl;
        cout << "You are in " << currentRoom->getName() << endl;

        cout << "Exits:";
        if (currentRoom->getExit("north") != nullptr)
        {
            cout << " north";
        }
        if (currentRoom->getExit("east") != nullptr)
        {
            cout << " east";
        }
        if (currentRoom->getExit("south") != nullptr)
        {
            cout << " south";
        }
        if (currentRoom->getExit("west") != nullptr)
        {
            cout << " west";
        }
        cout << endl;
        displayItems();
        cout << "Type info for help." << endl;

        cout << "\t" << player.getName() << "\t"
             << "  HP: " << player.getHealth() << " ST: " << player.getStamina() << endl
             << endl;

        int x = 0;
        cout << "Enemies in room " << player.getCurrentRoom()->getName() << " : " << endl;
        for (int n = enemiesInGame.size(); n > 0; n--)
        {
            if (enemiesInGame[x].getCurrentRoom() == player.getCurrentRoom())
            {
                cout << "\t" << enemiesInGame[x].getName() << "\t"
                << "  HP: " << enemiesInGame[x].getHealth() << " ST: " << enemiesInGame[x].getStamina() << endl;
            }
            x++;
        }
        cout << endl;
    }
    else
    {
        cout << "Type \"restart\" or \"exit\"." << endl;
    }
}

void Game::takeItem(string item)
{
    Room *currentRoom = player.getCurrentRoom();
    if (currentRoom->getItem(item))
    {
        Item temp = *new Item(item);
        currentRoom->isItemInRoom(item);
        player.addItem(&temp);
        cout << " You have added " << item << " to your inventory" << endl;
        if(item == "cursed item"){
            cout << "OUUCCCHHH" << endl;
            if(enemyAlive(&dragon)){
            removeEnemy(&dragon);
            Enemy temp = -dragon; //****************** 4. Unary operator overloading
            dragon.setName(temp.getName());
            dragon.setStat(temp.getHealth(), "health"); //****************** 3. Templates
            dragon.setStat(temp.getStamina(), "stamina"); //****************** 3. Templates
            enemiesInGame.push_back(dragon);
            cout << "You took damage but so did the dragon" << endl;
        }
        }
    }
    else if (currentRoom->itemsInRoom.size() == 0)
    {
        cout << endl
             << "There are no items in this room" << endl;
    }
    else
        cout << item << " is not in this room" << endl;
}

void Game::clearRooms()
{
    int size = rooms.size();
    for (int i = 0; i < size; i++)
    {
        rooms[i]->itemsInRoom.clear();
    }
}

void Game::displayItems()
{
    Room *currentRoom = player.getCurrentRoom();
    if (currentRoom->itemsInRoom.size() < 1)
        cout << "There are no items in this room" << endl;
    if (currentRoom->itemsInRoom.size() > 0)
    {
        int x = 0;
        cout << "Items in room : ";
        for (int n = currentRoom->itemsInRoom.size(); n > 0; n--)
        {
            cout << currentRoom->itemsInRoom[x].getDescription() + " ";
            x++;
        }
        cout << endl;
    }
}

void Game::Attack(string enemy)
{
    int x = 0;
    Enemy * enemy1 = &robot; //****************** 7. Virtual functions and polymorphism
    Enemy * enemy2 = &demon; //****************** 7. Virtual functions and polymorphism
    Enemy * enemy3 = &dragon; //****************** 7. Virtual functions and polymorphism

    for (int n = enemiesInGame.size(); n > 0; n--)
    {
        if (enemy.compare(enemiesInGame[x].getName()) == 0)
        {
            if (enemiesInGame[x].getCurrentRoom() == player.getCurrentRoom())
            {
                if (enemiesInGame[x].getName() == enemy1->getName()){
                    enemy1->Attack(&player, enemy1); //****************** 7. Virtual functions and polymorphism
                    replaceEnemy(enemy1);
                    if(enemy1->getHealth() <= 0) removeEnemy(enemy1);
                    break;
                }
                else if (enemiesInGame[x].getName() == enemy2->getName()){
                    enemy2->Attack(&player, enemy2); //****************** 7. Virtual functions and polymorphism
                    replaceEnemy(enemy2);
                    if(enemy2->getHealth() <= 0) removeEnemy(enemy2);
                    break;
                }
                else if (enemiesInGame[x].getName() == enemy3->getName()){
                    enemy3->Attack(&player, enemy3); //****************** 7. Virtual functions and polymorphism
                    replaceEnemy(enemy3);
                    if(enemy3->getHealth() <= 0) removeEnemy(enemy3);
                    break;
                }
            }
            else if (enemiesInGame[x].getCurrentRoom() != player.getCurrentRoom())
                cout << enemy << " is not in same room" << endl;
        }
        x++;
    }
}

void Game::replaceEnemy(Enemy *a)
{
    int x = 0;
    string enemy = a->getName();
    for (int n = enemiesInGame.size(); n > 0; n--)
    {
        if (enemy.compare(enemiesInGame[x].getName()) == 0)
        {
            enemiesInGame.erase(enemiesInGame.begin() + x);
            enemiesInGame.push_back(*a);
        }
        x++;
    }
}

void Game::removeEnemy(Enemy *a)
{
    int x = 0;
    string enemy = a->getName();
    for (int n = enemiesInGame.size(); n > 0; n--)
    {
        if (enemy.compare(enemiesInGame[x].getName()) == 0)
        {
            enemiesInGame.erase(enemiesInGame.begin() + x);
        }
        x++;
    }
}

bool Game::enemyAlive(Enemy *a)
{
    int x = 0;
    string enemy = a->getName();
    for (int n = enemiesInGame.size(); n > 0; n--)
    {
        if (enemy.compare(enemiesInGame[x].getName()) == 0)
        {
            return true;
        }
        x++;
    }
    return false;
}

void Game::removeAllEnemies()
{
    int x = 0;
    for (int n = enemiesInGame.size(); n > 0; n--)
    {
        enemiesInGame.erase(enemiesInGame.begin() + x);
        x++;
    }
}
