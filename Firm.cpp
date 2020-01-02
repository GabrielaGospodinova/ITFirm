#include "Firm.h"

Firm::Firm(std::string employeeName) {
	root = new Employee(employeeName, employeeName);
	totalEmployes++;
}

Firm::~Firm() {
	delete root;
	root = nullptr;
}

//Проверява дали два стринга имат еднакво съдържание
bool Firm::sameName(std::string name1, std::string name2) const {
	if (name1.compare(name2) == 0) {
		return true;
	}
	else {
		return false;
	}
}

//помощна функция на AddEmployee, която добавя служител в вектора от подчинени на конкретен шеф
void Firm::insert(Employee*& elem, std::string bossName) {
	if (elem == nullptr) {
		std::cout << "Invalid element. Insertion couldn't be completed" << std::endl;
		return;
	}
	else {
		Employee* temp = find(bossName);
		elem->level = temp->level + 1; //увеличаваме нивото на подчинения, тъй като е по-низш в йерархията
		temp->childs.push_back(elem);
		totalEmployes++;
		return;
	}
}

void Firm::removeElem(std::string& name)
{
	Employee* temp(find(name));
	if (sameName(temp->name, std::string()))
	{
		std::cout << "Person with the same name doesn't work in the company." << std::endl;
		return;
	}
	else if (temp == root) {
		std::cout << "The boss of the whole company couldn't be removed! Choose another one." << std::endl;
		return;
	}
	else {
		if (temp->childs.size() == 0) {
			deleteElem(temp);
			return;
		}
		else {
			//новият служител, ще бъде този който под текущия съдържа най-много подчинени
			Employee* toBecomeNewRoot = getMaximumDepthElem(temp, temp->level);
			//трябва ни пойнтър към шефа на текущия шеф, защото той ще бъде шеф на toBecomeNewRoot
			Employee* bossOfBosses = find(temp->directBoss);
			//Правим ротацията
			adjustElements(toBecomeNewRoot, temp, bossOfBosses);
		}
	}
}

//изтриване на служител от йерархията
void Firm::deleteElem(Employee*& elem) {
	if (elem != nullptr) {
		Employee* boss = find(elem->directBoss);
		for (int i = 0; i < boss->childs.size(); i++) {
			if (sameName(boss->childs[i]->name , elem->name)) {
				for (int j = i; j < boss->childs.size()-1; j++) {
					boss->childs[j] = boss->childs[j + 1];
				}
				boss->childs.pop_back();
				delete elem;
				elem = nullptr;
				return;
			}
		}
	}
	else {
		std::cout << "No such element!"<<std::endl;
		return;
	}
}

//всички подчинени на конкретен шеф
void Firm::printVector(std::vector<Employee*> list) {
	for (unsigned int i = 0; i < list.size(); i++) {
		std::cout << list[i]->name << " ";
	}
}

//добавяне на служител
void Firm::addEmployee(std::string name, std::string bossName) {
	if (sameName(find(bossName)->name, std::string())) { //find връща default-ни стойности за служител, като името е празен стринг
		std::cout<<"Invalid boss name!"<<std::endl;
	}
	if (sameName(find(name)->name, name)) {
		std::cout << "The employee with the same name already exists!";
		return;
	}
	else {
		Employee* newEmpl = new Employee(name,bossName);
		insert(newEmpl, bossName);
	}
}

//BFS обхождане
Employee*& Firm::find(std::string name) const  {
	std::queue<Employee*> q;
	Employee* temp = new Employee();
	int sizeVis = 0;
	bool* visited = new bool[totalEmployes];
	for (int i = 0; i < totalEmployes; i++) {
		visited[i] = false;
	}
	visited[0] = true;
	q.push(root);
	while (!q.empty()) {
		temp = q.front();
		if (sameName(temp->name, name)) {
			return temp;
		}
		q.pop();
		for (int i = 0; i < temp->childs.size(); i++) {
			if (!visited[++sizeVis]) {
				visited[sizeVis] = true;
				q.push(temp->childs[i]);
			}
		}
	}
	temp = new Employee();
	return temp;
}

//връща максимална височина на елемент
int Firm::getMaximumElem(Employee* elem) const {
	if (elem == nullptr) {
		return 0;
	}
	if (elem->childs.empty()) {
		return 1;
	}
	int maxChildHeight = 0;
	for (int i = 0; i < elem->childs.size(); i++) {
		int currHeight = getMaximumElem(elem->childs[i]);
		if (currHeight > maxChildHeight) {
			maxChildHeight = currHeight;
		}
	}
	return 1 + maxChildHeight;
}

// връща елемента с максимална височина
Employee*& Firm::getMaximumDepthElem(Employee*& elem, int levelOfElem) const
{
	Employee* temp = new Employee;
	if (elem->childs.empty()) {
		return elem;
	}
	else {
		int max = 0;
		for (int i = 0; i < elem->childs.size(); i++) {
			int currMax = getMaximumElem(elem->childs[i]);
			if (currMax > max) {
				max = currMax;
				temp = elem->childs[i];
			}
		}
		return temp;
	}
}

