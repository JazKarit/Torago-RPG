#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

class Item{
    private:
        string name;
        int baseCost;
        string statModified;
        int statModifier;
        bool equippable;
        int equipType; // -1:not equippable, 0:helmet, 1:chest,2:legs,3:sheild,4:sword
        double weight;
    public:
        Item();
        Item(string name1, int baseCost1, string statModified1, int statModifier1, bool equippable1, int equipType1, double weight1);
        string getName();
        int getBaseCost();
        void setBaseCost(int baseCost1);
        string getStatModified();
        int getStatModifier();
        bool isEquippable();
        int getEquipType();
        double getWeight();
};
