#include "Armor.h"
#include "Item.h"
#include "Exceptions.h"
#include "Print.h"
#include <iostream>
#include <fstream>
#include <vector>


Armor::Armor() : defense(0), magic_resistance(0) {}

Armor::Armor(std::string name, float weight, int price, int defense, int magic_resistance) :
	Item(name, weight, price),
	defense(defense),
	magic_resistance(magic_resistance) {}

void Armor::display() {
	basicDisplay();
	std::cout << "\n Statistics:" << std::endl;
	Print::stats(" Defense          ", defense);
	Print::stats(" Magic resistance ", magic_resistance);
	std::cout << std::endl;
}

void Armor::load(std::vector<Armor> *v) {
	std::ifstream infile;
	infile.open("armors");
	if (infile.is_open()) {
		std::string name;
		float weight;
		int price, defense, magic_resistance;
		while (getline(infile, name)){
			infile >> weight >> price >> defense >> magic_resistance;
			Armor temp(name, weight, price, defense, magic_resistance);
			v->push_back(temp);
			getline(infile, name);
		}
		infile.close();
	}
}

void Armor::save() {
	if (name == "") throw NoNameException();
	else {
		std::vector <Armor> v;
		load(&v);
		std::ofstream outfile("armors");
		for (int i = 0; i < v.size(); i++) {
			outfile << v[i].name << std::endl;
			outfile << v[i].weight << std::endl;
			outfile << v[i].price << std::endl;
			outfile << v[i].defense << std::endl;
			outfile << v[i].magic_resistance << std::endl;
		}
		outfile << name << std::endl;
		outfile << weight << std::endl;
		outfile << price << std::endl;
		outfile << defense << std::endl;
		outfile << magic_resistance;
		outfile.close();
	}
}

int Armor::getDefense() {
	return defense;
}

int Armor::getMagicResistance() {
	return magic_resistance;
}
