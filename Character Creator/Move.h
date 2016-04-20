#ifndef MOVE_H
#define MOVE_H

class Move {
public:
	static bool up_and_down(int *current, int min, int max);
	static bool change_value(float *current, float min, float max, float value);
};

#endif  // MOVE_H
