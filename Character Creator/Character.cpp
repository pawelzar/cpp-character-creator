#include "Character.h"
#include "Exceptions.h"
#include "Print.h"
#include <iostream>
#include <fstream>


Character::Character() : name("Name"), gender("gender"), skin("skin"), height(1.8), weight(80) {}
Character::Character(std::string name, std::string gender, std::string skin, float height, float weight, int money) :
	name(name),
	gender(gender),
	skin(skin),
	money(money),
	height(height),
	weight(weight) {}

Character Character::load(std::string name) {
	std::ifstream infile;
	infile.open(name.c_str());
	std::string line;
	if (infile.is_open()) {
		std::string name, gender, skin;
		float height, weight;
		int money;
		getline(infile, line);
		getline(infile, name);
		infile >> gender >> skin >> height >> weight >> money;
		infile.close();
		return Character(name, gender, skin, height, weight, money);
	}
}

void Character::loadArmor() {
	std::ifstream infile;
	infile.open(name.c_str());
	if (infile.is_open()) {
		std::string name;
		float weight;
		int price, defense, magic_resistance;
		for (int i = 0; i < 8; i++) {
			getline(infile, name);
		}
		infile >> price >> weight >> defense >> magic_resistance;
		this->armor = Armor(name, weight, price, defense, magic_resistance);
		infile.close();
	}
}

void Character::loadWeapon() {
	std::ifstream infile;
	infile.open(name.c_str());
	if (infile.is_open()) {
		std::string name;
		float weight;
		int price, damage, range, speed;
		for (int i = 0; i < 13; i++) {
			getline(infile, name);
		}
		infile >> price >> weight >> damage >> range >> speed;
		this->weapon = Weapon(name, weight, price, damage, range, speed);
		infile.close();
	}
}

void Character::save() {
	if (name == "") throw NoNameException();
	else {
		std::ofstream outfile(name.c_str());
		outfile << type << std::endl;
		outfile << name << std::endl;
		outfile << gender << std::endl;
		outfile << skin << std::endl;
		outfile << height << std::endl;
		outfile << weight << std::endl;
		outfile << money << std::endl;
		// ADD ARMOR
		outfile << armor.getName() << std::endl;
		outfile << armor.getPrice() << std::endl;
		outfile << armor.getWeight() << std::endl;
		outfile << armor.getDefense() << std::endl;
		outfile << armor.getMagicResistance() << std::endl;
		// ADD WEAPON
		outfile << weapon.getName() << std::endl;
		outfile << weapon.getPrice() << std::endl;
		outfile << weapon.getWeight() << std::endl;
		outfile << weapon.getDamage() << std::endl;
		outfile << weapon.getRange() << std::endl;
		outfile << weapon.getSpeed();
		outfile.close();
	}
}

void Character::display() {
	std::cout << "\n " << type << std::endl;
	std::cout << "\n " << name << std::endl;
	std::cout << " Gender: " << gender << std::endl;
	std::cout << " Skin: " << skin << std::endl;
	std::cout << " Height: " << height << " m    ";
	std::cout << " Weight: " << weight << " kg    ";
	std::cout << " Money: " << money << " $" << std::endl << std::endl;
	Print::stats(" Strength         ", strength);
	if (magic != 0) Print::stats(" Magic            ", magic);
	std::cout << std::endl;
}

void Character::displayItems() {
	armor.display();
	weapon.display();
}

void Character::addArmor(Armor armor) {
	this->armor = armor;
	if (money - armor.getPrice() < 0) throw TooExpensiveException();
	else money -= armor.getPrice();
}

void Character::addWeapon(Weapon weapon) {
	this->weapon = weapon;
	if (money - weapon.getPrice() < 0) throw TooExpensiveException();
	else money -= weapon.getPrice();
}

int Character::getMoney() {
	return money;
}

std::string Character::readType(std::string name) {
	std::ifstream infile;
	infile.open(name.c_str());
	std::string line;
	if (infile.is_open()){
		getline(infile, line);
		infile.close();
		return line;
	}
	else throw NoFileException();
}

Knight::Knight(std::string name, std::string gender, std::string skin, float height, float weight, int money) :
	Character(name, gender, skin, height, weight, money) {
	this->type = "KNIGHT";
	this->strength = 25;
	this->magic = 0;
}

Wizard::Wizard(std::string name, std::string gender, std::string skin, float height, float weight, int money) :
	Character(name, gender, skin, height, weight, money) {
	this->type = "WIZARD";
	this->strength = 12;
	this->magic = 28;
}

Thief::Thief(std::string name, std::string gender, std::string skin, float height, float weight, int money) :
	Character(name, gender, skin, height, weight, money) {
	this->type = "THIEF";
	this->strength = 10;
	this->magic = 0;
}

Character::operator Knight() {
	return Knight(name, gender, skin, height, weight, money);
}

Character::operator Wizard() {
	return Wizard(name, gender, skin, height, weight, money);
}

Character::operator Thief() {
	return Thief(name, gender, skin, height, weight, money);
}
