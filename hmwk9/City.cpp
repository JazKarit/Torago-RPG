#include <iostream>
#include <iomanip>
#include "Item.h"
#include "City.h"
using namespace std;

City::City(){
    name = "";
    priceMult = 1;
}
City::City(string name1, double priceMult1, vector<Item> itemsAvailable1){
    name = name1;
    priceMult = priceMult1;
    itemsAvailable = itemsAvailable1;
}
string City::getName(){
    return name;
}
void City::setName(string name1){
	name = name1;
}
double City::getPriceMult(){
    return priceMult;
}
void City::setPriceMult(double value){
	priceMult = value;
}
vector<Item> City::getItemsAvailable(){
    return itemsAvailable;
}
void City::setItemsAvailable(vector<Item> items1){
	itemsAvailable = items1;
}
void City::printItemsAvailable(){
	cout << "Items Available in " << getName() << ":" << endl;
	for(int i = 0; i < itemsAvailable.size(); i++){
		cout << i+1 << ". " << itemsAvailable.at(i).getName() << " " << itemsAvailable.at(i).getBaseCost() << endl;
	}
}
void City::setPrices(){
	for(int i=0; i < itemsAvailable.size(); i++){
		itemsAvailable.at(i).setBaseCost(itemsAvailable.at(i).getBaseCost() *  priceMult);
	}
}
