/*
 * C++ Project Assignment 7. "Phonebook" by Kasperi Kiviluoma
 */

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "Phonebook.h"

using namespace std;

Phonebook::Phonebook() {
}

void Phonebook::print_menu() {
	cout << endl;
	cout << setw(90) << setfill('-') << ' ' << endl;
	cout << '|' << setw(44) << setfill(' ') << "Phonebook" << setw(44) << setfill(' ') << '|' << endl;
	cout << setw(90) << setfill('-') << ' ' << endl;
	cout << "    1. Initialize (clear all records)" << endl;
	cout << "    2. Save contact information to file in csv format (if Phonebook.csv exists overwrite)" << endl;
	cout << "    3. Read contact information from file and add to the phonebook" << endl;
	cout << "    4. Add new person to phone book" << endl;
	cout << "    5. Remove a person from the phone book" << endl;
	cout << "    6. Print a list of persons who live in the given city" << endl;
	cout << "    7. Print all contact information, relatives are printed before other persons" << endl;
	cout << "    8. Quit" << endl;
	cout << endl;
}

void Phonebook::start() {
	int command = 0;

	while (true) {
		print_menu(); //print user interface
		cout << "Enter command:" << endl;
		cin >> command;
		if (cin.fail()) { //check that input can be handled
			cin.clear(); //clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore cin until '\n' is reached --> ignore whole input line that raised fail flag
		}

		switch (command) {
		case 1:
			initialize();
			break;
		case 2:
			save_to_file();
			break;
		case 3:
			read_from_file();
			break;
		case 4:
			add_person();
			break;
		case 5:
			remove_person();
			break;
		case 6:
			print_in_city();
			break;
		case 7:
			print_all();
			break;
		case 8:
			shutdown();
		default:
			cout << "Invalid command!" << endl;
			break;
		}
	}
}

void Phonebook::initialize() {
	phonebook.clear();
	cout << "Phonebook initialized!" << endl;
}

void Phonebook::save_to_file() {
	ofstream outFile("Phonebook.csv");

	if (!outFile.is_open()) {
		cout << "Error, can't write to Phonebook.csv!" << endl;
	}
	else if (outFile.is_open()) {
		outFile << "Name;Email;Telephone number;City;Relative" << endl; //header
		for (auto& person : phonebook) {
			outFile << person;
		}
		cout << "Phonebook saved to the file!" << endl;
	}
}

void Phonebook::read_from_file() {
	ifstream inputFile("Phonebook.csv");
	Person person;

	if (!inputFile.is_open()) {
		cout << "Error, can't open Phonebook.csv!" << endl;
	}
	else if (inputFile.is_open()) {
		string line;

		getline(inputFile, line); //skip first header line
		while (getline(inputFile, line)) { //true while inputFile outputs line
			stringstream s(line); //convert line to stream
			s >> person; //fill person's attributes with values from stream s
			phonebook.push_back(person);
		}
		cout << "Read succesfull!" << endl;
	}
}

void Phonebook::add_person() {
	string name, email, phone_number, city, relative;

	cout << "Name: ";
	cin.ignore(); //ignore previously printed '\n'
	getline(cin, name); //allows name to contain spaces
	//Check that name doesn't contain numbers
	while (contains_digits(name)) {
		cout << "Name contains number(s)! Enter name again: ";
		name.clear(); //clear string
		getline(cin, name); //allows name to contain spaces
	}

	cout << "Email: ";
	getline(cin, email);

	cout << "Number: ";
	getline(cin, phone_number);
	while (other_than_digits(phone_number)) {
		cout << "Phone number contains other symbol(s) than digits! Enter phone number again: ";
		phone_number.clear(); //clear string
		getline(cin, phone_number);
	}

	cout << "City: ";
	getline(cin, city); //allows city to contain spaces
	//Check that city doesn't contain numbers
	while (contains_digits(city)) {
		cout << "City contains number(s)! Enter city again: ";
		city.clear(); //clear string
		getline(cin, city); //allows city to contain spaces
	}

	while (relative != "No" && relative != "Yes") {
		cout << "Is this person relative?(Yes/No): ";
		cin >> relative;
		if (relative == "No") {
			Person p(name, email, phone_number, city, relative);
			phonebook.push_back(p);
			cout << "Person saved!" << endl;
		}
		else if (relative == "Yes") {
			Person p(name, email, phone_number, city, relative);
			phonebook.push_back(p);
			cout << "Person saved!" << endl;
		}
		else {
			relative.clear();
			cout << "Input error!, enter relation status again." << endl;
		}
	}
}

void Phonebook::remove_person() {
	string namee;
	bool hit = false;

	cout << "Enter person's name: ";
	cin.ignore(); //make getline ignore previous cout;
	getline(cin, namee);

	for (auto it = phonebook.begin(); it != phonebook.end(); ++it) {
		if (it->name == namee) {
			Person p(it->name, it->email, it->city, it->telephone_number, it->relative); //ensure that name is stored to namee
			namee = p.name;
			phonebook.erase(it);
			cout << namee << " erased from the phonebook!" << endl;
			hit = true;
			break;
		}
	}
	if (hit == false) {
		cout << namee << " was not found in the phonebook!" << endl;
	}
}

void Phonebook::print_in_city() {
	string city;
	bool hit = false;
	cout << "Enter the city: ";
	cin.ignore(); //make getline ignore previous cout
	getline(cin, city); //allows city to contain spaces
	cout << endl;

	for (auto& person : phonebook) {
		if (person.city == city) {
			cout << "Name: " << person.name << endl << "Email: " << person.email << endl << "Phone number: " << person.telephone_number << endl << "City: " << person.city << endl << "Relative: " << person.relative << endl;
			hit = true;
			cout << endl;
		}
	}

	if (hit == false) {
		cout << "No persons found in " << city << "!" << endl;
	}
}

void Phonebook::print_all() {
	bool nothing_to_print = false;

	for (auto& person : phonebook) {
		if (person.relative == "Yes") {
			cout << "Name: " << person.name << endl << "Email: " << person.email << endl << "Phone number: " << person.telephone_number << endl << "City: " << person.city << endl << "Relative: " << person.relative << endl;
			cout << endl;
			nothing_to_print = true;
		}
	}
	for (auto& person : phonebook) {
		if (person.relative == "No") {
			cout << "Name: " << person.name << endl << "Email: " << person.email << endl << "Phone number: " << person.telephone_number << endl << "City: " << person.city << endl << "Relative: " << person.relative << endl;
			cout << endl;
			nothing_to_print = true;
		}
	}
	if (nothing_to_print == false) {
		cout << "Phonebook is empty!" << endl;
	}
}

void Phonebook::shutdown() {
	cout << "Shutting down...." << endl;
	exit(0);
}

//Helper functions
bool Phonebook::contains_digits(string s) {
	for (auto i = s.begin(); i != s.end(); ++i) {
		if (isdigit(*i)) {
			return true;
		}
	}
	return false;
}

bool Phonebook::other_than_digits(string s) {
	for (auto i = s.begin(); i != s.end(); ++i) {
		if (!isdigit(*i)) {
			return true;
		}
	}
	return false;
}