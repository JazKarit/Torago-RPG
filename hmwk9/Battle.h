#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include "Item.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;

class Battle{
    private:
        Enemy enemy;
        Player player;
        bool battleOver;
    public:
        Battle(Player player1, Enemy enemy1);
        Player runBattle();
        void playerTurn();
        void enemyTurn();
};

