#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Enemy.h"
#include "Tile.h"
using namespace std;


Tile::Tile(){
	name = "";
    speedMod = 1;
    icon = '.';
    cityNum = -1;
}
Tile::Tile(string name1, double speedMod1, vector<Enemy> enemies1, vector<double> encounterChanceDay1, vector<double> encounterChanceNight1, char icon1){
    name = name1;
    speedMod = speedMod1;
    enemies = enemies1;
    encounterChanceDay = encounterChanceDay1;
    encounterChanceNight = encounterChanceNight1;
    icon = icon1;
    cityNum = -1;
}
string Tile::getName(){
    return name;
}
void Tile::setName(string newName){
    name = newName;
}
double Tile::getSpeedMod(){
    return speedMod;
}
void Tile::setSpeedMod(double value){
    speedMod = value;
}
void Tile::setEnemies(vector<Enemy> enemies1){
    enemies = enemies1;
}
void Tile::setEncounterChanceDay(vector<double> encounterChanceDay1){
    encounterChanceDay = encounterChanceDay1;
}
void Tile::setEncounterChanceNight(vector<double> encounterChanceNight1){
    encounterChanceNight = encounterChanceNight1;
}

//enemy chance vectors are in the form [no encounter, enemy1, ..., enemy n] all add up to 1.0
Enemy Tile::rollEnemies(double modifier, bool isDay){
    srand(time(0));
    double randNum = ((rand() % 100)+1)/100.0;
    if(isDay){
        for(int i = 0; i < enemies.size(); i++){
			if(randNum < encounterChanceDay.at(i)){
				return enemies.at(i);
			}else{
				randNum -= encounterChanceDay.at(i);//cut of the percent chance taken up by the enemy 
			}
		}
    }else{
        for(int i = 0; i < enemies.size(); i++){
			if(randNum < encounterChanceNight.at(i)){
				return enemies.at(i);
			}else{
				randNum -= encounterChanceNight.at(i);//cut of the percent chance taken up by the enemy 
			}
		}
    }
}

void Tile::setIcon(char icon1){
	icon = icon1;
}

char Tile::getIcon(){
	return icon;
}

void Tile::setCityNum(int cityNum1){
	cityNum = cityNum1;
}
int Tile::getCityNum(){
	return cityNum;
}
