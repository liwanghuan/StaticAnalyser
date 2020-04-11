#include "Parser.h"

using namespace std;

Parser::Parser() {
	isValidSourceCode = true;
	errorMsg = EMPTY_STRING;
}

Parser::~Parser() {
}

/*
TODO: Process the source code in string format
*/
vector<Statement> Parser::processSourceCode(string progLine) {
	initializeSourceCode(progLine);
	createSourceList();
	sortLists();
	return PKB::getPKBInstance()->getSourceList();
}

/*
TODO: Initialize source code in string format
*/
void Parser::initializeSourceCode(string progLine) {
	sourceCode = progLine;
}

/*
TODO: Set error message and the error character position
*/
void Parser::setErrorMsg(string msg, int pos) {
	if (errorMsg.empty()) {
		errorMsg = ERROR_MSG_INVALID_SOURCE_CODE + msg + ERROR_MSG_CHAR_POSITION + to_string(pos + 1) + SPACE_NEW_LINE_CHAR;
	}
}

/*
TODO: Sort lists in PKB
*/
void Parser::sortLists() {
	PKB::getPKBInstance()->sortUsesModifiesMap();
	PKB::getPKBInstance()->sortConstList();
	PKB::getPKBInstance()->sortCallsProcMap();
}

/*
TODO: Parse source code and update PKB table
*/
void Parser::createSourceList() {
	// Initialize all the variables
	int pos = INIT_POINTER_POSITION;
	int stmtNo = INIT_PROC_LINE_NUM;
	int codeLen = (int) sourceCode.length();
	int numOfOpenBracesCounter = INIT_COUNTER_NUM;
	int numOfCloseBracesCounter = INIT_COUNTER_NUM;
	int procID = INIT_PROC_ID;

	string procName = EMPTY_STRING;

	// Intialize all the stacks
	list<int> parentList;
	stack<stack<int>> followStack;

	validatePointerIsWithinRange(pos);

	while (isValidSourceCode && numOfOpenBracesCounter >= numOfCloseBracesCounter && pos < codeLen) {
		skipSpace(pos);
		if (isValidSourceCode && hasFoundProcedureKeyWord(pos)) {
			followStack.push(stack<int>());
			processProcedureStatement(pos, stmtNo, numOfOpenBracesCounter, numOfCloseBracesCounter, procID);
			skipSpace(pos);
			while (isValidSourceCode && numOfOpenBracesCounter > numOfCloseBracesCounter && pos < codeLen) {
				skipSpace(pos);
				processStatement(pos, stmtNo, numOfOpenBracesCounter, numOfCloseBracesCounter, procID, parentList, followStack);
			}
			if (isValidSourceCode && ifCounter != elseCounter) {
				setErrorMsg(ERROR_MSG_MISSING_ELSE_CONTAINER, pos);
				setIsInvalidSourceCode();
			}
		} else {
			setErrorMsg(ERROR_MSG_MISSING_PROCEDURE_KEY_WORD, pos);
			setIsInvalidSourceCode();
		}
	}

	if (isValidSourceCode && numOfOpenBracesCounter != numOfCloseBracesCounter) {
		setErrorMsg(ERROR_MSG_INVALID_SOURCE_CODE_OPEN_CLOSE_CURLY_BRACE_COUNT, pos);
		setIsInvalidSourceCode();
	}

	exitAndShowErrorIfInvalidSourceCode();
}

/*
TODO: Exit and output error if invalid source code is detected
*/
void Parser::exitAndShowErrorIfInvalidSourceCode() {
	if (!isValidSourceCode) {
		cerr << errorMsg << endl;
		exit(-1);
	}
}

/*
TODO: Obtain LHS and RHS of assign statement
*/
pair<string, string> Parser::getSplitAssignStatement(string data) {
	string delimiter = string(1, ARITHMETIC_EQUAL_CHAR);
	data += string(1, ARITHMETIC_EQUAL_CHAR); // add delimiter to the last string
	size_t pos = 0;
	string token;
	string assignArr[2] = { EMPTY_STRING, EMPTY_STRING };
	int count = 0;

	while ((pos = data.find(delimiter)) != std::string::npos) {
		token = data.substr(0, pos);
		assignArr[count] = token;
		data.erase(0, pos + delimiter.length());
		++count;
	}
	pair<string, string> assignPair = { assignArr[0], assignArr[1] };
	return assignPair;
}


