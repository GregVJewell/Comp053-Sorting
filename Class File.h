#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Products {
public:
	Products() {};

	Products(int number, int price) {
		itemNumber = number;
		itemPrice = price;
	};

	int getItemNumber() {
		return itemNumber;
	}

	int getItemPrice() {
		return itemPrice;
	}

	void printInfo() {
		cout << "Item #: " << itemNumber << " Item Price: $" << itemPrice << endl;
	}

protected:


private:
	int itemNumber;
	int itemPrice;

	int choice;
};