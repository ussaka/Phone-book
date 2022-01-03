/*
 * C++ Project Assignment 7. "Phonebook" by Kasperi Kiviluoma
 */

#include <string>
#include <iostream>
#include "Person.h"

using namespace std;

ostream& operator<<(ostream& out, const Person& p) {
	out << p.name << ";" << p.email << ";" << p.telephone_number << ";" << p.city << ";" << p.relative << endl;
	return out;
}

istream& operator>>(istream& is, Person& person) {
	getline(is, person.name, ';');
	getline(is, person.email, ';');
	getline(is, person.telephone_number, ';');
	getline(is, person.city, ';');
	getline(is, person.relative, '\n');
	return is;
}

Person::Person() {
}

Person::Person(string _name, string _email, string _telephone_number, string _city, string _relative) {
	name = _name;
	email = _email;
	telephone_number = _telephone_number;
	city = _city;
	relative = _relative;
}