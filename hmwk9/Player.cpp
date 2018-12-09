#include <iostream>
#include <iomanip>
#include "Player.h"
#include "Item.h"
using namespace std;


Player::Player(){
    name = "";
    maxHp = 0;
    hp = 0;
    atk = 0;
    stamina = 0;
    hydration = 0;
    def = 0;
    money = 0;
    carryCap = 0;
    lvl = 1;
    exp = 0;
    accuracy = 0.7;
    Item a = Item();
    equippedItems = {a,a,a,a,a};
    wonGame = false;
}
Player::Player(string name1, int hp1, int atk1, int stamina1, int hydration1, int def1, int money1, int carryCap1){
    name = name1;
    maxHp = 0;
    hp = hp1;
    atk = atk1;
    stamina = stamina1;
    hydration = hydration1;
    def = def1;
    money = money1;
    carryCap = carryCap1;
    lvl = 1;
    exp = 0;
    accuracy = 0.7;
    Item a = Item();
    equippedItems = {a,a,a,a,a};
    wonGame = false;
}

// int Player::getHp(){
//     return hp;
// }
// int Player::getStamina(){
//     return stamina;
// }
// int Player::getHydration(){
//     return hydration;
// }
// int Player::getAtk(){
//     return atk;
// }
// int Player::getDef(){
//     return def;
// }
// int Player::getMoney(){
//     return money;
// }
// int Player::getNumItems(){
//     return items.size();
// }
string Player::getName(){
    return name;
}
void Player::setName(string newName){
    name = newName;
}
vector<Item> Player::getItems(){
    return items;
}
vector<Item> Player::getEquippedItems(){
    return equippedItems;
}
// int Player::getCarryCap(){
//     return carryCap;
// }
// int Player::getExp(){
//     return exp;
// }
// int Player::getLvl(){
//     return lvl;
// }

int Player::getStat(string stat){
    if(stat == "maxHp"){
        return maxHp;
    }else if(stat == "hp"){
        return hp;
    }else if(stat == "atk"){
        return atk;
    }else if(stat == "def"){
       return def;
    }else if(stat == "money"){
        return money;
    }else if(stat == "stamina"){
        return stamina;
    }else if(stat == "hydration"){
        return hydration;
    }else if(stat == "exp"){
        return exp;
    }else if(stat == "lvl"){
        return lvl;
    }else if(stat == "numItems"){
        return items.size();
    }else if(stat == "carryCap"){
        return carryCap;
    }else{
        return -1;
    }
}

double Player::getAccuracy(){
	return accuracy;
}

void Player::printStats(){
	cout << "Hp: " << getStat("hp") << "/" << getStat("maxHp") << endl;
	cout << "Atk: " << getStat("atk") << endl;
	cout << "Def: " << getStat("def") << endl;
	cout << "Stamina: " << getStat("stamina") << endl;
	cout << "Hydration: " << getStat("hydration") << endl;
	cout << "Experience: " << getStat("exp") << endl;
	cout << "Level: " << getStat("lvl") << endl;
}


bool Player::setStat(string stat, int value){
    if(stat == "maxHp"){
        maxHp = value;
    }else if(stat == "hp"){
        hp = value;
    }else if(stat == "atk"){
        atk = value;
    }else if(stat == "def"){
        def = value;
    }else if(stat == "money"){
        money = value;
    }else if(stat == "stamina"){
        stamina = value;
    }else if(stat == "hydration"){
        hydration = value;
    }else if(stat == "carryCap"){
        carryCap = value;
    }else{
        return false;
    }
}

// bool Player::incHp(int value){
//     hp += value;
// }
// bool Player::incStamina(int value){
//     stamina += value;
// }
// bool Player::incHydration(int value){
//     hydration += value;
// }
// bool Player::incMoney(int value){
//     money += value;
// }
// bool Player::incExp(int value){
//     exp += value;
// }

