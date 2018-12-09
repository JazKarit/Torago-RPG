#include <iostream>
#include <iomanip>
#include "Item.h"
using namespace std;

Item::Item(){
   name = "";
    baseCost = 0;
    statModified = "";
    statModifier = 0;
    equippable = true;
    equipType = -1;
    weight = 0; 
}
Item::Item(string name1, int baseCost1, string statModified1, int statModifier1, bool equippable1, int equipType1, double weight1){
    name = name1;
    baseCost = baseCost1;
    statModified = statModified1;
    statModifier = statModifier1;
    equippable = equippable1;
    equipType = equipType1;
    weight = weight1;
}
string Item::getName(){
    return name;
}
int Item::getBaseCost(){
    return baseCost;
}
void Item::setBaseCost(int baseCost1){
	baseCost = baseCost1;
}
string Item::getStatModified(){
    return statModified;
}
int Item::getStatModifier(){
    return statModifier;
}
bool Item::isEquippable(){
    return equippable;
}
int Item::getEquipType(){
    return equipType;
}
double Item::getWeight(){
    return weight;
}