/*
TODO: Validate procedure and variable name
*/
void Parser::validateNameChar(int pos) {
	if (isValidSourceCode && !isAlphaNumeric(pos)) {
		setIsInvalidSourceCode();
		setErrorMsg(ERROR_MSG_INVALID_VAR_NAME_CHAR, pos);
	}
}

/*
TODO: Validate ID is valid
*/
void Parser::validateID(int id) {
	if (id == -1) {
		setIsInvalidSourceCode();
	}
}

/*
TODO: Validate procedure name and variable first letter is in letter
*/
void Parser::validateLetterNameFirstChar(int pos) {
	if (isValidSourceCode && !isAlpha(pos)) {
		setIsInvalidSourceCode();
		setErrorMsg(ERROR_MSG_INVALID_VAR_NAME_FIRST_CHAR, pos);
	}
}

/*
TODO: Validate the character at the position is space
*/
void Parser::validateSpaceChar(int pos) {
	if (isValidSourceCode && !isSpace(pos)) {
		setIsInvalidSourceCode();
		setErrorMsg(ERROR_MSG_INVALID_SPACE_CHAR, pos);
	}
}

/*
TODO: Validate the pointer is not out of bound
*/
void Parser::validatePointerIsWithinRange(int pos) {
	int sourceCodeSize = (int) sourceCode.length();

	if (pos >= sourceCodeSize) {
		setIsInvalidSourceCode();
	}
}

/*
TODO: Check statement type and call respective method to process the statement
*/
void Parser::processStatement(int& pos, int& stmtNo, int& numOfOpenBracesCounter, int& numOfCloseBracesCounter, int& procID, list<int>& parentList, stack<stack<int>>& followStack) {
	if (hasFoundWhileKeyWord(pos)) {
		processWhileStatement(pos, stmtNo, numOfOpenBracesCounter, numOfCloseBracesCounter, procID, parentList, followStack);
	}
	else if (hasFoundIfKeyWord(pos)) {
		processIfStatement(pos, stmtNo, numOfOpenBracesCounter, numOfCloseBracesCounter, procID, parentList, followStack);
	}
	else if (hasFoundElseKeyWord(pos)) {
		processElseStatement(pos, stmtNo, numOfOpenBracesCounter, numOfCloseBracesCounter, parentList, followStack);
	}
	else if (hasFoundCallKeyWord(pos)) {
		processCallStatement(pos, stmtNo, numOfOpenBracesCounter, numOfCloseBracesCounter, procID, parentList, followStack);
	}
	else {
		processAssignStatement(pos, stmtNo, numOfOpenBracesCounter, numOfCloseBracesCounter, procID, parentList, followStack);
	}
}

/*
TODO: Process procedure statement and update PKB
*/
void Parser::processProcedureStatement(int& pos, int& stmtNo, int& numOfOpenBracesCounter, int& numOfCloseBracesCounter, int& procID) {
	string data = EMPTY_STRING;
	pos += STMT_TYPE_PROC_STRING.length() + 1;
	skipSpace(pos);
	validateLetterNameFirstChar(pos);

	while (isValidSourceCode && !isCurlyOpenBraceSymbol(pos) && !isSpace(pos)) {
		validateNameChar(pos);
		data.push_back(sourceCode.at(pos));
		++pos;
		validatePointerIsWithinRange(pos);
	}

	while (isValidSourceCode && !isCurlyOpenBraceSymbol(pos)) {
		validateSpaceChar(pos);
		++pos;
		validatePointerIsWithinRange(pos);
	}
	++numOfOpenBracesCounter;
	int statementLevel = numOfOpenBracesCounter - numOfCloseBracesCounter - 1;
	PKB::getPKBInstance()->updateSourceList((int) -1, statementLevel, (int) 0, STMT_TYPE_PROC_STRING, data);

	procID = PKB::getPKBInstance()->insertProc(data);
	validateID(procID);
	++pos;
}

