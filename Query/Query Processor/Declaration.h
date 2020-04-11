#pragma once
#include <string>

using namespace std;

class Declaration {
private:
	string varName;
	string varType;
public:
	Declaration();
	~Declaration();
	void setVarName(string);
	void setVarType(string);
	string getVarName();
	string getVarType();
};