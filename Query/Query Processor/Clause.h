#pragma once
#include <string>
#include <vector>

using namespace std;

class Clause {
private:

	int numOfIntercept;

	string clauseType;

	string firstArg;
	string firstArgType;

	string secondArg;
	string secondArgType;

	string mainArg;
	string mainArgType;

	vector<string> variables;

	bool isFirstArgIntercept; // for stmt x; pattern a(x, y) isFirstArgIntercept = true
	bool isSecondArgIntercept; // for stmt y; pattern a(x, y) isSecondArgIntercept = true
	bool isMainArgIntercept; // for stmt a; pattern a(x, y) isMainArgIntercept = true

	bool isSubExpr; // pattern a ("x", _"y"_) isSubExpr = true
    
public:
	Clause();
	~Clause();

	string getClauseType();
	void setClauseType(string);

	string getFirstArg();
	string getFirstArgType();

	string getSecondArg();
	string getSecondArgType();

	string getMainArg();
	string getMainArgType();

	void setFirstArg(string);
	void setFirstArgType(string);

	void setSecondArg(string);
	void setSecondArgType(string);

	void setMainArg(string);
	void setMainArgType(string);

	void setIsFirstArgIntercept(bool);
	void setIsSecondArgIntercept(bool);
	void setIsMainArgIntercept(bool);
	void setIsSubExpr(bool);
	vector<string> getVariables();
	void setVariables(vector<string> newVariables);
};
