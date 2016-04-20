#include "Menu.h"
#include "Settings.h"
#include "Move.h"
#include "Character.h"
#include "Exceptions.h"
#include "Print.h"
#include <conio.h>

void Menu::color(std::string something, int color, bool ok){
	if (ok) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	std::cout << something;
	if (ok) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}
void Menu::wait(std::string comment) {
	std::cout << comment;
	_getch();
}

void Menu::MainMenu(int current) {
	system("cls");
	std::cout << "\n MENU\n";
	color(" - Create new character\n", CYAN, current == 0);
	color(" - Load character\n", CYAN, current == 1);
	color(" - Create new armor\n", CYAN, current == 2);
	color(" - Display armors\n", CYAN, current == 3);
	color(" - Create new weapon\n", CYAN, current == 4);
	color(" - Display weapons\n", CYAN, current == 5);
	color(" - About\n", CYAN, current == 6);
	color(" - QUIT", CYAN, current == 7);
}

void Menu::CharacterMenu(int current, std::string type, std::string name,
	std::string skin, std::string gender, float height, float weight) {
	system("cls");
	std::cout << "\n CREATION CENTER\n\n";
	color(" TYPE: ", CYAN, current == 0);
	color(type, BLUE, current == 0);
	color("\n\n Name: ", CYAN, current == 1);
	std::cout << name;
	color("\n Gender: ", CYAN, current == 2);
	color(gender, BLUE, current == 2);
	color("\n Skin: ", CYAN, current == 3);
	color(skin, BLUE, current == 3);
	color("\n Height: ", CYAN, current == 4);
	std::cout << height << " m";
	color("\n Weight: ", CYAN, current == 5);
	std::cout << weight << " kg";
	color("\n\n Next step.", CYAN, current == 6);
}

void Menu::CreateCharacter() {
	std::string name;
	std::string gender[3] = { "Male", "Female", "Other" };
	std::string skin[5] = { "White", "Black", "Yellow", "Green", "Blue" };
	std::string type[3] = { "KNIGHT", "WIZARD", "THIEF" };
	float height = 1.8, weight = 80.0;
	int current = 0, which_skin = 0, which_gender = 0, which_type = 0;
	bool esc = 0;
	bool quit = 0;

	while (!esc) {
		CharacterMenu(current, type[which_type], name, skin[int(which_skin)],
			gender[int(which_gender)], height, weight);
		switch (_getch()) {
		case UP:
			if (current > 0) current -= 1;
			break;
		case DOWN:
			if (current < 6) current += 1;
			break;
		case ENTER:
			switch (current) {
			case 0:
				do CharacterMenu(current, type[which_type], name, skin[int(which_skin)],
					gender[int(which_gender)], height, weight);
				while (Move::up_and_down(&which_type, 0, 2));
				break;
			case 1:
				system("cls");
				std::cout << "\n CREATION CENTER\n\n";
				color(" Name: ", CYAN, current == 0);
				getline(std::cin, name);
				break;
			case 2:
				do CharacterMenu(current, type[which_type], name, skin[int(which_skin)],
					gender[int(which_gender)], height, weight);
				while (Move::up_and_down(&which_gender, 0, 2));
				break;
			case 3:
				do CharacterMenu(current, type[which_type], name, skin[int(which_skin)],
					gender[int(which_gender)], height, weight);
				while (Move::up_and_down(&which_skin, 0, 4));
				break;
			case 4:
				do CharacterMenu(current, type[which_type], name, skin[int(which_skin)],
					gender[int(which_gender)], height, weight);
				while (Move::change_value(&height, 0.5, 5, 0.01));
				break;
			case 5:
				do CharacterMenu(current, type[which_type], name, skin[int(which_skin)],
					gender[int(which_gender)], height, weight);
				while (Move::change_value(&weight, 50, 150, 0.1));
				break;
			case 6:
				try {
					Character character(name, gender[which_gender],
						skin[which_skin], height, weight, 5000);
					character.save();
					esc = 1;
				}
				catch (NoNameException e) {
					std::cout << e.getMessage();
					wait("");
				}
			}
			break;
		case BACKSPACE:
			esc = 1;
			quit = 1;
		}
	}
	if (!quit) {
		Character character;
		if (which_type == 0)
			character = Knight(name, gender[which_gender], skin[which_skin], height, weight, 4000);
		if (which_type == 1)
			character = Wizard(name, gender[which_gender], skin[which_skin], height, weight, 7000);
		if (which_type == 2)
			character = Thief(name, gender[which_gender], skin[which_skin], height, weight, 9000);

		std::vector <Armor> armors;
		Armor::load(&armors);
		current = 0;
		esc = 0;

		while (!esc) {
			try {
				do {
					system("cls");
					std::cout << "\n CREATION CENTER"
						<< "       Money: "
						<< character.getMoney() - armors[current].getPrice()
						<< "\n\n"
						<< " Choose armor:\n\n";
					armors[current].display();
				} while (Move::up_and_down(&current, 0, armors.size() - 1));

				character.addArmor(armors[current]);
				esc = 1;

			}
			catch (TooExpensiveException e) {
				std::cout << e.getMessage();
				wait("");
			}
		}

		std::vector <Weapon> weapons;
		Weapon::load(&weapons);
		current = 0;
		esc = 0;

		while (!esc) {
			try {
				do {
					system("cls");
					std::cout << "\n CREATION CENTER"
						<< "       Money: "
						<< character.getMoney() - weapons[current].getPrice()
						<< "\n\n"
						<< " Choose weapon:\n\n";
					weapons[current].display();
				} while (Move::up_and_down(&current, 0, weapons.size() - 1));

				character.addWeapon(weapons[current]);
				esc = 1;

			}
			catch (TooExpensiveException e) {
				std::cout << e.getMessage();
				wait("");
			}
		}

		system("cls");
		std::cout << "\n Your character has been created.\n\n";
		character.save();
		character.display();
		character.displayItems();

		while (_getch() != ENTER) {}
	}
}

