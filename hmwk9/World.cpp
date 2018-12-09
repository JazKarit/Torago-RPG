#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <bits/stdc++.h> 
#include "Item.h"
#include "Player.h"
#include "Enemy.h"
#include "City.h"
#include "Tile.h"
#include "World.h"
#include "Battle.h"
using namespace std;

//split a string into a vector of strings split on the delimiter
vector<string> split(string str, char c){
    vector<string> values;
    if (str.length() == 0) {
         return values;
     }
    string word = "";
    int count = 0;
    str = str + c;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            if (word.length() == 0)
                continue;
            values.push_back(word);
            word = "";
        } else {
            word = word + str[i];
        }
    }
    return values;
}

//string to boolean
bool stob(string str){
	if(str == "0" or str == "false" or str == "False"){
		return false;
	}else{
		return true;
	}
}

World::World(){
    days = 1;
    hours = 8;//start at 8 am
    playerPos[0] = 15; //starting y position from top at y=0
    playerPos[1] = 5; //starting x position from left at x=0
    bool fileLoaded[6] = {0,0,0,0,0,0}; //array of what fails to load
    //read the files to initialize everything
    fileLoaded[0] = initPlayer("player.txt");
    fileLoaded[1] = initEnemies("enemies.txt");
    fileLoaded[2] = initTiles("tiles.txt");
    fileLoaded[3] = initItems("items.txt");
    fileLoaded[4] = initCities("cities.txt");
    fileLoaded[5] = initMap("map.txt");
    for (int i = 0; i<6; i++){
        if(fileLoaded[i] == false){
            cout << "File " << i << " failed to load." << endl;
        }
    }
}

//Read file and make an instance of the player class

//commented out code is to cout all initialized values
bool World::initPlayer(string filename){
    ifstream in;
    in.open(filename);
    if (in.is_open()){
		//cout << "New Player:" << endl;
        string line = "";
        while(getline(in,line)){//In form "stat value" 
            vector<string> stat;
            stat = split(line,' ');
            player.setStat(stat.at(0),stoi(stat.at(1)));
            //cout<<stat.at(0)<< ": " << player.getStat(stat.at(0)) << endl;
        }
        in.close(); 
        return true;
    }else{
        return false;
    }
    
}


bool World::initEnemies(string filename){
    ifstream in;
    in.open(filename);
    if (in.is_open()){
		//cout << "\nEnemies:" << endl;
		string line = "";
        while(getline(in,line)){ 
			vector<string> enemyData;
            enemyData = split(line,' '); // each line is in the form "name hp def atk agression accuracy reward"
            Enemy enemy = Enemy(enemyData.at(0),stoi(enemyData.at(1)),stoi(enemyData.at(2)),stoi(enemyData.at(3)),stod(enemyData.at(4)),stod(enemyData.at(5)), stoi(enemyData.at(6)));
            enemies.push_back(enemy);
            //cout << enemy.getName() << endl;
		}
        return true;

    }else{
        return false;
    }
}