/*
TODO: Process while statement and update PKB
*/
void Parser::processWhileStatement(int& pos, int& stmtNo, int& numOfOpenBracesCounter, int& numOfCloseBracesCounter, int procID, list<int>& parentList, stack<stack<int>>& followStack) {
	string data = EMPTY_STRING;
	pos += STMT_TYPE_WHILE_STRING.length() + 1;
	skipSpace(pos);
	validateLetterNameFirstChar(pos);

	while (isValidSourceCode && !isCurlyOpenBraceSymbol(pos) && !isSpace(pos)) {
		validateNameChar(pos);
		data.push_back(sourceCode.at(pos));
		++pos;
		validatePointerIsWithinRange(pos);
	}
	while (isValidSourceCode && !isCurlyOpenBraceSymbol(pos)) {
		validateSpaceChar(pos);
		++pos;
		validatePointerIsWithinRange(pos);
	}
	++numOfOpenBracesCounter;

	updateStmtLst(stmtNo);

	int statementLevel = numOfOpenBracesCounter - numOfCloseBracesCounter - 1;
	PKB::getPKBInstance()->updateSourceList(stmtNo, statementLevel, (int) 0, STMT_TYPE_WHILE_STRING, data);


	int varID = PKB::getPKBInstance()->insertVar(data);
	validateID(varID);
	int useProgLineNum = stmtNo;
	PKB::getPKBInstance()->setUses(procID, useProgLineNum, varID);
	updateWhilePatternMap(stmtNo, varID);
	for (list<int>::iterator it1 = parentList.begin(); it1 != parentList.end(); ++it1) {
		int parentProgLineNum = *it1;
		PKB::getPKBInstance()->setStmtUses(parentProgLineNum, varID);
	}

	processParentList(parentList, stmtNo);
	processFollowStack(followStack, stmtNo);
	followStack.push(stack<int>());

	int parentProgLineNum = stmtNo;
	parentList.push_front(parentProgLineNum);
	++stmtNo;
	++pos;
}

/*
TODO: Process if statement and update PKB
*/
void Parser::processIfStatement(int& pos, int& stmtNo, int& numOfOpenBracesCounter, int& numOfCloseBracesCounter, int procID, list<int>& parentList, stack<stack<int>>& followStack) {
	string data = EMPTY_STRING;
	pos += STMT_TYPE_IF_STRING.length() + 1;
	skipSpace(pos);
	validateLetterNameFirstChar(pos);

	while (isValidSourceCode && !isSpace(pos)) {
		validateNameChar(pos);
		data.push_back(sourceCode.at(pos));
		++pos;
		validatePointerIsWithinRange(pos);
	}

	skipSpace(pos);

	if (hasFoundThenKeyWord(pos)) {
		pos += STMT_TYPE_THEN_STRING.length();
		skipSpace(pos);
	} else {
		setErrorMsg(ERROR_MSG_MISSING_THEN_KEY_WORD, pos);
		setIsInvalidSourceCode();
	}

	while (isValidSourceCode && !isCurlyOpenBraceSymbol(pos)) {
		validateSpaceChar(pos);
		++pos;
		validatePointerIsWithinRange(pos);
	}
	++numOfOpenBracesCounter;

	updateStmtLst(stmtNo);

	int statementLevel = numOfOpenBracesCounter - numOfCloseBracesCounter - 1;
	PKB::getPKBInstance()->updateSourceList(stmtNo, statementLevel, (int)0, STMT_TYPE_IF_STRING, data);

	int varID = PKB::getPKBInstance()->insertVar(data);
	validateID(varID);

	int useProgLineNum = stmtNo;
	PKB::getPKBInstance()->setUses(procID, useProgLineNum, varID);

	updateIfPatternMap(stmtNo, varID);

	for (list<int>::iterator it1 = parentList.begin(); it1 != parentList.end(); ++it1) {
		int parentProgLineNum = *it1;
		PKB::getPKBInstance()->setStmtUses(parentProgLineNum, varID);
	}

	processParentList(parentList, stmtNo);
	processFollowStack(followStack, stmtNo);
	followStack.push(stack<int>());

	int parentProgLineNum = stmtNo;
	parentList.push_front(parentProgLineNum);
	parentList.push_front(parentProgLineNum);
	++stmtNo;
	++pos;
	++ifCounter;
}

