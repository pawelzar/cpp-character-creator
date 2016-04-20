#include <conio.h>
#include "Move.h"
#include "Settings.h"

bool Move::up_and_down(int *current, int min, int max) {
	switch (_getch()) {
	case BACKSPACE:
	case ENTER:
		return 0;
	case UP:
		if (*current>min) *current -= 1;
		break;
	case DOWN:
		if (*current<max) *current += 1;
		break;
	}
	return 1;
}

bool Move::change_value(float *current, float min, float max, float value) {
	switch (_getch()) {
	case ENTER:
		return 0;
	case UP:
		if (*current<max) *current += value;
		break;
	case DOWN:
		if (*current>min) *current -= value;
		break;
	}
	*current = int(*current * 100 + 0.5) / 100.0;
	return 1;
}