void Menu::LoadCharacter() {
	std::string name, type;

	system("cls");
	std::cout << "\n Enter name: ";
	getline(std::cin, name);

	try {
		type = Character::readType(name);
		Character character = Character::load(name);
		character.loadArmor();
		character.loadWeapon();

		system("cls");
		if (type == "KNIGHT") Knight(character).display();
		if (type == "WIZARD") Wizard(character).display();
		if (type == "THIEF") Thief(character).display();
		character.displayItems();

	}
	catch (NoFileException e) {
		std::cout << e.getMessage();
	}

	while (_getch() != BACKSPACE) {}
}

void Menu::ArmorMenu(int current, std::string name, float weight,
	float price, float defense, float magic_resistance) {
	system("cls");
	std::cout << "\n CREATION CENTER\n\n";
	color(" Name: ", CYAN, current == 0);
	std::cout << name;
	color("\n Weight: ", CYAN, current == 1);
	std::cout << weight << " kg";
	color("\n Price: ", CYAN, current == 2);
	std::cout << price << " $";
	color("\n Defense:           ", CYAN, current == 3);
	Print::stats("", defense);
	color(" Magic resistance:  ", CYAN, current == 4);
	Print::stats("", magic_resistance);
	color("\n\n Save.", CYAN, current == 5);
}

void Menu::CreateArmor() {
	std::string name;
	float weight = 5, price = 200, defense = 10, magic_resistance = 10;
	int current = 0;
	bool esc = 0;

	while (!esc) {
		ArmorMenu(current, name, weight, price, defense, magic_resistance);
		switch (_getch()) {
		case UP:
			if (current > 0) current -= 1;
			break;
		case DOWN:
			if (current < 5) current += 1;
			break;
		case ENTER:
			switch (current) {
			case 0:
				system("cls");
				std::cout << "\n CREATION CENTER\n\n";
				color(" Name: ", CYAN, current == 0);
				getline(std::cin, name);
				break;
			case 1:
				do ArmorMenu(current, name, weight, price, defense, magic_resistance);
				while (Move::change_value(&weight, 1, 30, 0.1));
				break;
			case 2:
				do ArmorMenu(current, name, weight, price, defense, magic_resistance);
				while (Move::change_value(&price, 50, 5000, 10));
				break;
			case 3:
				do ArmorMenu(current, name, weight, price, defense, magic_resistance);
				while (Move::change_value(&defense, 0, MAX_VALUE, 1));
				break;
			case 4:
				do ArmorMenu(current, name, weight, price, defense, magic_resistance);
				while (Move::change_value(&magic_resistance, 0, MAX_VALUE, 1));
				break;
			case 5:
				try {
					Armor armor(name, weight, price, int(defense), int(magic_resistance));
					armor.save();
					system("cls");
					wait("\n Armor created.");
					esc = 1;
				}
				catch (NoNameException e) {
					std::cout << e.getMessage();
					wait("");
				}
				break;
			}
			break;
		case BACKSPACE:
			esc = 1;
			break;
		}
	}
}