/*
TODO: Process else statement and update PKB
*/
void Parser::processElseStatement(int & pos, int& progLineNum, int& numOfOpenBracesCounter, int& numOfCloseBracesCounter, list<int>& parentList, stack<stack<int>>& followStack) {
	string data = EMPTY_STRING;
	vector<Statement> sourceList = PKB::getPKBInstance()->getSourceList();
	unordered_map<int, int> sourceListIndex = PKB::getPKBInstance()->getSourceListIndex();

	pos += STMT_TYPE_ELSE_STRING.length();
	skipSpace(pos);

	if (isValidSourceCode && !parentList.empty()) {
		auto it = sourceListIndex.find(parentList.front());
		if (it != sourceListIndex.end()) {
			int index = it->second;
			if (sourceList.at(index).getstatementType() != STMT_TYPE_IF_STRING) {
				setIsInvalidSourceCode();
			}
		}
	} else {
		setIsInvalidSourceCode();
	}

	if (sourceList.at(sourceList.size() - 1).getstatementType() == STMT_TYPE_ELSE_STRING) {
		setIsInvalidSourceCode();
	}

	while (isValidSourceCode && !isCurlyOpenBraceSymbol(pos)) {
		validateSpaceChar(pos);
		++pos;
		validatePointerIsWithinRange(pos);
	}
	++numOfOpenBracesCounter;
	int statementLevel = numOfOpenBracesCounter - numOfCloseBracesCounter - 1;
	PKB::getPKBInstance()->updateSourceList((int)-1, statementLevel, (int)0, STMT_TYPE_ELSE_STRING, data);
	followStack.push(stack<int>());
	++pos;
	++elseCounter;
}

/*
TODO: Process call statement and update PKB
*/
void Parser::processCallStatement(int & pos, int& stmtNo, int& numOfOpenBracesCounter, int& numOfCloseBracesCounter, int procID, list<int>& parentList, stack<stack<int>>& followStack) {
	string data = EMPTY_STRING;
	pos += STMT_TYPE_CALL_STRING.length() + 1;
	skipSpace(pos);
	validateLetterNameFirstChar(pos);

	while (sourceCode.at(pos) != SEMI_COLON_CHAR && !isSpace(pos)) {
		validateNameChar(pos);
		data.push_back(sourceCode.at(pos));
		++pos;
		validatePointerIsWithinRange(pos);
	}

	while (isValidSourceCode && sourceCode.at(pos) != SEMI_COLON_CHAR) {
		validateSpaceChar(pos);
		++pos;
		validatePointerIsWithinRange(pos);
	}
	++pos;
	validatePointerIsWithinRange(pos);

	bool isEndOfLoop = false;
	int statementLevel = numOfOpenBracesCounter - numOfCloseBracesCounter;
	int numOfCloseBraces = 0;

	processParentList(parentList, stmtNo);
	processFollowStack(followStack, stmtNo);

	while (!isEndOfLoop && pos < (int)sourceCode.length()) {
		if (isCurlyCloseBraceSymbol(pos) || isSpace(pos)) {
			if (isCurlyCloseBraceSymbol(pos)) {
				popFollowStack(followStack);
				popParentList(parentList);
				++numOfCloseBraces;
				++numOfCloseBracesCounter;
			}
			++pos;
		}
		else {
			isEndOfLoop = true;
		}
	}

	updateStmtLst(stmtNo);

	PKB::getPKBInstance()->updateSourceList(stmtNo, statementLevel, numOfCloseBraces, STMT_TYPE_CALL_STRING, data);
	PKB::getPKBInstance()->insertCallsProcMap(procID, data);
	PKB::getPKBInstance()->insertCallsStmtList(stmtNo, data);
	++stmtNo;
}

