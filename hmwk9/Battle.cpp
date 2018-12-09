#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"

Battle::Battle(Player player1, Enemy enemy1){
	enemy = enemy1;
	player = player1;
	battleOver = false;
}

Player Battle::runBattle(){
	cout << "You have encountered a level " << enemy.getLevel() << " " << enemy.getName() <<  endl << endl;
	while(true){
		
		cout << player.getName() << " hp: " << player.getStat("hp") << "/" << player.getStat("maxHp") << endl;
		cout << player.getName() <<" stamina: " << player.getStat("stamina") << "%" << endl << endl;
		cout << enemy.getName() << " hp: " << enemy.getHp() << "/" << enemy.getMaxHp() << endl << endl;
		playerTurn();
		if(battleOver){
			return player;
		}
		cout << player.getName() << " hp: " << player.getStat("hp") << "/" << player.getStat("maxHp") << endl;
		cout << enemy.getName() << " hp: " << enemy.getHp() << "/" << enemy.getMaxHp() << endl << endl;
		enemyTurn();
		if(battleOver){
			cout << player.getName() << " stamina: " << player.getStat("stamina")  << "%" << endl;
			cout << player.getName() << " hp: " << player.getStat("hp") << "/" << player.getStat("maxHp") << endl;
			return player;
		}	 
	}
}


