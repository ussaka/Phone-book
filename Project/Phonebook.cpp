/*
 * C++ Project Assignment 7. "Phonebook" by Kasperi Kiviluoma
 */

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Phonebook.h"

using namespace std;

Phonebook::Phonebook() {
}

void Phonebook::print_menu() {
	cout << endl;
	cout << "################################################################################" << endl;
	cout << "#                                 Phonebook                                    #" << endl;
	cout << "################################################################################" << endl;
	cout << "# 1. Initialize (clear all records)                                            #" << endl;
	cout << "# 2. Save contact information to file in csv format (if Phonebook.csv exists overwrite)  #" << endl;
	cout << "# 3. Read contact information from file and add to the phonebook               #" << endl;
	cout << "# 4. Add new person to phone book                                              #" << endl;
	cout << "# 5. Remove a person from the phone book                                       #" << endl;
	cout << "# 6. Print a list of persons who live in the given city                        #" << endl;
	cout << "# 7. Print all contact information, relatives are printed before other persons #" << endl;
	cout << "# 8. Quit                                                                      #" << endl;
	cout << "################################################################################" << endl;
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
			remove_person(); //KESKEN
			break;
			//^ ^OK
		case 6: //EI OK

			break;
		case 7: //EI OK!
			for (auto& e : phonebook) {
				cout << e << endl;
				cout << endl;
			}
			break;
		case 8:
			shutdown();
		default:
			cout << "Invalid command!" << endl;
			break;
		}
	}
}
//^^EI OK


void Phonebook::initialize() {
	phonebook.clear();
}

void Phonebook::save_to_file() {
	ofstream outFile("Phonebook.csv");

	if (!outFile.is_open()) {
		cout << "Error, can't write to Phonebook.csv!" << endl;
	}
	else if (outFile.is_open()) {
		outFile << "Name;Email;Telephone number;City;Relative" << endl;
		for (auto& person : phonebook) {
			outFile << person.name << ";" << person.email << ";" << person.telephone_number << ";" << person.city << ";" << person.relative << endl;
		}
		cout << "Phonebook saved to the file!" << endl;
	}
}

void Phonebook::read_from_file() {
	ifstream inputFile("Phonebook.csv");

	if (!inputFile.is_open()) {
		cout << "Error, can't open Phonebook.csv!" << endl;
	}
	else if (inputFile.is_open()) {
		string line, word, name, email, phone, city;
		bool relative = false;

		getline(inputFile, line); //skip first header line
		while (getline(inputFile, line)) { //true while inputFile outputs line
			stringstream s(line); //convert line to stream
			getline(s, word, ';'); //get first word from the stream s, delimiter ';'
			name = word;
			getline(s, word, ';');
			email = word;
			getline(s, word, ';');
			phone = word;
			getline(s, word, ';');
			city = word;
			getline(s, word, '\n');
			if (word == "0") {
				relative = false;
			}
			else if (word == "1") {
				relative = true;
			}
			phonebook.push_back(Person(name, email, phone, city, relative));
		}
		cout << "Read succesfull" << endl;
	}
}

void Phonebook::add_person() {
	string name, email, phone_number, city, relative;
	bool r;

	cout << "Enter new person's info:" << endl;
	cout << "Name: ";
	cin >> name;
	getline(cin, name); //allows name to contain spaces
	//Check that name doesn't contain numbers
	while (contains_digits(name)) {
		cout << "Name contains number(s)!" << endl << "Enter name again: ";
		name.clear(); //clear string
		cin >> name;
		getline(cin, name); //allows name to contain spaces
	}

	cout << "Email: ";
	cin >> email;

	cout << "Number: ";
	cin >> phone_number;
	while (other_than_numbers(phone_number)) {
		cout << "Phone number contains character(s)!" << endl << "Enter phone number again: ";
		phone_number.clear(); //clear string
		cin >> phone_number;
	}

	cout << "City: ";
	cin >> city;
	getline(cin, city); //allows city to contain spaces
	//Check that city doesn't contain numbers
	while (contains_digits(city)) {
		cout << "City contains number(s)!" << endl << "Enter city again: ";
		city.clear(); //clear string
		cin >> city;
		getline(cin, city); //allows city to contain spaces
	}

	while (relative != "No" && relative != "Yes") {
		cout << "Is this person relative?(Yes/No): ";
		cin >> relative;
		if (relative == "No") {
			r = false;
			Person p(name, email, phone_number, city, r);
			phonebook.push_back(p);
			cout << "Person saved!" << endl;
		}
		else if (relative == "Yes") {
			r = true;
			Person p(name, email, phone_number, city, r);
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
	string namee, phone_number;
	cout << "Enter person's phone number: "; //There can be multiple person's with same name but phone number is always tied to one person.
	cin >> phone_number;

	for (auto it = phonebook.begin(); it != phonebook.end(); ++it) {
		if (it->telephone_number == phone_number) {
			namee = it->name;
			phonebook.erase(it);
			cout << namee << " with phone number " << phone_number << " erased from the phonebook!" << endl;
			break;
		}
		else {
			cout << "Person with phone number " << phone_number << " was not found in the phonebook!" << endl;
		}
	}

}

void Phonebook::shutdown() {
	cout << "Shutting down...." << endl;
	exit(0);
}
//^^OK



//Helper functions
bool Phonebook::contains_digits(string s) {
	for (auto i = s.begin(); i != s.end(); ++i) {
		if (isdigit(*i)) {
			return true;
		}
	}
	return false;
}

bool Phonebook::other_than_numbers(string s) {
	for (auto i = s.begin(); i != s.end(); ++i) {
		if (!isdigit(*i)) {
			return true;
		}
	}
	return false;
}
//^^OK





void Phonebook::print_in_city() {
	string input;
	cout << "Enter the city: ";
	cin >> input;

	for (auto& e : phonebook) {
		if (e.city == input) {
			cout << e.name << endl;
		}
	}
}

//^^EI OK