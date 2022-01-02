/*
 * C++ Project Assignment 7. "Phonebook" by Kasperi Kiviluoma
 */

#include <string>
#include <iostream>
#include "Person.h"

using namespace std;

ostream& operator<<(ostream& out, const Person& p) {
	out << "Name: " << p.name << endl << "Email: " << p.email << endl << "Telephone number: " << p.telephone_number << endl << "City: " << p.city << endl;
	if (p.relative == true) {
		out << "Relative: Yes" << endl;
	}
	else if (p.relative == false) {
		out << "Relative: No" << endl;
	}
	return out;
}

Person::Person(string _name, string _email, string _telephone_number, string _city, bool _relative) {
	name = _name;
	email = _email;
	telephone_number = _telephone_number;
	city = _city;
	relative = _relative;
}