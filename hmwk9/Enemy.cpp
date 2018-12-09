#include <iostream>
#include <iomanip>
#include "Enemy.h"
using namespace std;

Enemy::Enemy(){
    name = "";
    maxHp = 0;
    hp = 0;
    def = 0;
    atk = 0;
    agression = 0;
    accuracy = 0;
    level = 1;
}

Enemy::Enemy(string name1, int maxHp1, int def1, int atk1, double agression1, double accuracy1, int reward1){
    name = name1;
    maxHp = maxHp1; 
    hp = maxHp;
    def = def1;
    atk = atk1;
    agression = agression1;
    accuracy = accuracy1;
    reward = reward1;
    level = 1;
}
string Enemy::getName(){
    return name;
}
int Enemy::getHp(){
    return hp;
}
int Enemy::getMaxHp(){
    return maxHp;
}
int Enemy::getDef(){
    return def;
}
int Enemy::getAtk(){
    return atk;
}
double Enemy::getAgression(){
    return agression;
}
double Enemy::getAccuracy(){
    return accuracy;
}
//base stats + 40% of base stats for each level
void Enemy::setLevel(int level1){
	level = level1;
    maxHp = maxHp+(level-1)*maxHp*.4;
    hp = maxHp;
    def = def+(level-1)*def*.4;
    atk = atk+(level-1)*atk*.4;
    reward = reward+(level-1)*reward*.4;
}
//make sure max hp is non-negative and below max hp
bool Enemy::incHp(int value){
    if (hp + value > 0  && hp + value < maxHp){
        hp += value;
        return true;
    }else if (hp + value >= maxHp){
		hp = maxHp;
    }else{
        hp = 0;
        return false;
    }
}
int Enemy::getReward(){
    return reward;
}
int Enemy::getLevel(){
	return level;
}