void Menu::WeaponMenu(int current, std::string name, float weight,
	float price, float damage, float range, float speed) {
	system("cls");
	std::cout << "\n CREATION CENTER\n\n";
	color(" Name: ", CYAN, current == 0);
	std::cout << name;
	color("\n Weight: ", CYAN, current == 1);
	std::cout << weight << " kg";
	color("\n Price: ", CYAN, current == 2);
	std::cout << price << " $";
	color("\n Damage:            ", CYAN, current == 3);
	Print::stats("", damage);
	color(" Range:             ", CYAN, current == 4);
	Print::stats("", range);
	color(" Speed:             ", CYAN, current == 5);
	Print::stats("", speed);
	color("\n\n Save.", CYAN, current == 6);
}

void Menu::CreateWeapon() {
	std::string name;
	float weight = 5, price = 200, damage = 10, range = 10, speed = 10;
	int current = 0;
	bool esc = 0;

	while (!esc) {
		WeaponMenu(current, name, weight, price, damage, range, speed);
		switch (_getch()) {
		case UP:
			if (current > 0) current -= 1;
			break;
		case DOWN:
			if (current < 6) current += 1;
			break;
		case ENTER:
			switch (current) {
			case 0:
				system("cls");
				std::cout << "\n CREATION CENTER\n\n";
				color(" Name: ", CYAN, current == 0);
				getline(std::cin, name);
				break;
			case 1:
				do WeaponMenu(current, name, weight, price, damage, range, speed);
				while (Move::change_value(&weight, 1, 30, 0.1));
				break;
			case 2:
				do WeaponMenu(current, name, weight, price, damage, range, speed);
				while (Move::change_value(&price, 50, 5000, 10));
				break;
			case 3:
				do WeaponMenu(current, name, weight, price, damage, range, speed);
				while (Move::change_value(&damage, 0, MAX_VALUE, 1));
				break;
			case 4:
				do WeaponMenu(current, name, weight, price, damage, range, speed);
				while (Move::change_value(&range, 0, MAX_VALUE, 1));
				break;
			case 5:
				do WeaponMenu(current, name, weight, price, damage, range, speed);
				while (Move::change_value(&speed, 0, MAX_VALUE, 1));
				break;
			case 6:
				try {
					Weapon weapon(name, weight, price, int(damage), int(range), int(speed));
					weapon.save();
					system("cls");
					wait("\n Weapon created.");
					esc = 1;
				}
				catch (NoNameException e) {
					std::cout << e.getMessage();
					wait("");
				}
				break;
			}
			break;
		case BACKSPACE:
			esc = 1;
			break;
		}
	}
}

void Menu::LoadArmors() {
	std::vector <Armor> armors;
	Armor::load(&armors);
	int current = 0;
	do {
		system("cls");
		armors[current].display();
	} while (Move::up_and_down(&current, 0, armors.size() - 1));
}

void Menu::LoadWeapons() {
	std::vector <Weapon> weapons;
	Weapon::load(&weapons);
	int current = 0;
	do {
		system("cls");
		weapons[current].display();
	} while (Move::up_and_down(&current, 0, weapons.size() - 1));
}

void Menu::About() {
	system("cls");
	Menu::color("\n Kreator postaci 2014.\n\n", CYAN, 1);
	std::cout << " Autor: Pawel Zarebski\n";
	while (_getch() != BACKSPACE) {}
}