/*
TODO: Process assign statement and update PKB
*/
void Parser::processAssignStatement(int& pos, int& stmtNo, int& numOfOpenBracesCounter, int& numOfCloseBracesCounter, int procID, list<int>& parentList, stack<stack<int>>& followStack) {
	int numOfEqualArithmeticSymbol = 0;
	int openParenthesisCounter = 0;
	int closeParenthesisCounter = 0;
	int prevCharPos = pos;
	int modifyProgLineNum = stmtNo;
	int useProgLineNum = stmtNo;

	bool hasFoundEqualArithmeticSymbol = false;
	bool hasFoundOperationArithmeticSymbol = false;
	bool hasFoundParenthesis = false;
	bool hasFoundVarNameChar = false;

	string data = EMPTY_STRING;
	string varName = EMPTY_STRING;

	skipSpace(pos);
	validateLetterNameFirstChar(pos);

	while (isValidSourceCode && sourceCode.at(pos) != SEMI_COLON_CHAR) {
		if (!isSpace(pos)) {
			if (isArithmeticEqualSymbol(pos)) {
				hasFoundEqualArithmeticSymbol = true;
				++numOfEqualArithmeticSymbol;
			}

			if (isParenthesisOpenSymbol(pos)) {
				hasFoundParenthesis = true;
				++openParenthesisCounter;
			}

			if (isParenthesisCloseSymbol(pos)) {
				hasFoundParenthesis = true;
				++closeParenthesisCounter;
			}

			if (varName.length() == 0 && isAlpha(pos)) {
				hasFoundVarNameChar = true;
			}

			hasFoundOperationArithmeticSymbol = isArithmeticOperationSymbol(pos);
			hasFoundParenthesis = isParenthesisSymbol(pos);

			if (!(isAlphaNumeric(pos) || isArithmeticSymbol(pos) || isParenthesisSymbol(pos))) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_CHAR, pos);
			} else if ((hasFoundEqualArithmeticSymbol || hasFoundOperationArithmeticSymbol || hasFoundParenthesis) && !hasFoundVarNameChar) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_UNDEFINED_MOD_VAR, pos);
			} else if (!hasFoundEqualArithmeticSymbol && (hasFoundParenthesis || hasFoundOperationArithmeticSymbol)) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_EQUAL_AFTER_OPERATOR, pos);
			} else if (numOfEqualArithmeticSymbol > 1) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_EQUAL_APPEARED_TWICE, pos);
			} else if (isArithmeticSymbol(prevCharPos) && isArithmeticSymbol(pos)) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_CONSEC_ARITH_SYMBOL, pos);
			} else if ((isParenthesisOpenSymbol(prevCharPos) && isParenthesisCloseSymbol(pos)) 
				|| (isParenthesisCloseSymbol(prevCharPos) && isParenthesisOpenSymbol(pos))) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_CONSEC_OPPO_PARENTHESIS, pos);
			} else if (isParenthesisOpenSymbol(prevCharPos) && isArithmeticSymbol(pos)) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_OPEN_PARENTHESIS_BEFORE_ARITH_SYMBOL, pos);
			} else if (isArithmeticSymbol(prevCharPos) && isParenthesisCloseSymbol(pos)) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_ARITH_SYMBOL_BEFORE_CLOSE_PARENTHESIS, pos);
			} else if (!(isArithmeticSymbol(prevCharPos) || isParenthesisOpenSymbol(prevCharPos)) && isParenthesisOpenSymbol(pos)) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_INVALID_CHAR_BEFORE_OPEN_PARENTHESIS, pos);
			} else if (!(isAlphaNumeric(prevCharPos) || isParenthesisCloseSymbol(prevCharPos)) && isParenthesisCloseSymbol(pos)) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_INVALID_CHAR_BEFORE_CLOSE_PARENTHESIS, pos);
			} else if ((isAlphaNumeric(prevCharPos) && isAlphaNumeric(pos) && (pos - prevCharPos) > 1) || (isParenthesisCloseSymbol(prevCharPos) && isAlphaNumeric(pos)) 
				|| (isAlphaNumeric(prevCharPos) && isParenthesisOpenSymbol(pos))) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_MISSING_ARITH_SYMBOL, pos);
			} else if (varName.length() > 0 && isdigit(varName.at(0)) && isAlpha(pos)) {
				setIsInvalidSourceCode();
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_VAR_DIGIT_FIRST_CHAR, pos);
			} else if (isAlphaNumeric(pos)) {
				varName.push_back(sourceCode.at(pos));
			} else if (hasFoundEqualArithmeticSymbol && !hasFoundOperationArithmeticSymbol && isArithmeticEqualSymbol(pos) && varName.length() > 0 && isalpha(varName.at(0))) {
				int varID = PKB::getPKBInstance()->insertVar(varName);
				validateID(varID);
				PKB::getPKBInstance()->setModifies(procID, stmtNo, varID);
				for (list<int>::iterator it1 = parentList.begin(); it1 != parentList.end(); ++it1) {
					int parentProgLineNum = *it1;
					PKB::getPKBInstance()->setStmtModifies(parentProgLineNum, varID);
				}
			} else if (hasFoundEqualArithmeticSymbol && hasFoundOperationArithmeticSymbol && isArithmeticOperationSymbol(pos) && varName.length() > 0 && isalpha(varName.at(0))) {
				int varID = PKB::getPKBInstance()->insertVar(varName);
				validateID(varID);
				PKB::getPKBInstance()->setUses(procID, stmtNo, varID);
				for (list<int>::iterator it1 = parentList.begin(); it1 != parentList.end(); ++it1) {
					int parentProgLineNum = *it1;
					PKB::getPKBInstance()->setStmtUses(parentProgLineNum, varID);
				}
			} else if (hasFoundEqualArithmeticSymbol && hasFoundOperationArithmeticSymbol && isArithmeticOperationSymbol(pos) && varName.length() > 0 && isDigits(varName)) {
				PKB::getPKBInstance()->insertConst(atoi(varName.c_str()));
			}

			if (isArithmeticSymbol(pos)) {
				varName.clear();
			}

			if (openParenthesisCounter < closeParenthesisCounter) {
				setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_EXTRA_CLOSE_PARENTHESIS, pos);
				setIsInvalidSourceCode();
			}

			data.push_back(sourceCode.at(pos));
			prevCharPos = pos;
		}
		++pos;
		validatePointerIsWithinRange(pos);
	}

	if (isValidSourceCode && !(isAlphaNumeric(prevCharPos) || isParenthesisCloseSymbol(prevCharPos))) {
		setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_LAST_CHAR, pos);
		setIsInvalidSourceCode();
	}

	if (isValidSourceCode && openParenthesisCounter != closeParenthesisCounter) {
		setErrorMsg(ERROR_MSG_INVALID_STMT_ASSIGN_OPEN_CLOSE_PARENTHESIS_COUNT, pos);
		setIsInvalidSourceCode();
	}

	updateAssignPatternMap(stmtNo, data);

	if (isValidSourceCode && varName.length() > 0 && isalpha(varName.at(0))) {
		int varID = PKB::getPKBInstance()->insertVar(varName);
		validateID(varID);

		PKB::getPKBInstance()->setUses(procID, stmtNo, varID);
		for (list<int>::iterator it1 = parentList.begin(); it1 != parentList.end(); ++it1) {
			int parentProgLineNum = *it1;
			PKB::getPKBInstance()->setStmtUses(parentProgLineNum, varID);
		}
	}

	if (isValidSourceCode && varName.length() > 0 && isDigits(varName)) {
		PKB::getPKBInstance()->insertConst(atoi(varName.c_str()));
	}

	++pos;
	validatePointerIsWithinRange(pos);
	

	bool isEndOfConsecutiveCloseBraces = false;
	int statementLevel = numOfOpenBracesCounter - numOfCloseBracesCounter;
	int numOfCloseBraces = 0;

	processParentList(parentList, stmtNo);
	processFollowStack(followStack, stmtNo);

	while (!isEndOfConsecutiveCloseBraces && pos < (int) sourceCode.length()) {
		if (isCurlyCloseBraceSymbol(pos) || isSpace(pos)) {
			if (isCurlyCloseBraceSymbol(pos)) {
				popFollowStack(followStack);
				popParentList(parentList);
				++numOfCloseBracesCounter;
				++numOfCloseBraces;
			}
			++pos;
		} else {
			isEndOfConsecutiveCloseBraces = true;
		}
	}

	updateStmtLst(stmtNo);

	PKB::getPKBInstance()->updateSourceList(stmtNo, statementLevel, numOfCloseBraces, STMT_TYPE_ASSIGN_STRING, data);
	++stmtNo;
}

