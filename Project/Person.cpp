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

istream& operator>>(istream& in, Person& person) {
	in >> person.name;
	return in;
}

Person::Person(string _name, string _email, string _telephone_number, string _city, bool _relative) {
	name = _name;
	email = _email;
	telephone_number = _telephone_number;
	city = _city;
	relative = _relative;
}