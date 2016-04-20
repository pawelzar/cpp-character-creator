#ifndef MENU_H
#define MENU_H

#include <string>

class Menu {
public:
	static void color(std::string something, int color, bool ok);
	static void wait(std::string comment);

	void MainMenu(int current);

	void CharacterMenu(int current, std::string type, std::string name,
		std::string skin, std::string gender, float height, float weight);
	void CreateCharacter();
	void LoadCharacter();

	void ArmorMenu(int current, std::string name, float weight,
		float price, float defense, float magic_resistance);
	void CreateArmor();

	static void WeaponMenu(int current, std::string name, float weight,
		float price, float damage, float range, float speed);
	void CreateWeapon();

	void LoadArmors();
	void LoadWeapons();
	void About();
};

#endif  // MENU_H
