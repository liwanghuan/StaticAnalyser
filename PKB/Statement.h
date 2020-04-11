#pragma once

#include <list>
#include <string>

using namespace std;

class Statement {
public:
	// default constructor
	Statement();
	Statement(int progLineNum, int level, int closeBracesCounter, string type, string data);

	int getStatementLevel();
	int getStatementNum();
	int getNumOfCloseBraces();
	string getstatementType();
	string getStatementData();

	void setStatementNum(int index);
	void setStatementLevel(int num);
	void setStatementType(string type);
	void setStatementData(string code);
	void setNumOfCloseBraces(int num);
	//~Statement();
private:

	int statementNum;
	int statementLevel;
	int numOfCloseBraces;
	string statementType;
	string statementData;
};