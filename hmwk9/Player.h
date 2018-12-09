#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include "Item.h"
#include "Tile.h"
using namespace std;

class Player{
    private:
        string name;
        int maxHp;
        int hp;
        int stamina;
        int hydration;
        int atk;
        int def;
        int money;
        vector<Item> items;
        vector<Item> equippedItems;//helmet, chestplate, leggings, sword, shield
        int carryCap;
        int exp;
        int lvl;
        
        double accuracy;

        int getItemIndex(string item);
        int getAtkMod();
        int getDefMod();
        bool wonGame;
    public:
        Player();
        Player(string name1, int hp1, int atk1, int stamina1, int hydration1, int def1, int money1, int carryCap1);
        string getName();
        void setName(string newName);
        int getStat(string stat);
        bool setStat(string, int value);
        bool incrementStat(string stat, int value);
        vector<Item> getItems();
        vector<Item> getEquippedItems();
        void printItems();
        void printEquippedItems();
        void printStats();
		double getTotalCarryWeight();



        bool useItem(string item);
        bool equipItem(string item);
        bool addItem(Item item);
        bool dropItem(string item);
        bool dropItem(string item, bool wasUsed);

        bool tryLvlUp();

		int getTotalAtk();
		int getTotalDef();
		double getAccuracy();
		bool unequipItem(int equipPos);
		bool useWaterBottle(Item emptyBottle);
		bool fillWaterBottle(Item waterBottle, Tile tile);
		void winGame();
		bool didWinGame();



};
