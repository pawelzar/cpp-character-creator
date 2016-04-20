#include "Item.h"
#include <iostream>

void Item::basicDisplay() const {
	std::cout << "\n " << name << std::endl;
	std::cout << " Price: " << price;
	std::cout << "    Weight: " << weight << std::endl;
}

Item::Item() : price(0), weight(0) {}

Item::Item(std::string name, float weight, int price) :
	name(name), price(price), weight(weight) {}

std::string Item::getName() {
	return name;
}

int Item::getPrice() {
	return price;
}

float Item::getWeight() {
	return weight;
}
