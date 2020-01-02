#pragma once
#include<string>
#include<vector>

struct Employee {
	std::string name;
	std::vector<Employee*> childs;
	std::string directBoss;
	int level = 0;
	
	Employee(std::string m_name = std::string(), std::string boss = std::string()) : name(m_name), directBoss(boss) {
		childs = {};
		if (m_name == boss ) {
			level = 0;
		}
	}
	
	~Employee() {
		for (int i = 0; i < childs.size(); i++) {
			delete childs[i];
		}
	}

};