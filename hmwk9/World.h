#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include "Item.h"
#include "Player.h"
#include "Enemy.h"
#include "City.h"
#include "Tile.h"
using namespace std;

class World{
    private:
        vector<vector<Tile>> map;
        vector<Tile> tiles;//all tile types
        vector<Item> items;//all items
        vector<Enemy> enemies;//all enemy types 
        vector<City> cities;//all cities
        int days;
        int hours;
        vector<int> playerPos = {0,0};
        
        
        bool initPlayer(string filname);
        bool initTiles(string filename);
        bool initItems(string filename);
        bool initEnemies(string filename);
        bool initCities(string filename);
        bool initMap(string filename);
        
        
    public:
        World();
        Player player;
        Enemy getEnemy(string name);
        Item getItem(string name);
        City getCity(string name);
        
        void battle(Enemy enemy);
        bool move(char dir);
        void shop();
        void printMap();
        void printPlayerMap();
        bool rollTileEnemies(double modifier);
        void stepTime(int time, bool isWalking);
        int getHours();
        int getDays();
        Tile getTile();
        void printMapKey();
        void inventoryMenu();
        bool winGame();
};
