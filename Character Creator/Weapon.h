#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include <vector>

class Weapon : public Item {
private:
	int damage;
	int range;
	int speed;
public:
	Weapon();
	Weapon(std::string name, float weight, int price, int damage, int range, int speed);

	void display();
	static void load(std::vector<Weapon> *v);
	void save();
	int getDamage();
	int getRange();
	int getSpeed();
};

#endif  // WEAPON_H
