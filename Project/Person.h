/*
 * C++ Project Assignment 7. "Phonebook" by Kasperi Kiviluoma
 */

#pragma once
#include <string>

class Person {
	friend class Phonebook; //Make private members available to the Phonebook class
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