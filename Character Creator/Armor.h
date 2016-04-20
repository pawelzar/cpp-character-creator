#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"
#include <vector>

class Armor : public Item {
private:
	int defense;
	int magic_resistance;
public:
	Armor();
	Armor(std::string name, float weight, int price, int defense, int magic_resistance);

	void display();
	static void load(std::vector<Armor> *v);
	void save();
	int getDefense();
	int getMagicResistance();
};

#endif  // ARMOR_H