bool World::initTiles(string filename){
    ifstream in;
    in.open(filename);
    if (in.is_open()){
		//cout << "\nTiles:" << endl;
        string line = "";
        int j = 0;
        Tile newTile = Tile();
        vector<Enemy> tileEnemies;
		vector<string> enemyNames;
		vector<double> dayEncounterChances;
		vector<string> chanceStrings;
		vector<double> nightEncounterChances;
		double encounterChance;
        while(getline(in,line)){
            switch(j){//each tile takes up 6 lines
                case 0:
                    newTile.setName(line);
                   // cout << "Name: " << newTile.getName() << endl;
                    break;
                case 1:
                    newTile.setSpeedMod(stod(line));
                    //cout << "Speed Mod: " << newTile.getSpeedMod() << endl;
                    break;
				case 2:
					newTile.setIcon(line[0]);
					//cout << "Icon: " << newTile.getIcon() << endl;
                    break;
                case 3:
                    enemyNames = split(line,' ');
                    //cout << "Enemies: " << endl;
                    for(int i = 0; i < enemyNames.size(); i++){
                        tileEnemies.push_back(getEnemy(enemyNames.at(i)));//convert name to Enemy class
                       // cout << ' ' << enemyNames.at(i); 
                    }
                    newTile.setEnemies(tileEnemies);
                    //cout << endl;
                    break;
                case 4:
                    chanceStrings = split(line,' ');
                    //cout << "Day Encounter Chances: " << endl;
                    for(int i = 0; i < chanceStrings.size(); i++){
                        encounterChance = stod(chanceStrings.at(i));
                        dayEncounterChances.push_back(encounterChance);
                      // cout << dayEncounterChances.at(i) << " "; 
                    }
                    newTile.setEncounterChanceDay(dayEncounterChances);
                    //cout << endl;
                    break;
                case 5:
                    chanceStrings = split(line,' ');
                    //cout << "Night Encounter Chances: " << endl;
                    for(int i = 0; i < chanceStrings.size(); i++){
                        encounterChance = stod(chanceStrings.at(i));
                        nightEncounterChances.push_back(encounterChance);
                       // cout << nightEncounterChances.at(i) << " "; 
                    }
                    newTile.setEncounterChanceNight(nightEncounterChances);
                    
                    tiles.push_back(newTile);
                    newTile = Tile();
                    
                    //reset for next tile type
                    dayEncounterChances = {};
					nightEncounterChances = {};
                    j=-2;
                    //cout << endl;
                    break;
            }
            j++;
           // cout << endl;
        }
        in.close(); 
        return true;

    }else{
        return false;
    }
}
bool World::initItems(string filename){
    ifstream in;
    in.open(filename);
    if (in.is_open()){
		//cout << "\nItems:" << endl;
		string line = "";
		int i = 0;
        while(getline(in,line)){//in form "name stats..."
			if(line != ""){
				vector<string> itemData;
				itemData = split(line,' ');
				Item item = Item(itemData.at(0),stoi(itemData.at(1)),itemData.at(2),stoi(itemData.at(3)),stob(itemData.at(4)),stoi(itemData.at(5)),stod(itemData.at(6)));
				items.push_back(item);
				//cout << items.at(i).getName() << endl;
				i++;
			}
		}
        return true;

    }else{
        return false;
    }
}

bool World::initCities(string filename){
    ifstream in;
    in.open(filename);
    if (in.is_open()){
		//cout << "\nCities:" << endl;
		string line = "";
		vector<Item> cityItems;
		vector<string> cityItemNames;
		int i = 0;
		City city = City();
		//Each city is in the form
		//Name
		//price multiplier
		//item 1
		//item 2
		//...
		//item n
        while(getline(in,line)){
			if(line != ""){//each city is seperated by a blank line
				if(i==0){
					city.setName(line);
					i++;
					//cout << city.getName() << endl;
				}else if(i==1){
					city.setPriceMult(stod(line));
					i++;
					//cout << city.getPriceMult() << endl;
				}else{
					cityItemNames.push_back(line);
				}
			}else{
				//make city from info and add to cities
				for(int i = 0; i < cityItemNames.size(); i++){
					cityItems.push_back(getItem(cityItemNames.at(i)));//string to Item class
				}
				city.setItemsAvailable(cityItems);
				city.setPrices();//apply the price multiplier
				//for(int i = 0; i < cityItemNames.size(); i++){
					//cout << i << " " << city.getItemsAvailable().at(i).getName() << " " << city.getItemsAvailable().at(i).getBaseCost() << endl; 
				//}
				cities.push_back(city);
				
				//reset for next city
				cityItems = {};
				cityItemNames = {};
				i=0;
			}//end if-else
		}//end while
		
        return true;

    }else{
        return false;
    }
}


bool World::initMap(string filename){
    ifstream in;
    in.open(filename);
    if (in.is_open()){
		//cout << "Map:" << endl;
        string line = "";
        while(getline(in,line)){//each character is a tile
            vector<Tile> mapRow = {};
            for(int i = 0; i<line.length(); i++){
				mapRow.push_back(Tile());
				for(int j = 0; j<tiles.size(); j++){
					if(line[i] == tiles.at(j).getIcon()){//icon to Tile class
						mapRow[i] = tiles.at(j);
						break;
					}else if(line[i] >= '0' && line[i] <= '9'){//number means its a city
						mapRow[i] = tiles.at(4);
						int cityNum = line[i] - '0';
						mapRow[i].setCityNum(cityNum);
						break;
					}else if(line[i] == '.'){//none tile: impassable  (redundant will be dealt with above)
						mapRow[i] = Tile();
					}
				}
				//cout << mapRow.at(i).getIcon(); 
			}
			map.push_back(mapRow);
			//cout << endl;
        }
        //printMap();
        in.close(); 
        return true;
    }else{
        return false;
    }
}

