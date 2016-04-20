#ifndef CHARACTER_H
#define CHARACTER_H

#include "Weapon.h"
#include "Armor.h"

class Knight;
class Wizard;
class Thief;

class Character {
protected:
	Armor armor;
	Weapon weapon;
	std::string name, gender, skin, type;
	int money, strength, magic;
	float height, weight;

public:
	Character();
	Character(std::string name, std::string gender, std::string skin, float height, float weight, int money);

	static Character load(std::string name);
	void loadArmor();
	void loadWeapon();
	void save();
	void display();
	void displayItems();
	void addArmor(Armor armor);
	void addWeapon(Weapon weapon);
	int getMoney();

	operator Knight();
	operator Wizard();
	operator Thief();

	static std::string readType(std::string name);
};

class Knight : public Character {
public:
	Knight(std::string name, std::string gender, std::string skin, float height, float weight, int money);
};

class Wizard : public Character {
public:
	Wizard(std::string name, std::string gender, std::string skin, float height, float weight, int money);
};

class Thief : public Character {
public:
	Thief(std::string name, std::string gender, std::string skin, float height, float weight, int money);
};

#endif // CHARACTER_H
