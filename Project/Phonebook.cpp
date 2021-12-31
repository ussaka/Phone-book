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
	cout << "# 2. Save contact information to file in csv format                            #" << endl;
	cout << "# 3. Read contact information from file and add to the phonebook               #" << endl;
	cout << "# 4. Add new person to phone book                                              #" << endl;
	cout << "# 5. Remove a person from the phone book                                       #" << endl;
	cout << "# 6. Print a list of persons who live in the given city                        #" << endl;
	cout << "# 7. Print all contact information, relatives are printed before other persons #" << endl;
	cout << "# 8. Quit                                                                      #" << endl;
	cout << "################################################################################" << endl;
	cout << endl;
}
//^^OK



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
			//^^OK

		case 2: //EI OK

			break;
		case 3: //EI OK
			read_from_file();
			break;
		case 4: //EI OK
			add_person();
			break;
		case 5: // EI OK

			break;
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

void Phonebook::add_person() {
	string name, email, phone_number, city, relative;
	bool r;

	cout << "Enter new person's info:" << endl;
	cout << "Name: ";
	cin >> name;
	//Check that name doesn't contain numbers
	while (contains_digits(name)) {
		cout << "Name contains number(s)!" << endl << "Enter name again: ";
		name.clear(); //clear string
		cin >> name;
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
	//Check that city doesn't contain numbers
	while (contains_digits(city)) {
		cout << "City contains number(s)!" << endl << "Enter city again: ";
		city.clear(); //clear string
		cin >> city;
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

void Phonebook::shutdown() {
	cout << "Shutting down...." << endl;
	exit(0);
}
//^^OK
// 
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



void Phonebook::save_to_file() {
	ofstream outFile("Phonebook.csv");

	outFile << "Name,Email,Telephone number,City" << endl;
	for (auto& e : phonebook) {
		outFile << e.name << "," << e.email << "," << e.telephone_number << "," << e.city << endl;
	}
}

void Phonebook::remove_person() {
	string input;
	cout << "Enter person's name: ";
	cin >> input;

	for (auto it = phonebook.begin(); it != phonebook.end(); ++it) {
		if (it->name == input) {
			phonebook.erase(it);
			cout << input << " erased from the database!" << endl;
			break;
		}
		else {
			cout << input << " not found in the database!" << endl;
		}
	}

}

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

void Phonebook::read_from_file() {
	ifstream inputFile("Phonebook.csv");
	string line, word, name, email, phone, city;
	bool rel = false;

	while (getline(inputFile, line)) {
		stringstream s(line);
		getline(s, word, ',');
		name = word;
		getline(s, word, ',');
		email = word;
		getline(s, word, ',');
		phone = word;
		getline(s, word, ',');
		city = word;

		phonebook.push_back(Person(name, email, phone, city, rel));
	}
}
//^^EI OK