//print the whole map
void World::printMap(){
	for(int y = 0; y < map.size(); y++){
		for(int x = 0; x < map.at(y).size(); x++){
			if(y == playerPos.at(0) && x == playerPos.at(1)){
				cout << "p/";
			}else{
				cout << map.at(y).at(x).getIcon();
			}
		}
		cout << endl;
	}
}

//print what the player can see
void World::printPlayerMap(){
	int sightRange = 5;//5 is avg sight range
	if(getTile().getName() == "Forest"){
		sightRange = 3;
	}else if(getTile().getName() == "Mountain"){
		sightRange = 7;
	}
	if(getHours() < 5 || getHours() > 21){//cut sight range a night
		sightRange -= 2;
	}else if(getHours() < 9 || getHours() > 18){//cut sight range in mornings/evenings
		sightRange -= 1;
	}
	int p_y = playerPos.at(0);
	int p_x = playerPos.at(1);
	//print 7 tiles around the player, but fill unknown tiles with "."
	for(int y = p_y - 7; y <= p_y + 7; y++){
		for(int x = p_x - 7; x <= p_x + 7; x++){
			if(y == p_y && x == p_x){
				cout << "p/";
			}else if (y < map.size() && x < map.at(y).size() && y >= 0 && x >= 0){//check if in map
				if((y >= p_y - sightRange) && y <= p_y + sightRange && x >= p_x - sightRange && x <= p_x + sightRange){//check if in sight range
					cout << map.at(y).at(x).getIcon() << " ";//each tile is 2 wide to make the map more square
				}else{
					cout << ". ";//can't see tile
				}
			}else{
				cout << ". ";//outside map
			}
		}
		cout << endl;
	}
}



bool World::move(char dir){
    //try to move the player in the direction chosen 
    //should work for non rectangular maps
    
    //Move in a direction if their is room on the map in that direction
    int y = playerPos.at(0);
    int x = playerPos.at(1);
    if(dir == 'N' && y > 0 && map.at(y-1).size() > x && map.at(y-1).at(x).getName() != "Empty"){//check if on map and if tile is impassable
		cout << "You move one tile North" << endl;
		playerPos[0] -= 1;
		return true;
	}else if(dir == 'S' && y < map.size()-1 && map.at(y+1).size() > x && map.at(y+1).at(x).getName() != "Empty"){
		cout << "You move one tile South" << endl;
		playerPos[0] += 1;
		return true;
	}else if(dir == 'W' && x > 0 && map.at(y).at(x-1).getName() != "Empty"){
		cout << "You move one tile West" << endl;
		playerPos[1] -= 1;
		return true;
	}else if(dir == 'E' && x < map.at(y).size()-1 && map.at(y).at(x+1).getName() != "Empty"){
		cout << "You move one tile East" << endl;
		playerPos[1] += 1;
		return true;
	}else{
		cout << "You try to move in that direction, but an invisible force fills you with despair" << endl;
		cout << "and you have to turn back." << endl;
		return false;
	}
}