/*
TODO: Update PKB assign pattern map
*/
void Parser::updateAssignPatternMap(int stmtNo, string data) {
	if (isValidSourceCode) {
		pair<string, string> assignPair = getSplitAssignStatement(data);
		PKB::getPKBInstance()->setAssignPattern(stmtNo, assignPair.first, assignPair.second);
	}
}

/*
TODO: Update PKB while pattern map
*/
void Parser::updateWhilePatternMap(int stmtNo, int varID) {
	if (isValidSourceCode) {
		PKB::getPKBInstance()->setWhilePattern(stmtNo, varID);
	}
}

/*
TODO: Update PKB if pattern map
*/
void Parser::updateIfPatternMap(int stmtNo, int varID) {
	if (isValidSourceCode) {
		PKB::getPKBInstance()->setIfPattern(stmtNo, varID);
	}
}

/*
TODO: Check if is procedure keyword. If found, return true, else false
*/
bool Parser::hasFoundProcedureKeyWord(int& pos) {
	if (pos + STMT_TYPE_PROC_STRING.length() <= sourceCode.length() - 1) {
		return (sourceCode.substr(pos, (int) STMT_TYPE_PROC_STRING.length()).find(STMT_TYPE_PROC_STRING) != string::npos
			&& isSpace(pos + (int) STMT_TYPE_PROC_STRING.length()));
	}
	return false;
}