//make sure stats don't go negative or over their cap
bool Player::incrementStat(string stat, int value){
    if(stat == "maxHp"){
        maxHp += value;
        return true;
    }else if(stat == "exp"){
		exp += value;
		if(tryLvlUp()){
			cout << getName() << " leveled up!" << endl;
			cout << "Your new stats are:" << endl;
			printStats();  
		}
		
	}else if(stat == "hp"){
        if(hp + value >= maxHp){
			hp = maxHp;
		}else if(hp + value <= 0){
			hp = 0;
		}else{
			hp += value;
		}
        return true;
    }else if(stat == "atk"){
        atk += value;
        return true;
    }else if(stat == "def"){
        def += value;
        return true;
    }else if(stat == "money"){
        money += value;
        return true;
    }else if(stat == "stamina"){
        if(stamina + value >= 100){
			stamina = 100;
		}else if(stamina + value <= 0){
			stamina = 0;
		}else{
			stamina += value;
		}
        return true;
    }else if(stat == "hydration"){
        if(hydration + value >= 100){
			hydration = 100;
		}else if(hydration + value <= 0){
			hydration = 0;
		}else{
			hydration += value;
		}
        return true;
    }else{
        return false;
    }
}

//Print each item and their affect when used or equipped
void Player::printItems(){
    cout << "Items: "; 
    if(items.size() == 0){
		cout << "None" << endl;
	}else{
		cout << endl;
		for(int i = 0; i < items.size(); i++){
			Item item = items.at(i);
			cout << i+1 << ". " << item.getName() << " " << item.getStatModified() << "+" << item.getStatModifier() << " ";
			if(item.isEquippable()){
				cout << "when equipped" << endl;
			}else{
				cout << "when used" << endl;
			}
			
		}
	}
	cout << endl;
}

void Player::printEquippedItems(){
    cout << "EquippedItems: "; 
    bool areItems = false;
    for(int i = 0; i < equippedItems.size(); i++){
		if(equippedItems.at(i).getName() != ""){
			areItems = true;
		}
	}
    if(!areItems){
		cout << "None" << endl;
	}else{
		cout << endl;
		for(int i = 0; i < equippedItems.size(); i++){
			Item item = equippedItems.at(i);
			switch(i){
				case 0:
					cout << "Head: ";
					break;
				case 1:	
					cout << "Chest: ";
					break;
				case 2:
					cout << "Legs: ";
					break;
				case 3:
					cout << "Sheild: ";
					break;
				case 4:
					cout << "Sword: ";
					break;
			}
			if(item.getName() == ""){
				cout << "none" << endl;
			}else{
				cout << item.getName() << " " << item.getStatModified() << "+" << item.getStatModifier() << " " << endl;
			}
		}
	}
}


int Player::getItemIndex(string item){
    for(int i=0;i<items.size();i++){
        if(item == items[i].getName()){
            return i;
        }
    }
    return -1;
}

bool Player::useItem(string item){
    int itemIndex = getItemIndex(item);
    if(itemIndex == -1){
        return false;
    }else if (items[itemIndex].isEquippable()){//only nonEquippable items can be used
        return false;
    }else{
        bool flag = incrementStat(items[itemIndex].getStatModified(),items[itemIndex].getStatModifier());
        dropItem(item,true);
        return flag;
    }
}

//Gets turned into an empty water bottle
bool Player::useWaterBottle(Item emptyBottle){
    int itemIndex = getItemIndex("water_bottle");
    if(itemIndex == -1){
        return false;
    }else{
        bool flag = incrementStat(items[itemIndex].getStatModified(),items[itemIndex].getStatModifier());
        dropItem("water_bottle",true);
        addItem(emptyBottle);
        return flag;
    }
}

