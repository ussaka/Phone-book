/*
 * C++ Project Assignment 7. "Phonebook" by Kasperi Kiviluoma
 */

#include <string>

#ifndef PROJECT_PERSON_H
#define PROJECT_PERSON_H

class Person {
	friend class Phonebook; //Make private members available to the phonebook
	friend std::ostream& operator<<(std::ostream& out, const Person& p); //Print person

public:
	Person(std::string _name, std::string _email, std::string _telephone_number, std::string _city, bool _relative);

private:
	std::string name;
	std::string email;
	std::string telephone_number;
	std::string city;
	bool relative;
};

#endif //PROJECT_PERSON_H

