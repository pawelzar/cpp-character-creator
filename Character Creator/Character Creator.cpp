#include <conio.h>

#include "Settings.h"
#include "Menu.h"


int main() {
	Menu menu;
	int current = 0;
	bool esc = 0;

	while (!esc) {
		menu.MainMenu(current);
		switch (_getch()) {
		case ESCAPE:
			esc = 1;
			break;
		case UP:
			if (current > 0) current -= 1;
			break;
		case DOWN:
			if (current < 7) current += 1;
			break;
		case ENTER:
			switch (current) {
			case 0:
				menu.CreateCharacter();
				break;
			case 1:
				menu.LoadCharacter();
				break;
			case 2:
				menu.CreateArmor();
				break;
			case 3:
				menu.LoadArmors();
				break;
			case 4:
				menu.CreateWeapon();
				break;
			case 5:
				menu.LoadWeapons();
				break;
			case 6:
				menu.About();
				break;
			case 7:
				esc = 1;
				break;
			}
			break;
		}
	}
	return 0;
}