void World::shop(){
    City city = cities.at(map.at(playerPos.at(0)).at(playerPos.at(1)).getCityNum());
    if(city.getName() != ""){
		string choice;
		while(true){
			cout << "\nGold: " << player.getStat("money") << endl;
			cout << "Bag Space Used: " << player.getTotalCarryWeight() << "/" << player.getStat("carryCap") << endl << endl;
			cout << city.getName() << " shop: \n| B - Buy | S - sell | L - leave |" << endl << endl;
			cin >> choice;
			if(choice == "B" || choice == "b" || choice == "buy" || choice == "Buy"){
				cout << "What do you want to buy?\n(enter the number of the item, or c to cancel)" << endl << endl;
				city.printItemsAvailable();
				cout << endl;
				string itemStr;
				bool validInput = false;
				while(!validInput){
					cin >> itemStr;
					if(itemStr == "C" || itemStr == "c" || itemStr == "cancel" || itemStr == "Cancel"){
						break;
					} 
					validInput = true;
					//make sure it is a number before calling stoi
					for(int i = 0; i < itemStr.length(); i++){
						if(itemStr[i] < '0' || itemStr[i] > '9'){
							validInput = false;
							break;
						} 
					}
					if(validInput && stoi(itemStr)-1 < city.getItemsAvailable().size()  && stoi(itemStr) > 0){//Item index is in the size of the items vector 
						Item item = city.getItemsAvailable().at(stoi(itemStr)-1);
						int price = item.getBaseCost();
						if(player.getStat("money") - price >= 0 && player.getTotalCarryWeight() + item.getWeight() <= player.getStat("carryCap")){ //can player pay? do they have room?
							player.incrementStat("money",-price);
							player.addItem(item);
							cout << "You bought the " << item.getName() << " for " << price << " gold" << endl;
						}else if(player.getStat("money") - price < 0){
							cout << "You do not have enough money to buy this item" << endl;
						}else{
							cout << "You do not have enough room in your bag to hold this item" << endl;
							cout << "Bag Space Used: " << player.getTotalCarryWeight() << "/" << player.getStat("carryCap") << endl;
							cout << "Item Weight: " << item.getWeight() << endl;
							
						}
						
					}else{
						cout << "Please enter a valid value from 1 to " << city.getItemsAvailable().size() << endl;
					}
				}
			}else if (choice == "S" || choice == "s" || choice == "sell" || choice == "Sell"){
				player.printItems();//can only sell unequiped items
				if(player.getItems().size() == 0){
					cout << "You have no items to sell" << endl;
				}else{
					cout << "Type the item number of the item you want to sell. (C to cancel)" << endl;
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
							Item item = player.getItems().at(stoi(itemNum)-1);
							int price = item.getBaseCost() * .85;
							cout << "Do you want to sell the " << item.getName() << " for " << price << " gold?" << endl;
							string answer;
							while(true){
								cin >> answer;
								if(answer == "Yes" || answer == "Y" || answer == "y" || answer == "Y"){
									cout << "You sell your used " << item.getName();
									break;
								}else if(answer == "No" || answer == "no" || answer == "n" || answer == "N"){
									cout << "You do not sell your trusty " << item.getName() << endl;
									break;
								}else{
									cout << "Please enter yes or no" << endl;
								}
							}
						}else{
							cout << "Please enter a valid value from 1 to " << player.getItems().size() << endl;
						}
					}
				}	
			}else if (choice == "L" || choice == "l" || choice == "leave" || choice == "Leave"){
				cout << "You leave the shop" << endl;
				break; 
			}
		}
	}
}
//name to Enemy class
Enemy World::getEnemy(string name){
	for(int i = 0; i < enemies.size(); i++){
		if(enemies.at(i).getName() == name){
			return enemies.at(i);
		}
	}
}
//name to Item class
Item World::getItem(string name){
	for(int i = 0; i < items.size(); i++){
		if(items.at(i).getName() == name){
			return items.at(i);
		}
	}
	return Item();
}

bool World::rollTileEnemies(double modifier){
	Tile tile = getTile();
	//the mountain is home to the boss
	if(tile.getName() == "Mountain"){
		Enemy sorcerer = enemies.at(7);
		sorcerer.setLevel(30);
		Battle battle = Battle(player,sorcerer);
		player = battle.runBattle();
		if(player.didWinGame()){
			return winGame();
		}
	}else{
		Enemy enemy = tile.rollEnemies(modifier,hours >= 6 && hours <= 19); //roll enemies for day or night at the tile
		if(enemy.getName() != "none"){
			enemy.setLevel(((playerPos.at(1)+map.size()-playerPos.at(0)) * (0.85 + ((rand() % 30)+1)/100.0))/3);//NE to harder enemies, slightly random
			Battle battle = Battle(player,enemy);
			player = battle.runBattle();
		}
	}
	return false;
}

