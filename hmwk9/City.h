#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

class City{
    private:
        string name;
        double priceMult;
        vector<Item> itemsAvailable;
    public:
        City();
        City(string name1, double priceMult1, vector<Item> itemsAvailable1);
        string getName();
        void setName(string name1);
        double getPriceMult();
        void setPriceMult(double value);
        vector<Item> getItemsAvailable();
        void setItemsAvailable(vector<Item> items1);
        void printItemsAvailable();
        void setPrices();
};
