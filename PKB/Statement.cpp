#include "Statement.h"

using namespace std;

Statement::Statement() {
	statementNum = -1;
	numOfCloseBraces = 0;
	statementLevel = 0;
	statementType = "";
	statementData = "";
}

Statement::Statement(int progLineNum, int level, int closeBracesCounter, string type, string data) {
	statementNum = progLineNum;
	numOfCloseBraces = closeBracesCounter;
	statementLevel = level;
	statementType = type;
	statementData = data;
}

int Statement::getStatementLevel() {
	return statementLevel;
}

int Statement::getStatementNum() {
	return statementNum;
}

string Statement::getstatementType() {
	return statementType;
}

string Statement::getStatementData() {
	return statementData;
}

int Statement::getNumOfCloseBraces() {
	return numOfCloseBraces;
}

void Statement::setStatementNum(int index) {
	statementNum = index;
}

void Statement::setStatementLevel(int num)
{
	statementLevel = num;
}

void Statement::setStatementType(string type) {
	statementType = type;

}

void Statement::setStatementData(string code) {
	statementData = code;

}

void Statement::setNumOfCloseBraces(int num) {
	numOfCloseBraces = num;
}
