#include "Weapon.h"
#include "Print.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>

Weapon::Weapon() {}
Weapon::Weapon(std::string name, float weight, int price, int damage, int range, int speed) :
	Item(name, weight, price),
	damage(damage), range(range),
	speed(speed) {}

void Weapon::display() {
	basicDisplay();
	std::cout << "\n Statistics:" << std::endl;
	Print::stats(" Damage           ", damage);
	Print::stats(" Range            ", range);
	Print::stats(" Speed            ", speed);
	std::cout << std::endl;
}

void Weapon::load(std::vector <Weapon> *v) {
	std::ifstream infile;
	infile.open("weapons");
	if (infile.is_open()){
		std::string name;
		float weight;
		int price, damage, range, speed;
		while (getline(infile, name)){
			infile >> weight >> price >> damage >> range >> speed;
			Weapon temp(name, weight, price, damage, range, speed);
			v->push_back(temp);
			getline(infile, name);
		}
		infile.close();
	}
}

void Weapon::save() {
	if (name == "") throw NoNameException();
	else {
		std::vector <Weapon> v;
		load(&v);
		std::ofstream outfile("weapons");
		for (int i = 0; i < v.size(); i++) {
			outfile << v[i].name << std::endl;
			outfile << v[i].weight << std::endl;
			outfile << v[i].price << std::endl;
			outfile << v[i].damage << std::endl;
			outfile << v[i].range << std::endl;
			outfile << v[i].speed << std::endl;
		}
		outfile << name << std::endl;
		outfile << weight << std::endl;
		outfile << price << std::endl;
		outfile << damage << std::endl;
		outfile << range << std::endl;
		outfile << speed;
		outfile.close();
	}
}

int Weapon::getDamage() {
	return damage;
}

int Weapon::getRange() {
	return range;
}

int Weapon::getSpeed() {
	return speed;
}
