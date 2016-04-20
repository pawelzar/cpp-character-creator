#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <Windows.h>
#include "Settings.h"

class Print {
public:
	static void stats(std::string atribute, int current) {
		std::cout << atribute << ": ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
		for (int i = 0; i<current; i++) std::cout << "|";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		for (int i = current; i < MAX_VALUE; i++) std::cout << "|";
		std::cout << std::endl;
	}
};

#endif  // PRINT_H
