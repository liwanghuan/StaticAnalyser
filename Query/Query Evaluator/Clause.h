#pragma once
#include <string>
#include <vector>

using namespace std;

class Clause {
private:

	int numOfIntercept;

	string clauseType; // follow, follow*, parent, parent*, uses, modifies, pattern

	string firstArg; // for pattern a(x, y) firstArg = "x"
	string firstArgType;

	string secondArg; // for pattern a(x, y) firstArg = "y"
	string secondArgType;


	string mainArg; // for pattern a(x, y) mainArg = "a"
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

	int getNumOfIntercept();

	string getFirstArg();
	string getFirstArgType();

	string getSecondArg();
	string getSecondArgType();

	string getMainArg();
	string getMainArgType();

	bool getIsSubExpr();

	void setnumOfIntercept(int);

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