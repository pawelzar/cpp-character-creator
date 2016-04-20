#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class NoNameException : public std::exception {
public:
	static std::string getMessage() {
		return "\n\n Must have a name.";
	}
};

class TooExpensiveException : public std::exception{
public:
	static std::string getMessage() {
		return "\n\n You don't have enough money to buy this item.";
	}
};

class NoFileException : public std::exception {
public:
	static std::string getMessage() {
		return "\n\n File doesn't exist.";
	}
};

#endif  // EXCEPTIONS_H
