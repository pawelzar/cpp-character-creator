#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
protected:
	std::string name;
	int price;
	float weight;
	void basicDisplay() const;

public:
	virtual ~Item() {}

	Item();
	Item(std::string name, float weight, int price);

	virtual void display() = 0;

	std::string getName();
	int getPrice();
	float getWeight();
};

#endif  // ITEM_H