//преки подчинени
void Firm::getDirectDependants(std::string bossName) {
	Employee* temp = find(bossName);

	if (sameName(temp->name, std::string()) ) {
		std::cout << "Invalid bossName!" << std::endl;
	}
	else if (temp->childs.size() == 0) {
		std::cout <<temp->name << " has no subemployees" << std::endl;
	}
	else {
		printVector(temp->childs);
	}
	
}

void Firm::getLevelOrderDependants(std::string bossName) {
	if (root == nullptr) {
		return;
	}
	Employee* temp = find(bossName);
	if (sameName(temp->name, std::string())) {
		std::cout << "Couldn't find person with this name working in the company" << std::endl;
	}
	else if (temp->childs.size() == 0) {
		std::cout <<temp->name<<" has no subemployees"<<std::endl;
	}
	else {
		std::queue<Employee*> q;
		q.push(temp);
		while (!q.empty()) {
			int size = q.size();
			while (size > 0) {
				Employee* currElem = q.front();
				if (sameName(currElem->name, bossName)) {}
				else {
					std::cout << currElem->name << " ";
				}
				q.pop();
				for (unsigned int i = 0; i < currElem->childs.size(); i++) {
					q.push(currElem->childs[i]);
				}
				size--;
			}
			std::cout << std::endl;
		}
	}
}

//връща прекият шеф
void Firm::getClosestBoss(std::string name) {
	Employee* temp = find(name);
	if (sameName(temp->name,root->name)) {
		std::cout << root->name << std::endl;
	}
	else if (sameName(temp->name,std::string())) {
		std::cout << "Couldn't find person with this name working in the company"<<std::endl;
	}
	else {
		std::cout<<temp->directBoss<<std::endl;
	}
}

//public функция, която сама по себе си извиква removeElem
void Firm::removeEmployee(std::string name) {
	removeElem(name);
}

//ротацията на елемнти
void Firm::adjustElements(Employee*& toBecomeNewRoot, Employee*& currBoss, Employee*& bossOfBosses) {

	int foundNewRoot = false;
	for (int i=0; i < currBoss->childs.size(); i++) {
		if (!sameName(currBoss->childs[i]->name ,toBecomeNewRoot->name) && foundNewRoot == false) {
			if (!toBecomeNewRoot->childs.empty()) {
				toBecomeNewRoot->childs.push_back(new Employee);
				for (int j = toBecomeNewRoot->childs.size() - 1; j > i; j--) {
					toBecomeNewRoot->childs[j] = toBecomeNewRoot->childs[j - 1];
				}
				toBecomeNewRoot->childs[i] = currBoss->childs[i];
				toBecomeNewRoot->childs[i]->directBoss = bossOfBosses->name;
			}
		}
		else if (!sameName(currBoss->childs[i]->name,toBecomeNewRoot->name) && foundNewRoot) {
			toBecomeNewRoot->childs.push_back(currBoss->childs[i]);
			int position = toBecomeNewRoot->childs.size() - 1;
			currBoss->childs[position]->directBoss = bossOfBosses->name;
		}
		else foundNewRoot = true;
	}
	for (int i = 0 ; i < bossOfBosses->childs.size(); i++) {
		if (sameName(bossOfBosses->childs[i]->name,currBoss->name)) {
			bossOfBosses->childs[i]=toBecomeNewRoot;
			bossOfBosses->childs[i]->directBoss = bossOfBosses->name;
			deleteElem(currBoss);
			return;
		}
	}
}

void Firm::promotion(std::string name, std::string bossName) {
	Employee* temp = find(name);
	if (sameName(temp->name, std::string())) {
		std::cout << "This employee doesn't work in the company. Couldn't promote him." << std::endl;
		return;
	}
	Employee* boss = find(bossName);
	if (sameName(bossName, root->name)) {
		if (temp->level - boss->level + 1 > 1) {
			std::cout << "You couldn't promote employee to positions above. It's not fair. :)" << std::endl;
			return;
		}
	}
	if (temp->level - boss->level - 1 > 1) {
		std::cout << "You couldn't promote employee to positions above. It's not fair. :)" << std::endl;
		return;
	}
	transferSubemployee(name,boss->name);
}

void Firm::transferSubemployee(std::string name, std::string bossName) {
	if (sameName(name, root->name)) {
		std::cout << "The general boss of the company couldn't be changed!" << std::endl;
	}
	Employee* toBeTrasfered = find(name);
	if (sameName(toBeTrasfered->name, std::string())) {
		std::cout << "This employee doesn't work in the company. Couldn't transfer him." << std::endl;
		return;
	}
	Employee* newBoss = find(bossName);
	if (newBoss->level > toBeTrasfered->level) {
		std::cout << "The boss " << newBoss->name << " is in lower level in hiearchy at the Firm, compared to " << toBeTrasfered->name << std::endl;
	}
	else {
		removeElem(name); // or removeElem
		addEmployee(name, bossName);
	}
}