/*
TODO: Check if is while keyword. If found, return true, else false
*/
bool Parser::hasFoundWhileKeyWord(int& pos) {
	if (pos + STMT_TYPE_WHILE_STRING.length() <= sourceCode.length() - 1) {
		return (sourceCode.substr(pos, (int) STMT_TYPE_WHILE_STRING.length()).find(STMT_TYPE_WHILE_STRING) != string::npos
			&& isSpace(pos + (int) STMT_TYPE_WHILE_STRING.length()));
	}
	return false;
}

/*
TODO: Check if is if keyword. If found, return true, else false
*/
bool Parser::hasFoundIfKeyWord(int& pos) {
	if (pos + STMT_TYPE_IF_STRING.length() <= sourceCode.length() - 1) {
		return (sourceCode.substr(pos, (int) STMT_TYPE_IF_STRING.length()).find(STMT_TYPE_IF_STRING) != string::npos
			&& isSpace(pos + (int) STMT_TYPE_IF_STRING.length()));
	}
	return false;
}

/*
TODO: Check if is then keyword. If found, return true, else false
*/
bool Parser::hasFoundThenKeyWord(int& pos) {
	if (pos + STMT_TYPE_THEN_STRING.length() <= sourceCode.length() - 1) {
		return (sourceCode.substr(pos, (int) STMT_TYPE_THEN_STRING.length()).find(STMT_TYPE_THEN_STRING) != string::npos);
	}
	return false;
}

/*
TODO: Check if is else keyword. If found, return true, else false
*/
bool Parser::hasFoundElseKeyWord(int& pos) {
	if (pos + STMT_TYPE_ELSE_STRING.length() <= sourceCode.length() - 1) {
		return (sourceCode.substr(pos, (int) STMT_TYPE_ELSE_STRING.length()).find(STMT_TYPE_ELSE_STRING) != string::npos);
	}
	return false;
}

/*
TODO: Check if is call keyword. If found, return true, else false
*/
bool Parser::hasFoundCallKeyWord(int& pos) {
	if (pos + STMT_TYPE_CALL_STRING.length() <= sourceCode.length() - 1) {
		return (sourceCode.substr(pos, (int) STMT_TYPE_CALL_STRING.length()).find(STMT_TYPE_CALL_STRING) != string::npos
			&& isSpace(pos + (int) STMT_TYPE_CALL_STRING.length()));
	}
	return false;
}

