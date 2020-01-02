#pragma once
#include<iostream>
#include<queue>
#include "Employee.h"

class Firm {
private:
	Employee* root;
	int totalEmployes = 0;

	void insert(Employee*& elem, std::string bossName);
	void removeElem(std::string& name);
	void adjustElements(Employee*& toBecomeNewRoot, Employee*& currBoss, Employee*& bossOfBosses);
	void deleteElem(Employee*& elem);

	Employee*& find(std::string name) const;
	Employee*& getMaximumDepthElem(Employee*& list, int levelOfElem) const;
	int getMaximumElem(Employee* elem) const;

	void printVector(std::vector<Employee*> list);
	
public:
	Firm(std::string employeeNam=std::string());
	~Firm();

	void addEmployee(std::string name, std::string bossName);
	void promotion(std::string name, std::string bossName);
	void transferSubemployee(std::string name, std::string bossName);
	void removeEmployee(std::string name);

	void getDirectDependants(std::string bossName);
	void getLevelOrderDependants(std::string bossName);
	void getClosestBoss(std::string name);

	bool sameName(std::string name1, std::string name2) const;

};
