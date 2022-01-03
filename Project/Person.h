/*
 * C++ Project Assignment 7. "Phonebook" by Kasperi Kiviluoma
 */

#pragma once
#include <string>

class Person {
	friend class Phonebook; //Make private members available to the Phonebook class
	friend std::ostream& operator<<(std::ostream& out, const Person& p);
	friend std::istream& operator>>(std::istream& is, Person& p);

public:
	Person();
	Person(std::string _name, std::string _email, std::string _telephone_number, std::string _city, std::string _relative);
	std::string name;
	std::string email;
	std::string telephone_number;
	std::string city;
	std::string relative; //Couldn't get rest of the program to work if relative was bool
};