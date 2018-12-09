#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

class Enemy{
    private:
        string name;
        int hp;
        int maxHp;
        int def;
        int atk;
        double agression;
        double accuracy;
        int reward;
        int level; 
    public:
        Enemy();
        Enemy(string name1, int hp1, int def1, int atk1, double agression1, double accuracy1, int reward);
        string getName();
        int getHp();
        int getMaxHp();
        int getDef();
        int getAtk();
        double getAgression();
        double getAccuracy();
        void setLevel(int level);
        bool incHp(int value);
        int getReward();
        int getLevel();
};
