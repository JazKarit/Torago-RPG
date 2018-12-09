#include <iostream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include "Item.h"
#include "Player.h"
#include "Enemy.h"
#include "City.h"
#include "Tile.h"
#include "World.h"
using namespace std;

void dispMainMenu(){
	cout << "| WASD - move | I - check inventory | P - view player stats | C - visit city (when on city tile) |" << endl;
	cout << "| M - map | K - map key | R - rest | H - view command list | Q - quit |" << endl;
	cout << "(You can also type in the name of the command you want to do)" << endl;
}

//converts input into recognized chars N,S,E,W
char convertDir(string dir){
	if (dir == "N" || dir == "n" || dir == "w" || dir == "W" || dir == "north" || dir == "North"){
		return 'N';
	}else if (dir == "S" || dir == "s" || dir == "south" || dir == "South"){
		return 'S';
	}else if (dir == "E" || dir == "e" || dir == "d" || dir == "D" || dir == "east" || dir == "East"){
		return 'E';
	}else if (dir == "A" || dir == "a" || dir == "west" || dir == "West"){
		return 'W';
	}else{
		return ' ';
	}
}



int main(){
	World world = World();
	cout << "The Treasure of Torago" << endl << endl;
	cout << "You sit at a table in the corner of a tavern when an old man" << endl;
	cout << "walks up to you and asks" << endl;
	cout << "'What is your name lad?'" << endl;
	string name;
	cin >> name;
	world.player.setName(name);
	if(name == "hacker"){//hack for testing puposes
		world.player.setStat("maxHp",10000);
		world.player.setStat("stamina",10000);
		world.player.setStat("atk",10000);
		world.player.setStat("def",10000);
		world.player.setStat("hp",10000);
		world.player.setStat("hydration",10000);
	}
	cout << "'That is the name of an adveturer if I ever knew one." << endl;
	cout << "  'Legend speaks of a time when Torago was a peaceful land" << endl;
	cout << "when the king possesed a saphire embued with magical properties" << endl;
	cout << "allowing him to establish a peaceful reign. But the saphire" << endl;
	cout << "was lost in time and the empire fell to chaos.'" << endl;
	cout << "  'I have heard rumors of a lost treasure in the mountains towards " << endl;
	cout << "the Northeast, but the years weigh heavy upon me so I cannot make the " << endl;
	cout << "journey myself. That is why I am asking you to make this journey for me." << endl;
	cout << "  'The road is long and dangerous, but I beleive you have what it takes" << endl;
	cout << "to find the lost treasure" << endl;
	cout << "  'Here's 25 gold to get you started'" << endl;
	cout << endl << endl;
	
	string choice;
	char dir = ' ';
	string input;
	dispMainMenu();
	bool gameOver = false;
	while(!gameOver){
		
		//Display time and important stats every turn
		cout << "\nThe time is now " << world.getHours() << ":00 on day " << world.getDays() << " of your expedition" << endl;
		cout << "Hp: " << world.player.getStat("hp") << "/" << world.player.getStat("maxHp") << endl;
		cout << "Stamina: " << world.player.getStat("stamina") << "%" << endl;
		cout << "Hydration: " << world.player.getStat("hydration") << "%" << endl << endl;
		cout << "\n>> " ;
		cin >> choice;
		
		//move
		if (choice == "A" || choice == "a" || choice == "west" || choice == "West" || choice == "N" || choice == "n" || choice == "north" || choice == "north" || choice == "w" || choice == "W" || choice == "south" || choice == "South" || choice == "s" || choice == "S" || choice == "d" || choice == "D" || choice == "East" || choice == "east" || choice == "e" || choice == "E"){
			dir = convertDir(choice);//returns N,S,E,W
			if (dir == ' '){
				cout << "ERROR" << endl;
			}else{
				bool newTile = world.move(dir);//move returns if player could move there
				if(newTile){
					world.stepTime(1/world.getTile().getSpeedMod(),true);//rough tiles take longer to traverse; time decreases stamina and hydration
					cout << "Current Tile: " << world.getTile().getName() << endl;
					cout << "Your surroundings now look like: " << endl;
					world.printPlayerMap();
					if(world.rollTileEnemies(1.0)){//Check if player won by defeating the sorcerer
						gameOver = true;
					}
				}
			}
			
		}else if(choice == "I" || choice == "i" || choice == "inv" || choice == "inventory" || choice == "Inv" || choice == "Inventory"){	
			world.inventoryMenu();
		}else if(choice == "C" || choice == "c" || choice == "city" || choice == "City" || choice == "Visit" || choice == "visit" || choice == "shop" || choice == "Shop"){
			if(world.getTile().getName() == "City"){
				world.shop();
			}else{
				cout << "You are not at a city" << endl;
			}
		//See player stats	
		}else if(choice == "P" || choice == "p" || choice == "player" || choice == "stats" || choice == "Player" || choice == "Stats"){
			world.player.printStats();
		}else if(choice == "h" || choice == "help" || choice == "Help"){
			cout << "\nHere is a list of commands: " << endl;
			dispMainMenu();
		//Rest to gain stamina and hp, but lose some hydration
		//Enemies can attack when you are sleeping!
		}else if(choice == "rest" || choice == "Rest" || choice == "R" || choice == "r"){
			cout << "How Long would you like to rest for? " << endl;
			bool validInput = false;
			string timeStr;
			while(!validInput){
				validInput = true;
				cin >> timeStr;
				//make sure a number is entered
				for(int i = 0; i < timeStr.length(); i++){
					if(timeStr[i] < '0' || timeStr[i] > '9'){
						validInput = false;
						cout << "Please enter a valid number" << endl;
						break;
					} 
				}
				//can only sleep for up to 12 hours
				if(validInput && stoi(timeStr) > 12){
					validInput = false;
					cout << "You can only rest for up to 12 hours" << endl;
				}
				
			}
			int sleepTime = stoi(timeStr);
			//roll for enemies once every 4 hours of resting
			while(sleepTime > 0){
				int sleepInc = 0;
				if (sleepTime >= 4){
					sleepInc = 4;
					sleepTime -= 4;
				}else{
					sleepInc = sleepTime;
					sleepTime = 0;
				}
				world.stepTime(sleepInc,false);
				if(world.player.getStat("hp") <= 0 || world.player.getStat("stamina") <= 0 || world.player.getStat("hydration") <= 0){//check if player is dead
					gameOver = true;
					break;
				}
				if(world.rollTileEnemies(1.5)){//check if game is won
					gameOver = true;
					break;
				}
				
			}
			cout << "Your surroundings now look like: " << endl;
			world.printPlayerMap();
			
		}else if (choice == "m" || choice == "M" || choice == "map"  || choice == "Map"){
			cout << "Current Tile: " << world.getTile().getName() << endl;
			world.printPlayerMap();
			
		}else if(choice == "k" || choice == "K" || choice == "key" || choice == "Key"){
			cout << "Map Key: " << endl;
			world.printMapKey();
			
		}else if(choice == "quit" || choice == "Quit" || choice == "Q" || choice == "q"){
			break;
		}else{
			cout << "\nPlease enter a valid command from the list below" << endl;
			dispMainMenu();
		}
		//check if player is dead
		if(world.player.getStat("hp") <= 0 || world.player.getStat("stamina") <= 0 || world.player.getStat("hydration") <= 0){
			gameOver = true;
		}else if(world.getTile().getName() == "River"){//Rivers quench all thirst
			world.player.setStat("hydration",100);
		}
	}
	//print reason for death
	if(world.player.getStat("hp") <= 0){
		cout << "You have 0 hp" << endl;
	}else if(world.player.getStat("stamina") <= 0){
		cout << "You have 0 stamina" << endl;
	}else if(world.player.getStat("hydration") <= 0){
		cout << "You have 0 stamina" << endl;
	}
	cout << "Game Over" << endl;
	
	
    /*
    Initialize World, load all of the data from files
    Backstory... Player fights an enemy
    Switch Player Turn:
        M or move - move
            Move Directions:
                W - North
                A - West
                S - South
                D - East
                press c to cancel
        I or inv or inventory - inventory
            Display items and equipped items
            E - Equip Item
                1. item 1
                2. item 2
                ...
            U - unequip item
                1. item 1
                2. item 2
                ...
            D - Drop item
                1. item 1
                2. item 2
                ...
            press c to cancel
        V or view or view stats - view player stats
        H or help - help on commands
        C or city or visit city - visit city (if applicable)
            B - buy
                list items and prices
            S - sell
                list items and prices
        R or rest - rest
            Change player stats
        press q to quit
    Roll enemies for new tile
    If enemy is found then start a battle
    If tile is a city add option to vist city to menu
    repeat
    
    When the boss tile is reached:
    "The treasure is in sight, but something is blocking your path"
    Run or fight
    
    When tresure is captured
    "You won!"
    "It took you xx days"
    "Enter your name to be placed on the leaderboard"
    "Would you like to see the leaderboard?"
    "Would you like to keep playing?"
    
    */
    
}