void World::stepTime(int time, bool isWalking){
	hours += time;
	if(isWalking){
		player.incrementStat("hydration",-7*time);
		player.incrementStat("stamina",-5*time);
	}else{//is resting
		player.incrementStat("stamina",7*time);
		player.incrementStat("hydration",-2*time);
		player.incrementStat("hp",(player.getStat("maxHp")/10)*time);
	}
	while(hours >= 24){
		days += 1;
		hours -= 24;
	}
}

int World::getHours(){
	return hours;
}

int World::getDays(){
	return days;
}

Tile World::getTile(){
	return map.at(playerPos.at(0)).at(playerPos.at(1));
}

void World::printMapKey(){
	for(int i = 0; i < tiles.size(); i++){
		cout << tiles.at(i).getIcon() << " - " << tiles.at(i).getName() << endl;
	}
	cout << ". - Not Visible" << endl;
}

bool World::winGame(){
	cout << "You won the game!" << endl;
	cout << endl;
	cout << "Highscores: " << endl;
	ifstream in;
	vector<vector<string>> gameWinners;
	//Start time was on day 1 hour 8, so get only the change in time from start to finish
	if(hours < 8){
		days -= 2;
		hours -= 8;
	}else{
		days -= 1;
		hours -= 8;
	}
	vector<string> winVector = {player.getName(),to_string(days),to_string(hours)};
    in.open("highscores.txt");
    if (in.is_open()){
        string line = "";
        while(getline(in,line)){// in form "1. name <days> days and <hours> hours
            vector<string> gameWinner;
            vector<string> temp;
            temp = split(line,' ');
            gameWinner.push_back(temp.at(1));//name
            gameWinner.push_back(temp.at(2));//days
            gameWinner.push_back(temp.at(5));//hours
            gameWinners.push_back(gameWinner);
        }
        in.close(); 
    }else{
       cout << "No past winners" << endl;
    }
    bool inHighScores = false;
    //Put player in the right slot
    for(int i = 0; i<gameWinners.size(); i++){
		vector<string> gameWinner = gameWinners.at(i);
		if(days < stoi(gameWinner.at(1)) || (days == stoi(gameWinner.at(1)) && hours <= stoi(gameWinner.at(2)))){
			gameWinners.insert(gameWinners.begin() + i,winVector);
			inHighScores = true;
			break;
		}
	}
	//add player if not already added
	if(!inHighScores){
		gameWinners.push_back(winVector);
	}
	//overwrite file with new board
	//new file is always longer so overwrite is always complete
	ofstream out;
	out.open("highscores.txt");
    if (out.is_open()){
		for(int i = 0; i<gameWinners.size(); i++){
			vector<string> winner = gameWinners.at(i);
			out << i+1 << ". " << winner.at(0) << " " << winner.at(1) << " days and " << winner.at(2) << " hours" << endl;
			cout << i+1 << ". " << winner.at(0) << " " << winner.at(1) << " days and " << winner.at(2) << " hours" << endl;
		}
		out.close();
    }else{
        cout << "error" << endl;
    }
    cout << endl;
    
	string response;
	while(true){
		cout << "Would you like to keep playing?" << endl;
		cin >> response;
		if(response == "yes" || response == "Yes" || response == "Y" || response == "y"){
			return false; 
		}else if(response == "no" || response == "No" || response == "N" || response == "n"){
			return true;
		}else{
			cout << "Please answer yes or no" << endl;
		}
	}
}