//Gets turned into a full water bottle
bool Player::fillWaterBottle(Item waterBottle, Tile tile){
    int itemIndex = getItemIndex("empty_water_bottle");
    if(itemIndex == -1){
        return false;
    }else if(tile.getName() == "River"){
        dropItem("empty_water_bottle",true);
        addItem(waterBottle);
        return true;
    }else{
		cout << "You can only fill your water bottle at the river" << endl;
		return false;
	}
}

bool Player::equipItem(string item){
    int itemIndex = getItemIndex(item);
    if(itemIndex == -1){
        return false;
    }else{
		Item item = items.at(itemIndex);
		int equipPos = item.getEquipType();
		if(equippedItems.at(equipPos).getName() != ""){//Item is equipped at that position: unequip it to item's position
			items[itemIndex] = equippedItems.at(equipPos);
			cout << equippedItems.at(equipPos).getName() << " was unequipped and " << item.getName() << " was equipped" << endl;
		}else{//no item equipped: erase item
			items.erase(items.begin() + itemIndex);
			cout << item.getName() << " was equipped" << endl;
		}
		equippedItems[equipPos] = item;
		return true;
    }
}
bool Player::unequipItem(int equipPos){
	Item item = equippedItems.at(equipPos);
	if(item.getName() != ""){//item will have name "" if no real item is equipped
		items.push_back(item);
		Item a = Item();
		equippedItems[equipPos] = a;
		cout << item.getName() << " was unequipped" << endl;
	}else{
		cout << "There's nothing to unequip there" << endl;
	}
	
}

bool Player::addItem(Item item){
    if(getTotalCarryWeight() + item.getWeight() <= carryCap){
        items.push_back(item);
        return true;
    }else{
        return false;
    }
}

bool Player::dropItem(string item){
    int itemIndex = getItemIndex(item);
    if(itemIndex == -1){
		cout << "Could not find " << item << endl;
        return false;
    }else{
		cout << item << " was dropped"<< endl;
        items.erase(items.begin() + itemIndex);
        return true;
    }
}

//don't display "was dropped" if it was used
bool Player::dropItem(string item, bool wasUsed){
    int itemIndex = getItemIndex(item);
    if(itemIndex == -1){
		cout << "Could not find " << item << endl;
        return false;
    }else{
		if(wasUsed){
			cout << item << " was used" << endl;
		}else{
			cout << item << " was dropped"<< endl;
		}
        items.erase(items.begin() + itemIndex);
        return true;
    }
}
bool Player::tryLvlUp(){
    if(exp >= 100 && lvl < 40){//level cap 40
        exp = exp % 100;//should always be under 200 when called
        lvl += 1;
        //semi random stat increases
        maxHp += (2 + (rand() % 3));
        hp = maxHp;
        def += (0 + (rand() % 3));
        atk += (1 + (rand() % 3));
        return true;
    }else{
        return false;
    }
}
double Player::getTotalCarryWeight(){
    double totalWeight = 0;
    for(int i = 0; i<items.size(); i++){
        totalWeight += items.at(i).getWeight();
    }
    for(int i = 0; i<equippedItems.size();i++){
        totalWeight += equippedItems.at(i).getWeight();
    }
    return totalWeight;
}
//get atk mod from equipped items
int Player::getAtkMod(){
    int atkMod = 0;
    for(int i=0; i<equippedItems.size(); i++){
        if(equippedItems.at(i).getStatModified() == "atk"){
            atkMod += equippedItems.at(i).getStatModifier();  
        }
    }
    return atkMod;
}
//get atk mod from equipped items
int Player::getDefMod(){
    int defMod = 0;
    for(int i=0; i<equippedItems.size(); i++){
        if(equippedItems.at(i).getStatModified() == "def"){
            defMod += equippedItems.at(i).getStatModifier();  
        }
    }
    return defMod;
}

int Player::getTotalAtk(){
	return (getStat("atk") + getAtkMod());
}

int Player::getTotalDef(){
	return (getStat("def") + getDefMod());
}

void Player::winGame(){
	wonGame = true;
}
bool Player::didWinGame(){
	return wonGame;
}
