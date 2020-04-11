#pragma once

#include <string>
#include <vector>

using namespace std;

class Relationship {
private:
	int totalArgs;
	vector<string> arg1, arg2;

public:
	Relationship();
	Relationship(int num, vector<string> arg1, vector<string> arg2);

	int getNumOfArgs();
	vector<string> getArg1();
	vector<string> getArg2();
};