void World::inventoryMenu(){
	cout << endl;
	cout << "Gold: " << player.getStat("money") << endl;
	cout << "Bag Space Used: " << player.getTotalCarryWeight() << "/" << player.getStat("carryCap") << endl << endl;
	bool completelyDone = false; //stay in inventory until user cancels all the way out
	while(!completelyDone){
		bool done = false;
		player.printItems();
		player.printEquippedItems();
		cout << endl;
		cout << "\n| E - equip item | U - use item | D - drop item | X - unequip item | \n(C to cancel)" << endl;
		string itemAction;
		cin >> itemAction;
		if(itemAction == "E" || itemAction == "e" || itemAction == "Equip" || itemAction == "equip"){
			if(player.getItems().size() == 0){
				cout << "You have no items to equip" << endl;
				done = true;
			}else{
				string itemNum;
				bool validInput = false;
				while(!done){
					cout << "Type the item number of the item you want to equip. (C to cancel)" << endl;
					cin >> itemNum;
					if(itemNum == "C" || itemNum == "c" || itemNum == "cancel" || itemNum == "Cancel"){
						done = true;
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
						Item item = player.getItems().at(stoi(itemNum)-1);
						if(item.isEquippable()){
							player.equipItem(item.getName());
							done = true;
						}else{
							cout << "You can't equip the " << item.getName() << endl;
						}
					}else{
						cout << "Please enter a valid value from 1 to " << player.getItems().size() << endl;
					}
				}
			}
		}else if(itemAction == "U" || itemAction == "u" || itemAction == "use" || itemAction == "Use"){
			if(player.getItems().size() == 0){
				cout << "You have no items to use" << endl;
			}
			string itemNum;
			bool validInput = false;
			while(!validInput){
				cout << "Type the item number of the item you want to use. (C to cancel)" << endl;
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
					}else if(player.getItems().at(stoi(itemNum)-1).getName() == "water_bottle"){//used water bottle becomes empty
						player.useWaterBottle(getItem("empty_water_bottle"));
						done = true;
					}else if(player.getItems().at(stoi(itemNum)-1).getName() == "empty_water_bottle"){//empty water bottle can be filled at a river
						player.fillWaterBottle(getItem("water_bottle"),getTile());
						done = true;
					}else{
						player.useItem(player.getItems().at(stoi(itemNum)-1).getName());
						done = true;
					}
				}else{
					cout << "Please enter a valid value from 1 to " << player.getItems().size() << endl;
				}
			}
		}else if(itemAction == "D" || itemAction == "d" || itemAction == "Drop" || itemAction == "drop"){
			if(player.getItems().size() == 0){
				cout << "You have no items to drop" << endl;
			}
			string itemNum;
			bool validInput = false;
			while(!validInput){
				cout << "Type the item number of the item you want to drop. (C to cancel)" << endl;
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
					player.dropItem(player.getItems().at(stoi(itemNum)-1).getName());
					done = true;
				}else{
					cout << "Please enter a valid value from 1 to " << player.getItems().size() << endl;
				}
			}
		}else if(itemAction == "X" || itemAction == "x" || itemAction == "Unequip" || itemAction == "unequip"){
			bool areItems = false;
			for(int i = 0; i<player.getEquippedItems().size(); i++){
				if(!(player.getEquippedItems().at(i).getName() == "")){
					areItems = true;
				}
			}
			if(!areItems){
				cout << "You have no items to unequip" << endl;
			}else{
				string itemNum;
				bool validInput = false;
				while(!done){
					cout << "Type the position of the item you want to unequip. (C to cancel)" << endl;
					cin >> itemNum;
					int pos = -1;
					if(itemNum == "C" || itemNum == "c" || itemNum == "cancel" || itemNum == "Cancel"){
						break;
					}else if(itemNum == "H" || itemNum == "h" || itemNum == "Head" || itemNum == "head" || itemNum == "helmet" || itemNum == "Helmet" || itemNum == "Helm" || itemNum == "helm"){
						pos = 0;
					}else if(itemNum == "Chest" || itemNum == "chest" || itemNum == "Chestplate" || itemNum == "chestplate" || itemNum == "ChestPlate"){
						pos = 1;
					}else if(itemNum == "Legs" || itemNum == "legs" || itemNum == "Leggings" || itemNum == "leggings" || itemNum == "Pants" || itemNum == "pants"){
						pos = 2;
					}else if(itemNum == "Sheild" || itemNum == "sheild"){
						pos = 3;
					}else if(itemNum == "Sword" || itemNum == "sword" || itemNum == "S" || itemNum == "s" || itemNum == "weapon" || itemNum == "Weapon"){
						pos = 4;
					}else{
						cout << "Your input could not be understood" << endl;
					}
					if(pos >= 0 && pos <= 4){
						player.unequipItem(pos);
						done = true;
					}

				}
			}
		}else if(itemAction == "C" || itemAction == "c" || itemAction == "Cancel" || itemAction == "cancel"){
			completelyDone = true;
		}else{
			cout << "Your input could not be understood" << endl;
		}
	}
}

