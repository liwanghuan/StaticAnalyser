#include "PatternTable.h"
#include <stack>

using namespace std;

PatternTable::PatternTable(){
}


PatternTable::~PatternTable(){
}

void PatternTable::setAssignPattern(int stmtNo, string LHS, string RHS) {
	string toStoreRHS = convertToPostFix(RHS);
	pair<string, string> assignPair = { LHS, toStoreRHS };
	assignPatternMap[stmtNo] = assignPair;
}

void PatternTable::setWhilePattern(int stmtNo, int varID) {
	whilePatternMap[stmtNo] = varID;
	auto it1 = whilePatternMapReverse.find(varID);
	if (it1 != whilePatternMapReverse.end()) {
		whilePatternMapReverse[varID].push_back(stmtNo);
	} else {
		whilePatternMapReverse[varID] = list<int>();
		whilePatternMapReverse[varID].push_back(stmtNo);
	}
}

void PatternTable::setIfPattern(int stmtNo, int varID) {
	ifPatternMap[stmtNo] = varID;
	auto it1 = ifPatternMapReverse.find(varID);
	if (it1 != ifPatternMapReverse.end()) {
		ifPatternMapReverse[varID].push_back(stmtNo);
	} else {
		ifPatternMapReverse[varID] = list<int>();
		ifPatternMapReverse[varID].push_back(stmtNo);
	}
}

//1 for LHS pattern, 2 for RHS pattern, -1 for no stmtNo
list<int> PatternTable::getAssignPatternStmtNumber(int side, string pattern) {
	//case switch
	list<int> allStmtNoWithExactString;
	allStmtNoWithExactString.clear();
	unordered_map<int, pair<string, string>>::iterator it;

	if (side == 1) {
		for (it = assignPatternMap.begin(); it != assignPatternMap.end(); ++it) {
			if (it->second.first.compare(pattern) == 0)
				allStmtNoWithExactString.push_back(it->first);
		}
	}

	else if (side == 2) {
		string patternToCompare = convertToPostFix(pattern);
		for (it = assignPatternMap.begin(); it != assignPatternMap.end(); ++it) {
			if (it->second.second.compare(patternToCompare) == 0)
				allStmtNoWithExactString.push_back(it->first);
		}
	}
	
	return allStmtNoWithExactString;
}

list<int> PatternTable::getStmtNoWithString(int side, string pattern) {
	list<int> allStmtNoWithString;
	allStmtNoWithString.clear();
	unordered_map<int, pair<string, string>>::iterator it;
	
	if (side == 1) {
		for (it = assignPatternMap.begin(); it != assignPatternMap.end(); ++it) {
			if ((it->second.first.find(pattern)) != string::npos)
				allStmtNoWithString.push_back(it->first);
		}
	}

	else if (side == 2) {
		string patternToCompare = convertToPostFix(pattern);
		for (it = assignPatternMap.begin(); it != assignPatternMap.end(); ++it) {
			if ((it->second.second.find(patternToCompare)) != string::npos)
				allStmtNoWithString.push_back(it->first);
		}
	}
	
	allStmtNoWithString.sort();
	return allStmtNoWithString;
}


//get LHS of pattern from stmtNo.
string PatternTable::getAssignPatternLHS(int stmtNo) {
	return assignPatternMap.at(stmtNo).first;

}

//get RHS of pattern from stmtNo.

string PatternTable::getAssignPatternRHS(int stmtNo) {
	return assignPatternMap.at(stmtNo).second;
}

list<int> PatternTable::getIfPatternStmtNumber(int varID) {
	unordered_map<int, list<int>>::iterator itKey = ifPatternMapReverse.find(varID);
	
	if (itKey == ifPatternMapReverse.end()) {
		list<int> nullResultList;
		return nullResultList;
	}

	else {
		return itKey->second;
	}
}

