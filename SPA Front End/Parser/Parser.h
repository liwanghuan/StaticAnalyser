#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "../../PKB/PKB.h"

using namespace std;

class Parser {
public:
	Parser();
	~Parser();

	// method of reading and initializing the source code
	vector<Statement> processSourceCode(string);
private:

	const int INIT_COUNTER_NUM = 0;
	const int INIT_POINTER_POSITION = 0;
	const int INIT_PROC_ID = -1;
	const int INIT_PROC_LINE_NUM = 1;

	const char ARITHMETIC_DIVIDES_CHAR = '/';
	const char ARITHMETIC_EQUAL_CHAR = '=';
	const char ARITHMETIC_MINUS_CHAR = '-';
	const char ARITHMETIC_PLUS_CHAR = '+';
	const char ARITHMETIC_TIMES_CHAR = '*';

	const char SPACE_NEW_LINE_CHAR = '\n';
	const char SPACE_TAB_CHAR = '\t';
	const char SPACE_WHITE_SPACE_CHAR = ' ';

	const char CURLY_CLOSE_BRACE_CHAR = '}';
	const char CURLY_OPEN_BRACE_CHAR = '{';

	const char PARENTHESIS_CLOSE_CHAR = ')';
	const char PARENTHESIS_OPEN_CHAR = '(';

	const char SEMI_COLON_CHAR = ';';

	const string EMPTY_STRING = "";

	const string STMT_TYPE_ASSIGN_STRING = "assign";
	const string STMT_TYPE_CALL_STRING = "call";
	const string STMT_TYPE_ELSE_STRING = "else";
	const string STMT_TYPE_IF_STRING = "if";
	const string STMT_TYPE_PROC_STRING = "procedure";
	const string STMT_TYPE_THEN_STRING = "then";
	const string STMT_TYPE_WHILE_STRING = "while";

	const string ERROR_MSG_CHAR_POSITION = "Error at character position: ";
	const string ERROR_MSG_INVALID_PROC_COUNT = "Only one procedure should exist in the source code!";
	const string ERROR_MSG_INVALID_SOURCE_CODE = "Invalid souce code!";
	const string ERROR_MSG_INVALID_SPACE_CHAR = "Space character is to be expected!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_ARITH_SYMBOL_BEFORE_CLOSE_PARENTHESIS = "Assignment statement should not have arithmetic symbol followed by close parenthesis!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_CHAR = "Assignment statement should only contain alphanumeric and arithmetic symbol!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_CONSEC_ARITH_SYMBOL = "Assignment statement should not have consecutive arithmetic symbol!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_CONSEC_OPPO_PARENTHESIS = "Assignment statement should not have consecutive opposite parenthesis!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_EQUAL_AFTER_OPERATOR = "Assignment statement should have  equal arithmetic symbol appear only before parenthesis and operator!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_EQUAL_APPEARED_TWICE = "Assignment statement should not have equal arithmetic symbol appearing twice";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_EXTRA_CLOSE_PARENTHESIS = "Assignment statement should not have extra close parenthesis!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_LAST_CHAR = "Assignment statement last character should be either alphanumeric or close parenthesis!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_MISSING_ARITH_SYMBOL = "Assignment statement is missing arithmetic symbol between two expressions!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_OPEN_CLOSE_PARENTHESIS_COUNT = "Assignment statement should have equal number of open and close parenthesis!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_OPEN_PARENTHESIS_BEFORE_ARITH_SYMBOL = "Assignment statement should not have open parenthesis followed by arithmetic symbol!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_INVALID_CHAR_BEFORE_CLOSE_PARENTHESIS = "Assignment statement should allow only alphanumeric before close parenthesis!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_INVALID_CHAR_BEFORE_OPEN_PARENTHESIS = "Assignment statement should allow only arithmetic symbol or open parenthesis before open parenthesis!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_UNDEFINED_MOD_VAR = "Assignment statement with modifying variable name undefined!";
	const string ERROR_MSG_INVALID_STMT_ASSIGN_VAR_DIGIT_FIRST_CHAR = "Assignment statement should not contain variable name with numerical number at first character!";
	const string ERROR_MSG_INVALID_STMT_IF_THEN_NOT_FOUND = "If statement should have \"then\" keyword appearing after specifying variable name!";
	const string ERROR_MSG_INVALID_SOURCE_CODE_OPEN_CLOSE_CURLY_BRACE_COUNT = "Source Code should have equal number of open and close curly braces!";
	const string ERROR_MSG_INVALID_VAR_NAME_CHAR = "Procedure or Variable name should contain only alphanumeric!";
	const string ERROR_MSG_INVALID_VAR_NAME_FIRST_CHAR = "Procedure or Variable name first character should contain only letter!";
	const string ERROR_MSG_MISSING_ELSE_CONTAINER = "If cointainer should be followed by else container!";
	const string ERROR_MSG_MISSING_PROCEDURE_KEY_WORD = "Missing procedure keyword!";
	const string ERROR_MSG_MISSING_THEN_KEY_WORD = "Missing then keyword!";
		
	string sourceCode;
	string errorMsg;

	int ifCounter = 0;
	int elseCounter = 0;

	pair<string, string> getSplitAssignStatement(string);

	void createSourceList();
	void exitAndShowErrorIfInvalidSourceCode();
	void initializeSourceCode(string code);
	void setErrorMsg(string, int);
	void sortLists();


	void processStatement(int&, int&, int&, int&, int&, list<int>&, stack<stack<int>>&);
	void processAssignStatement(int&, int&, int&, int&, int, list<int>&, stack<stack<int>>&);
	void processProcedureStatement(int&, int&, int&, int&, int&);
	void processWhileStatement(int&, int&, int&, int&, int, list<int>&, stack<stack<int>>&);
	void processIfStatement(int&, int&, int&, int&, int, list<int>&, stack<stack<int>>&);
	void processElseStatement(int&, int&, int&, int&, list<int>&, stack<stack<int>>&);
	void processCallStatement(int&, int&, int&, int&, int, list<int>&, stack<stack<int>>&);

	void processFollowStack(stack<stack<int>>&, int);
	void processParentList(list<int>&, int);

	void updateStmtLst(int);

	void updateAssignPatternMap(int, string);
	void updateWhilePatternMap(int, int);

	void updateIfPatternMap(int stmtNo, int varID);

	void popVarStack(stack<list<int>>&);
	void popFollowStack(stack<stack<int>>&);
	void popParentList(list<int>&);

	void pushVarStack(stack<list<int>>&, int);

	void skipSpace(int&);
	void setIsInvalidSourceCode();

	bool isAlpha(int);
	bool isAlphaNumeric(int);
	bool isArithmeticEqualSymbol(int);
	bool isArithmeticOperationSymbol(int);
	bool isArithmeticSymbol(int);
	bool isCurlyOpenBraceSymbol(int);
	bool isCurlyCloseBraceSymbol(int);
	bool isDigits(string);
	bool isParenthesisCloseSymbol(int);
	bool isParenthesisOpenSymbol(int);
	bool isParenthesisSymbol(int);
	bool isSpace(int);
	bool isValidSourceCode;

	bool hasFoundCallKeyWord(int&);
	bool hasFoundElseKeyWord(int&);
	bool hasFoundIfKeyWord(int&);
	bool hasFoundProcedureKeyWord(int&);
	bool hasFoundThenKeyWord(int&);
	bool hasFoundWhileKeyWord(int&);

	void validateID(int id);
	void validateLetterNameFirstChar(int);
	void validateNameChar(int);
	void validatePointerIsWithinRange(int);
	void validateSpaceChar(int);
};