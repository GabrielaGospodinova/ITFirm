#pragma once
#include "Firm.h"
#include <sstream>

class Command {
public:
	Command() {};
	~Command() {};

	void run();
private:
	bool running = true;
	bool isValidName(std::string name);
};

bool Command::isValidName(std::string name) {
	if (name[0] < 'A' || name[0]>'Z') {
		return false;
	}
	for (int i = 1; i < name.size(); i++) {
		if (name[i] < 'a' || name[i]>'z') {
			return false;
		}
	}
	return true;
}

void Command::run() {
	std::cout << "Welcome to your IT Firm hierarchy. Please enter your first name to become the ultimate boss at the firm." << std::endl;
	std::string name;
	std::cin >> name;
	Firm* root = new Firm(name);
	while (root->sameName(name, std::string()) || !isValidName(name)) {
		
		std::cout << "The name of the employee is not valid one. Reenter it:" << std::endl;
		std::cin >> name;
	}
	std::cout << "Please, choose an option from the menu:\n"
		"Enter 'ADD EMPLOYEE' in order to hire an employee at your firm.\n"
		"Enter 'FIRE EMPLOYEE' in order to fire an employee at your firm.\n"
		"Enter 'PROMOTE EMPLOYEE' in order to promote an employee.\n"
		"Enter 'TRANSFER' in order to tranfer a current employee to different department.\n"
		"Enter 'LIST SUBEMPLOYEES' in order to list the closest subemployees of the boss. \n"
		"Enter 'LIST ALL SUBEMPLOYEES' in order to list every subemployee under the boss, listed in level order.\n"
		"Enter 'BOSS?' in order to get the name of the closest boss to this employee. \n"
		"Enter 'EXIT' in order to exit the firm hierachy control pannel.\n";

	std::string command;
	std::cin.ignore();
	while (running) {
		std::getline(std::cin,command);
		if (command.compare("EXIT") == 0) {
			running = false;
		}
		else if (command.compare("ADD EMPLOYEE") == 0) {
			std::cout << "Write the name of the employee and the name of his direct boss."<<std::endl;
			std::string input;
			std::string bossName;
			std::getline(std::cin, input);
			std::stringstream reader(input); //used for getting words from a string
			reader >> name;	
			reader >> bossName;
			root->addEmployee(name, bossName);
		}
		else if(command.compare("FIRE EMPLOYEE") == 0) {
			std::cout << "Write the name of the employee: ";
			std::string input;
			std::getline(std::cin, input);
			std::stringstream reader(input);
			std::string name;
			reader >> name;
			root->removeEmployee(name);
		}
		else if (command.compare("PROMOTE EMPLOYEE") == 0) {
			std::cout << "Write the name of the employee you want to promote and the name of his new boss: " <<std::endl;
			std::string input;
			std::string name;
			std::string boss;
			std::getline(std::cin, input);
			std::stringstream reader(input);
			reader >> name;
			reader >> boss;
			root->promotion(name, boss);
		}
		else if (command.compare("TRANSFER") == 0) {
			std::cout << "Write the name of the employee you want to transfer and the name of the boss of the new department: "<<std::endl;
			std::string input;
			std::string name;
			std::string boss;
			std::getline(std::cin, input);
			std::stringstream reader(input);
			reader >> name;
			reader >> boss;
			root->transferSubemployee(name, boss);
		}
		else if (command.compare("LIST SUBEMPLOYEES") == 0) {
			std::string name;
			std::cout << "Write the name of the boss:";
			std::cin >> name;
			root->getDirectDependants(name);
			std::cin.ignore();
		}
		else if (command.compare("LIST ALL SUBEMPLOYEES") == 0) {
			std::string name;
			std::cout << "Write the name of the boss: ";
			std::cin >> name;
			root->getLevelOrderDependants(name);
			std::cin.ignore();
		

		}
		else if (command.compare("BOSS?") == 0) {
			std::string name;
			std::cout << "Write the name of the employee: ";
			std::cin >> name;
			root->getClosestBoss(name);
			std::cin.ignore();
		}
		else {
			std::cout << "Invalid command!" << std::endl;
		}
		std::cout << "Enter new command: " << std::endl;
	}


}

