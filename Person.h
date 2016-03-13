#ifndef PERSON_H
#define PERSON_H

#include <iostream>

class Person {
private: 
	double height, weight;
	int num;
	static int amount;

public:
	Person(){height = weight = 0; ++amount; num = amount;}
	Person(double h, double w){height = h; weight = w; ++amount; num = amount;}

	double getHeight() const {return height;}
	double getWeight() const {return weight;}
	int getNum() const {return num;}

	friend std::ostream &operator<<(std::ostream &, const Person &);

};

int Person::amount = 0;
std::ostream &operator<<(std::ostream &os, const Person &p) { 
    return os << "Person " << p.getNum() << ": height " << p.getHeight() << ", weight " << p.getWeight();
}


#endif