list<int> PatternTable::getWhilePatternStmtNumber(int varID) {
	unordered_map<int, list<int>>::iterator itKey = whilePatternMapReverse.find(varID);

	if (itKey == whilePatternMapReverse.end()) {
		list<int> nullResultList;
		return nullResultList;
	}

	else {
		return itKey->second;
	}
}

int PatternTable::getWhilePatternUses(int stmtNo) {
	unordered_map<int, int>::iterator itKey = whilePatternMap.find(stmtNo);
	if (itKey != whilePatternMap.end()) {
		return itKey->second;
	}
	return -1;
}

int PatternTable::getIfPatternUses(int stmtNo) {
	unordered_map<int, int>::iterator itKey = ifPatternMap.find(stmtNo);
	if (itKey != ifPatternMap.end()) {
		return itKey->second;
	}
	return -1;
}

unordered_map<int, int> PatternTable::getWhilePatternMap() {
	return whilePatternMap;
}

unordered_map<int, int> PatternTable::getIfPatternMap() {
	return ifPatternMap;
}

unordered_map<int, pair<string, string>> PatternTable::getassignPatternMap() {
	return assignPatternMap;
}

int PatternTable::getAssignPatternMapSize() {
	return assignPatternMap.size();
}

int PatternTable::getWhilePatternMapSize() {
	return whilePatternMap.size();
}

int PatternTable::getWhilePatternMapReverseSize() {
	return whilePatternMapReverse.size();
}

int PatternTable::getIfPatternMapSize() {
	return ifPatternMap.size();
}

int PatternTable::getIfPatternMapReverseSize() {
	return ifPatternMapReverse.size();
}

string PatternTable::convertToPostFix(string str) {
	stack<string> opStack;
	list<string> tokenList;
	list<string> postFixList;
	string postFixString = "";

	tokenList = tokenizeExpression(str);
	
	//if only have one variable
	if (tokenList.size() == 1) {
		postFixString = "." + tokenList.front() + ".";
		return postFixString;
	}

	//else an expression
	for (list<string>::iterator iter = tokenList.begin(); iter != tokenList.end(); ++iter) {
		if (*iter == "(") {
			opStack.push("(");
		}
		else if (*iter == ")") {
			while (opStack.top() != "(") {
				postFixList.push_back(opStack.top());
				opStack.pop();
			}
			opStack.pop();
		}
		else if (isOperator(*iter)) {
			while (!opStack.empty() &&
				(getPriority(opStack.top()) >= getPriority(*iter))) {
				postFixList.push_back(opStack.top());
				opStack.pop();
			}
			opStack.push(*iter);
		}
		else {
			string str = "." + *iter + ".";
			postFixList.push_back(str);
		}
	}

	while (!opStack.empty()) {
		postFixList.push_back(opStack.top());
		opStack.pop();
	}

	for (list<string>::iterator i = postFixList.begin(); i != postFixList.end(); ++i) {
		postFixString += *i;
	}

	return postFixString;
}

list<string> PatternTable::tokenizeExpression(string expression) {
	size_t found = expression.find_first_of("+-*()");
	list<string> result;
	string temp;

	if (found == string::npos) {
		result.push_back(expression);
		return result;
	}

	while (found != string::npos) {
		temp = expression.substr(0, found);
		if (temp != "") {
			result.push_back(temp);
		}

		temp = expression.at(found);
		result.push_back(temp);

		expression = expression.substr(found + 1);
		found = expression.find_first_of("+-*()");
	}

	if (!expression.empty()) {
		result.push_back(expression);
	}

	return result;
}

int PatternTable::getPriority(string str) {
	if (str == "*") {
		return 2;
	}
	else if (str == "+" || str == "-") {
		return 1;
	}
	else {
		return 0;
	}
}

bool PatternTable::isParenthesis(string str) {
	return ((str == "(") || (str == ")"));
}

bool PatternTable::isOperator(string str) {
	return ((str == "+") || (str == "-") || (str == "*"));
}