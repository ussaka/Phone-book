/*
 * C++ Project Assignment 7. "Phonebook" by Kasperi Kiviluoma
 */

#pragma once
#include <vector>
#include "Person.h"

class Phonebook {
public:
	Phonebook();
	void start(); //Start the phonebook program
	void print_menu(); //Print available commands
	void initialize(); //Delete all entries from the phonebook
	void save_to_file(); //Save values to Phonebook.csv. Overwrites existing file
	void read_from_file(); //Add values from Phonebook.csv to the phonebook
	void add_person(); //Add person to the phonebook
	void remove_person(); //Remove person from the phonebook
	void print_in_city(); //Print all persons in given city
	void print_all(); //Print all persons. Print relatives first
	void shutdown(); //End program

	//Helper functions
	bool contains_digits(std::string s); //Check if string contains digits, return true if contains digits.
	bool other_than_digits(std::string s); //Check if string contains only digits, return true if contains other than digits.

private:
	std::vector<Person> phonebook;
};