/*
TODO: Check if character at the position is alphanumeric. If yes, return true, else false
*/
bool Parser::isAlphaNumeric(int pos) {
	if (isalnum(sourceCode.at(pos))) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is alpha. If yes, return true, else false
*/
bool Parser::isAlpha(int pos) {
	if (isalpha(sourceCode.at(pos))) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is space. If yes, return true, else false
*/
bool Parser::isSpace(int pos) {
	if (sourceCode.at(pos) == SPACE_WHITE_SPACE_CHAR || sourceCode.at(pos) == SPACE_TAB_CHAR || sourceCode.at(pos) == SPACE_NEW_LINE_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is arithmetic symbol. If yes, return true, else false
*/
bool Parser::isArithmeticSymbol(int pos) {
	if (sourceCode.at(pos) == ARITHMETIC_EQUAL_CHAR || sourceCode.at(pos) == ARITHMETIC_PLUS_CHAR || sourceCode.at(pos) == ARITHMETIC_MINUS_CHAR
		|| sourceCode.at(pos) == ARITHMETIC_TIMES_CHAR || sourceCode.at(pos) == ARITHMETIC_DIVIDES_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is open brace. If yes, return true, else false
*/
bool Parser::isCurlyOpenBraceSymbol(int pos) {
	if (sourceCode.at(pos) == CURLY_OPEN_BRACE_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is close brace. If yes, return true, else false
*/
bool Parser::isCurlyCloseBraceSymbol(int pos) {
	if (sourceCode.at(pos) == CURLY_CLOSE_BRACE_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Check if string is digit. If yes, return true, else false
*/
bool Parser::isDigits(string varName)
{
	return std::all_of(varName.begin(), varName.end(), ::isdigit);
}

/*
TODO: Check if character at the position is equal symbol. If yes, return true, else false
*/
bool Parser::isArithmeticEqualSymbol(int pos) {
	if (sourceCode.at(pos) == ARITHMETIC_EQUAL_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is operation symbol. If yes, return true, else false
*/
bool Parser::isArithmeticOperationSymbol(int pos) {
	if (sourceCode.at(pos) == ARITHMETIC_TIMES_CHAR || sourceCode.at(pos) == ARITHMETIC_DIVIDES_CHAR
		|| sourceCode.at(pos) == ARITHMETIC_PLUS_CHAR || sourceCode.at(pos) == ARITHMETIC_MINUS_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is open parenthesis. If yes, return true, else false
*/
bool Parser::isParenthesisOpenSymbol(int pos) {
	if (sourceCode.at(pos) == PARENTHESIS_OPEN_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is close parenthesis. If yes, return true, else false
*/
bool Parser::isParenthesisCloseSymbol(int pos) {
	if (sourceCode.at(pos) == PARENTHESIS_CLOSE_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Check if character at the position is parenthesis. If yes, return true, else false
*/
bool Parser::isParenthesisSymbol(int pos) {
	if (sourceCode.at(pos) == PARENTHESIS_OPEN_CHAR || sourceCode.at(pos) == PARENTHESIS_CLOSE_CHAR) {
		return true;
	}
	return false;
}

/*
TODO: Set invalid code
*/
void Parser::setIsInvalidSourceCode() {
	isValidSourceCode = false;
}

/*
TODO: Push var id into var stack
*/
void Parser::pushVarStack(stack<list<int>>& varStack, int varID) {
	if (!varStack.empty()) {
		varStack.top().push_back(varID);
	}
}

/*
TODO: Process follow stack and update PKB follows map
*/
void Parser::processFollowStack(stack<stack<int>>& followStack, int stmtNo) {
	if (!followStack.empty()) {
		int afterProgLineNum = stmtNo;
		if (!followStack.top().empty()) {
			int beforeProgLineNum = followStack.top().top();
			PKB::getPKBInstance()->setFollows(beforeProgLineNum, afterProgLineNum);
		}
		followStack.top().push(afterProgLineNum);
	}
}

/*
TODO: Process parent stack and update PKB parent map
*/
void Parser::processParentList(list<int>& parentList, int stmtNo) {
	if (!parentList.empty()) {
		int parentProgLineNum = parentList.front();
		int childProgLineNum = stmtNo;
		PKB::getPKBInstance()->setParent(parentProgLineNum, childProgLineNum);
	}
}

/*
TODO: Update PKB stmtLst
*/
void Parser::updateStmtLst(int stmtNo) {
	vector<Statement> sourceList = PKB::getPKBInstance()->getSourceList();
	if (sourceList.at(sourceList.size() - 1).getstatementType() == STMT_TYPE_PROC_STRING || sourceList.at(sourceList.size() - 1).getstatementType() == STMT_TYPE_IF_STRING
		|| sourceList.at(sourceList.size() - 1).getstatementType() == STMT_TYPE_ELSE_STRING || sourceList.at(sourceList.size() - 1).getstatementType() == STMT_TYPE_WHILE_STRING) {
		PKB::getPKBInstance()->insertStmtLst(stmtNo);
	}
}

/*
TODO: pop the first element in variable stack
*/
void Parser::popVarStack(stack<list<int>>& varStack) {
	if (!varStack.empty()) {
		varStack.pop();
	}
}

/*
TODO: pop the first element in follow stack
*/
void Parser::popFollowStack(stack<stack<int>>& followStack) {
	if (!followStack.empty()) {
		followStack.pop();
	}
}

/*
TODO: pop the first element in parent stack
*/
void Parser::popParentList(list<int>& parentList) {
	if (!parentList.empty()) {
		parentList.pop_front();
	}
}

/*
TODO: Iterate if until it point to non space character
*/
void Parser::skipSpace(int& pos) {
	validatePointerIsWithinRange(pos);
	while (isValidSourceCode && isSpace(pos)) {
		++pos;
		validatePointerIsWithinRange(pos);
	}
}