#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include "Enemy.h"
using namespace std;

class Tile{
    private:
        string name;
        double speedMod;
        vector <Enemy> enemies;//First one is blank meaning no enemy
        vector<double> encounterChanceDay;//must add up to 1
        vector<double> encounterChanceNight;//must add up to 1
        char icon;
        int cityNum;//-1 if not city
    public:
        Tile();
        Tile(string name1, double speedMod1, vector<Enemy> enemies1, vector<double> encounterChanceDay1, vector<double> encounterChanceNight1, char icon1);
        string getName();
        void setName(string newName);
        double getSpeedMod();
        void setSpeedMod(double value);
        void setEnemies(vector<Enemy> enemies1);
        void setEncounterChanceDay(vector<double> encounterChanceDay1);
        void setEncounterChanceNight(vector<double> encounterChanceNight1);
        Enemy rollEnemies(double modifier, bool isDay);
        void setIcon(char icon1);
        char getIcon();
        
        void setCityNum(int cityNum1);
        int getCityNum();
        
        
        
        
};