void Battle::playerTurn(){
	bool turnOver = false;
	cout << "| A - attack | R - rest | I - inventory | S - check stats | F - flee |" << endl;
    string choice;
    cin >> choice;
    if(choice == "A" || choice == "a" || choice == "attack" || choice == "Attack"){
		srand(time(0));
		if(((rand() % 100)+1)/100.0 < player.getAccuracy()){//If number is from 0 - player accuracy ~ .70 the player makes a hit
			int damage = (player.getTotalAtk()-(enemy.getDef()/2)) * (0.85 + ((rand() % 30)+1)/100.0);//(0.85 + ((rand() % 30)+1)/100.0) adds a 15% randomness on either side of the value
			if(damage > 0){
				enemy.incHp(-damage);
				cout << enemy.getName() << " took " << damage << " damage" << endl;
			}else{
				cout << enemy.getName() << " was unaffected by your attack" << endl;
			}
		}else{
			cout << "You missed" << endl;
		}
		//Attacking expends stamina
		int staminaLoss = 7 * (0.85 + ((rand() % 30)+1)/100.0);
		player.incrementStat("stamina",-staminaLoss);
		cout << "You expended " << staminaLoss << " stamina attacking the " << enemy.getName() << endl;
		turnOver = true;//An attempted atttack counts as a turn
	}else if(choice == "R" || choice == "r" || choice == "rest" || choice == "Rest"){
		//Player can choose to rest to regain ~ 35% stamina and ~ 1/6 of their health
		int hpGain = (player.getStat("maxHp") / 6) * (0.85 + ((rand() % 30)+1)/100.0);
		int staminaGain = 35 * (0.85 + ((rand() % 30)+1)/100.0);
		player.incrementStat("hp",hpGain);
		player.incrementStat("stamina",staminaGain);
		cout << "You gained " << hpGain << " hp" << endl;
		cout << "and " << staminaGain << " stamina" << endl;
		turnOver = true;
	}else if(choice == "I" || choice == "i" || choice == "inv" || choice == "Inventory" || choice == "inventory"){
		cout << endl;
		player.printItems();
		cout << "Gold: " << player.getStat("money") << endl;
		cout << "Bag Space Used: " << player.getTotalCarryWeight() << "/" << player.getStat("carryCap") << endl;
		if(player.getItems().size() == 0){
			cout << "You have no items to use" << endl;
		}
		cout << "Type the item number of the item you want to use. (C to cancel)" << endl;
		string itemNum;
		bool validInput = false;
		while(!validInput){
			cin >> itemNum;
			if(itemNum == "C" || itemNum == "c" || itemNum == "cancel" || itemNum == "Cancel"){
				break;
			} 
			validInput = true;
			//make sure it is a number before calling stoi
			for(int i = 0; i < itemNum.length(); i++){
				if(itemNum[i] < '0' || itemNum[i] > '9'){
					validInput = false;
					break;
				} 
			}
			if(validInput && stoi(itemNum)-1 < player.getItems().size() && stoi(itemNum) > 0){//Item index is in the size of the items vector 
				if(player.getItems().at(stoi(itemNum)-1).isEquippable()){//If item is a useable item, then use it (item is either usable or equipable)
					cout << "This item can't be used" << endl;
					break;
				}else{
					player.useItem(player.getItems().at(stoi(itemNum)-1).getName());
					turnOver = true;
					break;
				}
			}else{
				cout << "Please enter a valid value from 1 to " << player.getItems().size() << endl;
			}
		}
		
	}else if(choice == "S" || choice == "s" || choice == "Stats" || choice == "stats" || choice == "check"){
		player.printStats();
	}else if(choice == "F" || choice == "f" || choice == "Flee" || choice == "flee"){
		if(((rand() % 100)+1)/100.0 < .65){//You flee successfully (65% chance)
			cout << "You manage to flee successfully" << endl;
			if(((rand() % 100)+1)/100.0 < .40){//You get attacked as you flee (40% chance)
				int dmg = (enemy.getAtk()-(player.getTotalDef()/2)) * (0.85 + ((rand() % 30)+1)/100.0);
				player.incrementStat("hp",-dmg);
				cout << "But your enemy attacks you as you leave, dealing " << dmg << " damage" << endl;
			}else{
				cout << "Without taking any damage." << endl;
			}
			turnOver = true;
			battleOver = true;
		}else{
			cout << "Your enemy stops you from leaving" << endl;
			turnOver = true;
		}
		int staminaLoss = 5 * (0.85 + ((rand() % 30)+1)/100.0);//fleeing takes stamina
		player.incrementStat("stamina",staminaLoss);
		cout << "You expended " << staminaLoss << " stamina" << endl;
	}
	cout << endl;
	if(player.getStat("stamina") <= 0 || player.getStat("hp") <= 0){//player died if stamina or health is 0
		battleOver = true;
	}else if(enemy.getHp() <= 0){//player won
		int reward = enemy.getReward() * (0.85 + ((rand() % 30)+1)/100.0);
		player.incrementStat("money",reward);
		int exp = 5*(enemy.getAtk()+enemy.getDef()+enemy.getMaxHp())/player.getStat("lvl");
		player.incrementStat("exp",exp);
		cout << "You defeated the " << enemy.getName() << ", plundered " << reward << " gold and gained " << exp << " experience" << endl;
		if(enemy.getName() == "sorcerer"){
			player.winGame();
		}
		battleOver = true;
	}
	if(turnOver || battleOver){//Repeat the player's turn if they never did an action and the battle is not over
		return;
	}else{
		playerTurn();
	}
}

void Battle::enemyTurn(){
	double randNum = ((rand() % 100)+1)/100.0;
	if(randNum > enemy.getAgression()){//attack
		int dmg = (enemy.getAtk()-(player.getTotalDef()/2)) * (0.85 + ((rand() % 30)+1)/100.0);
		if (dmg > 0){ 
			player.incrementStat("hp",-dmg);
			cout << "The " << enemy.getName() << " attacks, dealing " << dmg << " damage" << endl;
		}else{
			cout << "The " << enemy.getName() << " attacks, but deals no damage" << endl;
		}
	}else{//rest
		int heal = (enemy.getMaxHp() / 10) * (0.85 + ((rand() % 30)+1)/100.0);//heal about 10% hp 
		enemy.incHp(heal);
		cout << "The " << enemy.getName() << " rested and gained " << heal << " hp." << endl;
	}
	if(player.getStat("hp") <= 0){//player died if stamina or health is 0
		battleOver = true;
	}
	cout << endl;
}
