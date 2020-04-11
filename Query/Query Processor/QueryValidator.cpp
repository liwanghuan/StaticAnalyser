#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

#include "QueryValidator.h"
#include "../../SPA Logs/SPALogs.h"

using namespace std;

const vector<string> VARIABLETYPES = { "variable", "constant", "stmt", "assign", "while", "if", "procedure", "call", "prog_line", "stmtLst" };

const vector<string> VALID_KEYWORDS = { "constant", "stmt", "stmtLst", "assign", "while", "if", "procedure", "call", "prog_line", "Select",
"Modifies", "Uses", "Parent", "Parent*", "Follows", "Follows*", "Pattern", "Next", "Next*", "Calls", "Calls*", "Affects", "Affects*",
"with", "and", "such", "that" };

const char SYMBOL_SEMICOLON = ';';
const char SYMBOL_SPACE = ' ';
const char SYMBOL_COMMA = ',';
const char SYMBOL_QUOTE = '\"';
const char SYMBOL_OPEN_BRACKET = '(';
const char SYMBOL_CLOSE_BRACKET = ')';
const char SYMBOL_EQUALS = '=';
const char SYMBOL_FULLSTOP = '.';
const char SYMBOL_UNDERSCORE_CHAR = '_';

const string VARIABLETYPE_VARIABLE = "variable";
const string VARIABLETYPE_STRING = "string";
const string VARIABLETYPE_SUBSTRING = "substring";
const string VARIABLETYPE_CONSTANT = "constant";
const string VARIABLETYPE_ASSIGN = "assign";
const string VARIABLETYPE_WHILE = "while";
const string VARIABLETYPE_IF = "if";
const string VARIABLETYPE_PROCNAME = "procName";
const string VARIABLETYPE_VARNAME = "varName";
const string VARIABLETYPE_PROG_LINE = "prog_line";
const string VARIABLETYPE_NUMBER = "number";
const string VARIABLETYPE_ALL = "all";
const string VARIABLETYPE_BOOLEAN = "BOOLEAN";
const string VARIABLETYPE_STMTLST = "stmtLst";

const string SYMBOL_UNDERSCORE_STRING = "_";

const string VARIABLETYPE_CALLPROCNAME = "callProcName";
const string VARIABLETYPE_CALLSTMT = "callStmt";
const string VARIABLETYPE_VALUE = "value";
const string VARIABLETYPE_CALL = "call";
const string VARIABLETYPE_PROCEDURE = "procedure";
const string VARIABLETYPE_STMT = "stmt#";

const string RELATIONSHIP_TYPE_SELECT = "Select";
const string RELATIONSHIP_TYPE_SUCHTHAT = "such that";
const string RELATIONSHIP_TYPE_SUCH = "such";
const string RELATIONSHIP_TYPE_THAT = "that";
const string RELATIONSHIP_TYPE_PATTERN = "pattern";
const string RELATIONSHIP_TYPE_PATTERN_ASSIGN = "patternAssign";
const string RELATIONSHIP_TYPE_PATTERN_WHILE = "patternWhile";
const string RELATIONSHIP_TYPE_PATTERN_IF = "patternIf";
const string RELATIONSHIP_TYPE_WITH = "with";
const string RELATIONSHIP_TYPE_WITH_CONSTANT = "withConstant";
const string RELATIONSHIP_TYPE_WITH_STRING = "withString";
const string RELATIONSHIP_TYPE_AND = "and";

const string EMPTY_QUERY = "";

const string VALID_QUERY = "VALID";
const string INVALID_QUERY = "INVALID";
const string INVALID_BOOLEAN_QUERY = "INVALID_BOOLEAN";
int BOOLEAN_FLAG;

/*
 * For debugging purposes
 */
void QueryValidator::printQuery(string subquery)
{
	cout << "\n====================Query contains====================\n" << endl;

	// Print out all declarations
	for (int i = 0; i < queryObj.getDeclarationList().size(); i++) {
		cout << "Declaration (Variable name): " << queryObj.getDeclarationList().at(i).getVarName() << " Variable Type: " << queryObj.getDeclarationList().at(i).getVarType() << "\n" << endl;
	}

	// Print out select and check if it's boolean or variable
	for (int i = 0; i < queryObj.getSelectList().size(); i++) {
		cout << "Select (Variable name): " << queryObj.getSelectList().at(i).getVarName() << " Select (Type): " << queryObj.getSelectList().at(i).getVarType() << "\n" << endl;
	}

	// Print out all clauses
	for (int i = 0; i < queryObj.getClauseList().size(); i++) {
		cout << "Clause Type: " << queryObj.getClauseList().at(i).getClauseType() << "\n" << endl;
		cout << "Clause (First arg): " << queryObj.getClauseList().at(i).getFirstArg() << " First arg Type: " << queryObj.getClauseList().at(i).getFirstArgType() << "\n" << endl;
		cout << "Clause (Second arg): " << queryObj.getClauseList().at(i).getSecondArg() << " Second arg Type: " << queryObj.getClauseList().at(i).getSecondArgType() << "\n" << endl;
		cout << "Clause (Main arg): " << queryObj.getClauseList().at(i).getMainArg() << " Main arg Type: " << queryObj.getClauseList().at(i).getMainArgType() << "\n" << endl;
	}

	// Print out query to be validated
	cout << "Current query: " << subquery << "\n" << endl;
	cout << "====================End of Query object====================\n" << endl;
}

/*
 * The main control of the Query Validator
 */
string QueryValidator::isValidDeclarationAndQuery(string query)
{
	// Initialise BOOLEAN_FLAG to 0
	BOOLEAN_FLAG = 0;

	// Split the query by SEMICOLON to get all declarations
	vector<string> splitStr = split(trim(query), SYMBOL_SEMICOLON);

	if (splitStr.at(0).empty()) {
		return INVALID_QUERY;
	}

	int size = splitStr.size(), index = 0;

	// Store all declarations into Declaration Object
	for (index; index < size - 1; index++) {
		if (!isValidDeclaration(splitStr.at(index))) {
			return INVALID_QUERY;
		}
	}

	// Store Select and Clauses with their respective Select/Clauses Object
	if (!isValidQuery(splitStr.back())) {
		// It is Select BOOLEAN but the query is invalid
		if (BOOLEAN_FLAG == 1) {
			SPALogs::getSPALogsInstance()->logging("The query is INVALID and is a BOOLEAN", query);
			return INVALID_BOOLEAN_QUERY;
		}
		SPALogs::getSPALogsInstance()->logging("The query is INVALID", query);
		return INVALID_QUERY;
	}

	// Print query here for debugging purposes and to make sure that the correct query is passed to Query Evaluator
	// printQuery(query);
	SPALogs::getSPALogsInstance()->logging("The query is VALID", query);
	// Clear the map
	map.clear();
	// cout << "===================================QUERY VALIDATOR ENDS HERE===================================" << endl;
	return VALID_QUERY;
}

// Query Object is created for each query to be passed to Query Evaluator
Query QueryValidator::getQuery()
{
	return queryObj;
}

/*
 *	To check if Declaration given is valid
 *	If valid declaration, returns true and fills up Declaration Object
 *	If invalid declaration, returns false and goes to next query
 */
bool QueryValidator::isValidDeclaration(string declaration) {

	// Split the declaration(s) by spaces
	vector<string> declarationArr = split(declaration, SYMBOL_SPACE, 2);
	int declarationArrSize = declarationArr.size();

	if (declarationArrSize < 2) {
		return false;
	}

	// Checks to make sure that the declarations are valid
	if (!(find(VARIABLETYPES.begin(), VARIABLETYPES.end(), declarationArr.at(0)) != VARIABLETYPES.end())) {
		SPALogs::getSPALogsInstance()->logging("Declarations is not valid!", declaration);
		return false;
	}

	// Checks if there are multiple variables declared in a particular declaration
	vector<string> synonym = split(declarationArr.at(1), SYMBOL_COMMA);
	int synonymSize = synonym.size();

	// Cannot have a declaration with no declared variables
	// E.g. assign; variable;
	if (synonymSize < 1) {
		SPALogs::getSPALogsInstance()->logging("Declaration has no declared variables!", declaration);
		return false;
	}

	for (int i = 0; i < synonymSize; i++) {
		// Checks if variable name is valid
		if (!isValidVariableName(synonym.at(i))) {
			SPALogs::getSPALogsInstance()->logging("Variable Name is not valid!", declaration);
			return false;
		}
		else if (!isalpha(synonym.at(i).at(0))) {
			SPALogs::getSPALogsInstance()->logging("Variable Name is not valid! (Cannot start with number)", declaration);
			return false;
		}
		else {
			// Check if variable was declared before
			if (map.find(synonym.at(i)) != map.end()) {
				return false;
			}

			// Maps the declared variable to their respective declaration
			// Stores the declaration to the Declaration object in order
			map[synonym.at(i)] = declarationArr.at(0);
			declarationObj.setVarName(synonym.at(i));
			declarationObj.setVarType(toLower(declarationArr.at(0)));
			queryObj.addDeclaration(declarationObj);
			clearDeclarationObject();
			SPALogs::getSPALogsInstance()->logging("Declaration is mapped.", declaration);
		}

	}
	return true;
}

/*
 *	To check if Select and the Clauses after that are valid
 *	If valid Select, stores selection into Select Object and move onto clauses
 *	If invalid Select, returns false and moves on to next query
 *	If valid Clause, stores clause(s) into Clause Object and return true
 *	If invalid Clause, returns false and goes to next query
 */
bool QueryValidator::isValidQuery(string query) {

	// Split Selection by spaces
	vector<string> clausesArr = split(query, SYMBOL_SPACE, 2);

	// Make sure that the first word is always "Select"
	// Take note that "Select" is case sensitive
	if (clausesArr.at(0).compare(RELATIONSHIP_TYPE_SELECT) != 0) {
		SPALogs::getSPALogsInstance()->logging("\"Select\" is not properly declared!", query);
		return false;
	}

	 // Check if the selection is a tuple or not
	 // Example of tuple: Select <x, y> || Select <x.varName, y.procName>
	 // Example of non-tuple: Select v
	if (clausesArr.at(1).at(0) == '<') {
		// Query is a tuple
		clausesArr = split(clausesArr.at(1), '>', 2);
		clausesArr.at(0) = clausesArr.at(0).substr(1, clausesArr.at(0).size() - 1);

		vector<string> wordsArr = split(clausesArr.at(0), SYMBOL_COMMA); // Contains all the Selects in the tuple < ... > 
		vector<string> variable, variableType;

		// A loop to traverse all selections in the tuple
		for (int i = 0; i < wordsArr.size(); i++) {
			if (isVariableNameExists(wordsArr.at(i))) {
				// It is not v.varName or anything similar
				selectObj.setVarName(wordsArr.at(i));
				selectObj.setVarType(getVariableType(wordsArr.at(i)));
				queryObj.addSelect(selectObj);
				clearSelectObject();
			}
			else {
				// It is a "special" selection
				// Example: v.varName, p.procName, etc
				vector<string> selectExtra = split(wordsArr.at(i), SYMBOL_FULLSTOP);

				if (!specialSelection(selectExtra)) {
					SPALogs::getSPALogsInstance()->logging("Invalid <tuple> selection!", query);
					return false;
				}
			}
		}
	}
	else {
		// Query is not a tuple
		clausesArr = split(clausesArr.at(1), SYMBOL_SPACE, 2);

		if (isVariableNameExists(clausesArr.at(0))) {
			selectObj.setVarName(clausesArr.at(0));
			selectObj.setVarType(toLower(getVariableType(clausesArr.at(0))));
			queryObj.addSelect(selectObj);
			clearSelectObject();
		}
		else if (clausesArr.at(0).compare(VARIABLETYPE_BOOLEAN) == 0) {
			// Selection type is BOOLEAN
			selectObj.setVarName("");
			selectObj.setVarType(toLower(VARIABLETYPE_BOOLEAN));
			queryObj.addSelect(selectObj);
			BOOLEAN_FLAG = 1; // Set BOOLEAN flag to 1 to check for potential invalid queries but returns BOOLEAN
			clearSelectObject();
		}
		else {
			// It is a "special" selection
			// Example: v.varName, p.procName, etc
			vector<string> selectExtra = split(clausesArr.at(0), SYMBOL_FULLSTOP);
			
			if (!specialSelection(selectExtra)) {
				SPALogs::getSPALogsInstance()->logging("Invalid selection!", query);
				return false;
			}
		}
	}

	// Only have declaration and selection with no clauses
	if (clausesArr.size() == 1) {
		SPALogs::getSPALogsInstance()->logging("Query has no clauses.", query);
		return true;
	}

	// A temporary string to store the previous clause to check if "and" is valid
	string prevClause = "";
	bool isClauseValid;

	// A loop to check for all clauses until there is no clause left
	while (1) {
		// There are no more clauses
		if ((clausesArr.at(1).size() > 0) && (clausesArr.at(1).at(0) == NULL) || clausesArr.at(1).size() == 0) {
			break;
		}

		// Split by whitespace
		clausesArr = split(clausesArr.at(1), SYMBOL_SPACE, 2);

		// No more clauses to process
		if (clausesArr.empty()) {
			return false;
		}

		// Check if the first clause is a "such that" clause
		if (clausesArr.at(0).compare("such") == 0) {
			clausesArr = split(clausesArr.at(1), SYMBOL_SPACE, 2);
			if (clausesArr.size() != 2 || clausesArr.at(0).compare("that") != 0) {
				return false;
			}

			isClauseValid = findSuchThatClause(clausesArr.at(1));
			prevClause = RELATIONSHIP_TYPE_SUCHTHAT;
		}
		else if (clausesArr.at(0).compare(RELATIONSHIP_TYPE_PATTERN) == 0) {
			// Check if the first clause is a "pattern" clause
			isClauseValid = findPatternClause(clausesArr.at(1));
			prevClause = RELATIONSHIP_TYPE_PATTERN;
		}
		else if (clausesArr.at(0).compare(RELATIONSHIP_TYPE_WITH) == 0) {
			// Check if the first clause is a "with" clause
			isClauseValid = findWithClause(clausesArr.at(1));
			prevClause = RELATIONSHIP_TYPE_WITH;
		}
		else if (clausesArr.at(0).compare(RELATIONSHIP_TYPE_AND) == 0) {
			// Check if the first clause is an "and" clause
			// If the first clause is an "and", it will return as invalid
			if (prevClause.compare(RELATIONSHIP_TYPE_SUCHTHAT) == 0) {
				isClauseValid = findSuchThatClause(clausesArr.at(1));
				prevClause = RELATIONSHIP_TYPE_SUCHTHAT;
			}
			else if (prevClause.compare(RELATIONSHIP_TYPE_PATTERN) == 0) {
				isClauseValid = findPatternClause(clausesArr.at(1));
				prevClause = RELATIONSHIP_TYPE_PATTERN;
			}
			else if (prevClause.compare(RELATIONSHIP_TYPE_WITH) == 0) {
				isClauseValid = findWithClause(clausesArr.at(1));
				prevClause = RELATIONSHIP_TYPE_WITH;
			}
			else {
				// Returns false if the first clause is an "and" as there is no previous clause
				return false;
			}
		}
		else {
			break;
		}

		// Checks if the syntax of the next clause is valid
		// Example: Select a1 such that Affects*(s1, s2) and Affects*(s3, s4) Affects*(s5, s6) is invalid because there's no "and"
		vector<string> cornerCaseClause = split(clausesArr.at(1), SYMBOL_SPACE, 2);
		if (!((cornerCaseClause.at(0).compare(RELATIONSHIP_TYPE_SUCH) == 0) || (cornerCaseClause.at(0).compare(RELATIONSHIP_TYPE_PATTERN) == 0) || (cornerCaseClause.at(0).compare(RELATIONSHIP_TYPE_AND) == 0) || (cornerCaseClause.at(0).compare(RELATIONSHIP_TYPE_WITH) == 0) || (cornerCaseClause.at(0).compare(EMPTY_QUERY) == 0))) {
			return false;
		}

		// Returns false if a particular clause is invalid
		if (!isClauseValid) {
			return false;
		}
	}

	return true;
}

bool QueryValidator::specialSelection(vector<string> selectExtra)
{
	if (isVariableNameExists(selectExtra.at(0))) {
		selectObj.setVarName(selectExtra.at(0));
		selectObj.setVarType(getVariableType(selectExtra.at(0)));

		if (getVariableType(selectExtra.at(0)).compare(VARIABLETYPE_CALL) == 0) {
			if (selectExtra.at(1).compare(VARIABLETYPE_PROCNAME) == 0) {
				// call.procName
				selectObj.setVarType(toLower(VARIABLETYPE_CALLPROCNAME));
			}
			else if (selectExtra.at(1).compare(VARIABLETYPE_STMT) == 0) {
				// call.stmt#
				selectObj.setVarType(toLower(VARIABLETYPE_CALLSTMT));
			}
			else {
				return false;
			}
		}
		else if (getVariableType(selectExtra.at(0)).compare(VARIABLETYPE_VARIABLE) == 0) {
			// variable.varName
			if (selectExtra.at(1).compare(VARIABLETYPE_VARNAME) != 0) {
				return false;
			}
		}
		else if (getVariableType(selectExtra.at(0)).compare(VARIABLETYPE_PROCEDURE) == 0) {
			// procedure.procName
			if (selectExtra.at(1).compare(VARIABLETYPE_PROCNAME) != 0) {
				return false;
			}
		}
		else if (getVariableType(selectExtra.at(0)).compare(VARIABLETYPE_CONSTANT) == 0) {
			// constant.value
			if (selectExtra.at(1).compare(VARIABLETYPE_VALUE) != 0) {
				return false;
			}
		}
		else {
			// Everything else can only be (something).stmt#
			if (selectExtra.at(1).compare(VARIABLETYPE_STMT) != 0) {
				return false;
			}
		}

		queryObj.addSelect(selectObj);
		clearSelectObject();
	}
	else {
		return false;
	}

	return true;
}

/*
 * Validate "such that" clauses and stores them into the Query Object
 * If that particular "such that" clause is VALID, return true
 * If that particular "such that" clause is INVALID, return false
 */
bool QueryValidator::findSuchThatClause(string &subquery)
{
	// Splits by "("
	// So if the clause is Follows(4, 5), clausesArr.at(0) will be "Follows" and clausesArr.at(1) will be "4, 5)"
	vector<string> clausesArr = split(subquery, SYMBOL_OPEN_BRACKET, 2);

	// Checks the Relationship Table if the clause is VALID
	if (!relationshipTable.hasRelationship(toLower(clausesArr.at(0))) || clausesArr.size() != 2) {
		return false;
	}

	// If VALID, store the relationship type
	string relationshipType = toLower(clausesArr.at(0));

	if (clausesArr.at(1).find(")") == string::npos) {
		return false;
	}

	clausesArr = split(clausesArr.at(1), SYMBOL_CLOSE_BRACKET, 2);

	if (clausesArr.size() != 2) {
		return false;
	}

	vector<string> variableArr = split(clausesArr.at(0), SYMBOL_COMMA);

	// Make sure that there are only 2 arguments
	if (!relationshipTable.isNumOfArgsEqual(relationshipType, variableArr.size())) {
		return false;
	}

	vector<string> variableTypes(variableArr.size());
	
	// Validates the 2 arguments
	if (!findSuchThatClauseArguments(relationshipType, variableArr, variableTypes)) {
		return false;
	}

	clauseObj.setClauseType(relationshipType);
	clauseObj.setFirstArg(trim(variableArr.at(0)));
	clauseObj.setSecondArg(trim(variableArr.at(1)));

	// All "such that" clauses cannot have constant variable as an argument
	// Argument 1
	if ((isInteger(variableArr.at(0)) && (variableTypes.at(0).compare(VARIABLETYPE_CONSTANT) == 0))) {
		clauseObj.setFirstArgType(VARIABLETYPE_NUMBER);
	}
	else if ((!isInteger(variableArr.at(0)) && (variableTypes.at(0).compare(VARIABLETYPE_CONSTANT) == 0))) {
		return false;
	}
	else {
		clauseObj.setFirstArgType(variableTypes.at(0));
	}

	// Argument 2
	if ((isInteger(variableArr.at(1)) && (variableTypes.at(1).compare(VARIABLETYPE_CONSTANT) == 0))) {
		clauseObj.setSecondArgType(VARIABLETYPE_NUMBER);
	}
	else if ((!isInteger(variableArr.at(1)) && (variableTypes.at(1).compare(VARIABLETYPE_CONSTANT) == 0))) {
		return false;
	}
	else {
		clauseObj.setSecondArgType(variableTypes.at(1));
	}

	queryObj.addClause(clauseObj);
	clearClauseObject();

	subquery = trim(clausesArr.at(1));
	return true;
}

/*
 * Checks if the arguments for a "such that" clause
 * If arguments are VALID, stores them into the Query Object and return true
 * If arguments are INVALID, returns false and moves onto next query
 */
bool QueryValidator::findSuchThatClauseArguments(string relationshipType, vector<string> &variableArr, vector<string> &variableType)
{
	for (int i = 0; i < variableArr.size(); i++) {
		// Check if variable is declared properly
		if (isVariableNameExists(variableArr.at(i))) {
			// Check if argument type is a possible type for that specific clause
			if (!relationshipTable.isArgsValid(relationshipType, i + 1, getVariableType(variableArr.at(i)))) {
				return false;
			}
			else {
				variableType.at(i) = getVariableType(variableArr.at(i));
			}

		}
		else if (isString(variableArr.at(i))) {
			if (!relationshipTable.isArgsValid(relationshipType, i + 1, VARIABLETYPE_STRING)) {
				return false;
			}
			else {
				variableArr.at(i) = variableArr.at(i).substr(1, variableArr.at(i).size() - 2);
				variableType.at(i) = VARIABLETYPE_STRING;
			}

		}
		else if (isInteger(variableArr.at(i))) {
			if (!relationshipTable.isArgsValid(relationshipType, i + 1, VARIABLETYPE_CONSTANT)) {
				return false;
			}
			else {
				variableType.at(i) = VARIABLETYPE_CONSTANT;
			}

		}
		else if (variableArr.at(i).compare(SYMBOL_UNDERSCORE_STRING) == 0) {
			if (!relationshipTable.isArgsValid(relationshipType, i + 1, VARIABLETYPE_ALL)) {
				return false;
			}
			else {
				variableType.at(i) = VARIABLETYPE_ALL;
			}
		}
		else {
			return false;
		}
	}
	return true;
}

/*
 * Checks if the declaration given is a valid declaration based on the keywords given in the const vector<string> above
 */
bool QueryValidator::isValidVariableName(string variableName) {

	if (variableName.length() == 0) {
		return false;
	}

	if (find(VALID_KEYWORDS.begin(), VALID_KEYWORDS.end(), variableName) != VALID_KEYWORDS.end()) {
		return false;
	}

	return true;
}

/*
 * Checks if the arguments for "pattern" clause
 * If arguments are VALID, stores them into the Query Object and return true
 * If arguments are INVALID, returns false and moves onto next query
 */
bool QueryValidator::findPatternClause(string &subquery)
{
	// Splits by "("
	// So if the clause is a(_, _"x+y"_), wordsArr.at(0) will be "a" and wordsArr.at(1) will be "_, _"x+y"_)
	vector<string> wordsArr = split(subquery, SYMBOL_OPEN_BRACKET, 2);

	if (wordsArr.size() != 2) {
		return false;
	}

	// Check if variable name is declared
	if (isVariableNameExists(wordsArr.at(0))) {
		if (getVariableType(wordsArr.at(0)).compare(VARIABLETYPE_ASSIGN) == 0 || getVariableType(wordsArr.at(0)).compare(VARIABLETYPE_WHILE) == 0 || getVariableType(wordsArr.at(0)).compare(VARIABLETYPE_IF) == 0) {
			string relationshipType, synonym, synonymType;

			if (!findPatternType(wordsArr.at(0), relationshipType, synonym, synonymType)) {
				return false;
			}

			if ((relationshipType.compare(RELATIONSHIP_TYPE_PATTERN_IF) == 0) || relationshipType.compare(RELATIONSHIP_TYPE_PATTERN_WHILE) == 0){
				vector<string> variableArr = split(wordsArr.at(1), SYMBOL_COMMA, 2);
				vector<string> variableType(variableArr.size());

				if (!findPatternArgs1(relationshipType, variableArr.at(0), variableType.at(0))) {
					return false;
				}

				if (!findPatternArgs2_WhileAndIf(relationshipType, variableArr.at(1), variableType.at(1))) {
					return false;
				}
				
				clauseObj.setClauseType(relationshipType);
				clauseObj.setMainArg(synonym);
				clauseObj.setMainArgType(synonymType);
				queryObj.addClause(clauseObj);
				clearClauseObject();
				subquery = trim(variableArr.at(1));
			}
			else {
				vector<string> variableArr = split(wordsArr.at(1), SYMBOL_COMMA, 2);
				vector<string> variableType(variableArr.size());

				// Checks if first argument is valid
				if (!findPatternArgs1(relationshipType, variableArr.at(0), variableType.at(0))) {
					return false;
				}

				// Checks if second argument is valid
				if (!findPatternArgs2_Assign(relationshipType, variableArr.at(1), variableType.at(1))) {
					return false;
				}

				clauseObj.setClauseType(relationshipType);
				clauseObj.setMainArg(synonym);
				clauseObj.setMainArgType(synonymType);
				queryObj.addClause(clauseObj);
				clearClauseObject();
				subquery = trim(variableArr.at(1));
			}
		}
	}
	else {
		return false;
	}
	return true;
}

/*
 * Checks if the pattern type is VALID
 * If VALID, store the value as string and return true
 * If INVALID, return false and move onto next query
 */
bool QueryValidator::findPatternType(string word, string &relationshipType, string &synonym, string &synonymType)
{
	if (getVariableType(word).compare(VARIABLETYPE_ASSIGN) == 0) {
		relationshipType = RELATIONSHIP_TYPE_PATTERN_ASSIGN;
		synonym = word;
		synonymType = VARIABLETYPE_ASSIGN;
	}
	else if (getVariableType(word).compare(VARIABLETYPE_WHILE) == 0) {
		relationshipType = RELATIONSHIP_TYPE_PATTERN_WHILE;
		synonym = word;
		synonymType = VARIABLETYPE_WHILE;
	}
	else if (getVariableType(word).compare(VARIABLETYPE_IF) == 0) {
		relationshipType = RELATIONSHIP_TYPE_PATTERN_IF;
		synonym = word;
		synonymType = VARIABLETYPE_IF;
	}
	else {
		return false;
	}

	return true;
}

/*
 * Checks if first argument of pattern is a VALID argument
 * If VALID, stores the argument and argument type as string and return true
 * If INVALID, return false and move onto next query
 */
bool QueryValidator::findPatternArgs1(string relationshipType, string &args1, string &variableType)
{
	if (isVariableNameExists(args1)) {
		variableType = VARIABLETYPE_VARIABLE;
	}
	else if (isString(args1)) {
		args1 = args1.substr(1, args1.size() - 2);
		variableType = VARIABLETYPE_STRING;
	}
	else if (args1.compare(SYMBOL_UNDERSCORE_STRING) == 0) {
		variableType = VARIABLETYPE_ALL;
	}
	else {
		return false;
	}

	clauseObj.setFirstArg(trim(args1));
	clauseObj.setFirstArgType(variableType);

	return true;
}

/*
 * Checks if second argument of pattern is a VALID argument
 * If VALID, stores the argument and argument type as string and return true
 * If INVALID, return false and move onto next query
 */
bool QueryValidator::findPatternArgs2_Assign(string relationshipType, string &subquery, string &variableType)
{
	string variable;

	// Second argument is of type "ALL"
	if ((subquery.at(0) == SYMBOL_UNDERSCORE_CHAR) && ((subquery.at(1) == SYMBOL_CLOSE_BRACKET) || (subquery.at(1) == SYMBOL_SPACE))) {
		variable = SYMBOL_UNDERSCORE_STRING;
		variableType = VARIABLETYPE_ALL;

		if (subquery.size() >= 4) {
			subquery = trim(subquery.substr(3, subquery.size() - 1));
		}
		else {
			subquery = EMPTY_QUERY;
		}
	}
	// Second argument is of type "SUBSTRING"
	// (i.e. Argument is _"x+y"_)
	else if ((subquery.at(0) == SYMBOL_UNDERSCORE_CHAR) && (subquery.at(1) == SYMBOL_QUOTE)) {
		vector<string> splitPatternSubstring1 = split(trim(subquery), SYMBOL_QUOTE, 2);
		vector<string> splitPatternSubstring2 = split(trim(splitPatternSubstring1.at(1)), SYMBOL_QUOTE, 2);

		int leftBracketCount = 0, rightBracketCount = 0;

		leftBracketCount = numOfLeftBrackets(splitPatternSubstring2.at(0));
		rightBracketCount = numOfRightBrackets(splitPatternSubstring2.at(0));

		// The number of brackets in the arguments must match
		if (leftBracketCount != rightBracketCount) {
			return false;
		}

		if (splitPatternSubstring2.at(1).at(0) == SYMBOL_UNDERSCORE_CHAR && (splitPatternSubstring2.at(1).at(1) == SYMBOL_CLOSE_BRACKET || splitPatternSubstring2.at(1).at(1) == SYMBOL_SPACE)) {
			variable = splitPatternSubstring2.at(0);
			variableType = VARIABLETYPE_SUBSTRING;
		}
		else {
			return false;
		}

		if (splitPatternSubstring2.at(1).size() >= 4) {
			subquery = trim(splitPatternSubstring2.at(1).substr(3, splitPatternSubstring2.at(1).size() - 1));
		}
		else {
			subquery = EMPTY_QUERY;
		}
	}
	// Second argument is of type "STRING"
	else if (subquery.at(0) == SYMBOL_QUOTE) {
		vector<string> splitPatternString1 = split(subquery, SYMBOL_QUOTE, 2);
		vector<string> splitPatternString2 = split(splitPatternString1.at(1), SYMBOL_QUOTE, 2);

		int leftBracketCount = 0, rightBracketCount = 0;

		leftBracketCount = numOfLeftBrackets(splitPatternString2.at(0));
		rightBracketCount = numOfRightBrackets(splitPatternString2.at(0));

		// The number of brackets in the arguments must match
		if (leftBracketCount != rightBracketCount) {
			return false;
		}

		if (splitPatternString2.at(1).at(0) == SYMBOL_CLOSE_BRACKET) {
			variable = splitPatternString2.at(0);
			variableType = VARIABLETYPE_STRING;
		}
		else {
			return false;
		}

		if (splitPatternString2.at(1).size() >= 3) {
			subquery = trim(splitPatternString2.at(1).substr(2, splitPatternString2.at(1).size() - 1));
		}
		else {
			subquery = EMPTY_QUERY;
		}

	}
	else {
		return false;
	}
	
	clauseObj.setSecondArg(trim(variable));
	clauseObj.setSecondArgType(variableType);

	return true;
}

bool QueryValidator::findPatternArgs2_WhileAndIf(string relationshipType, string &subquery, string &variableType)
{
	string variable;

	// Second argument is of type "ALL"
	if (subquery.at(0) == SYMBOL_UNDERSCORE_CHAR) {
		variable = SYMBOL_UNDERSCORE_STRING;
		variableType = VARIABLETYPE_ALL;
		clauseObj.setSecondArg(trim(variable));
		clauseObj.setSecondArgType(variableType);
	}
	else {
		return false;
	}

	// Returns true and stop parsing if relationship type is "while" as there is no 3rd argument
	if (relationshipType.compare(RELATIONSHIP_TYPE_PATTERN_WHILE) == 0) {
		vector<string> splitPatternSubstring = split(subquery, SYMBOL_CLOSE_BRACKET, 2);

		// Check if there are extra arguments in pattern "while"
		vector<string> splitPatternSubstringExtraArgument = split(subquery, SYMBOL_UNDERSCORE_CHAR, 2);
		if (splitPatternSubstringExtraArgument.at(1).at(0) != SYMBOL_CLOSE_BRACKET) {
			return false;
		}

		subquery = trim(splitPatternSubstring.at(1));
		return true;
	}

	vector<string> splitPatternSubstring1 = split(subquery, SYMBOL_COMMA, 2);
	try {
		// Third argument is of type "ALL"
		if (!(splitPatternSubstring1.at(1).at(0) == SYMBOL_UNDERSCORE_CHAR) && (splitPatternSubstring1.at(1).at(1) == SYMBOL_CLOSE_BRACKET)) {
			return false;
		}
		else {
			vector<string> splitPatternSubstring2 = split(splitPatternSubstring1.at(1), SYMBOL_CLOSE_BRACKET, 2);
			subquery = trim(splitPatternSubstring2.at(1));
		}
	}
	catch (exception) {
		return false;
	}

	return true;
}

/*
 * Checks if the arguments for "with" clause
 * If arguments are VALID, stores them into the Query Object and return true
 * If arguments are INVALID, returns false and moves onto next query
 */
bool QueryValidator::findWithClause(string &subquery)
{
	string relationshipType;
	vector<string> variableArr, variableType;

	// Check the "with" clause if it is a constant first, then check if string.
	// If it is neither, return false
	// If one of them returns true, it will continue to add the query to their respective objects
	if (!findWithClauseConstant(subquery, relationshipType, variableArr, variableType)) {
		if (!findWithClauseString(subquery, relationshipType, variableArr, variableType)) {
			return false;
		}
	}

	clauseObj.setClauseType(relationshipType);
	queryObj.addClause(clauseObj);
	clearClauseObject();

	return true;
}

/*
 * Checks if the "with" clause is a constant
 * If it is a constant and is VALID, store the value as string and return true
 * If it is a constant but is INVALID, return false and move onto next query
 */
bool QueryValidator::findWithClauseConstant(string &subquery, string &relationshipType, vector<string> &variableArr, vector<string> &variableType)
{
	// Splits by "="
	// So if the clause is c1.value = 25, wordsArr.at(0) will be "c1.value" and wordsArr.at(1) will be "25"
	vector<string> wordsArr = split(subquery, SYMBOL_EQUALS, 2);

	relationshipType = RELATIONSHIP_TYPE_WITH_CONSTANT;

	if (!relationshipTable.isNumOfArgsEqual(relationshipType, wordsArr.size())) {
		return false;
	}

	vector<string> query = split(wordsArr.at(1), SYMBOL_SPACE, 2);
	wordsArr.at(1) = query.at(0);

	for (int i = 0; i < wordsArr.size(); i++) {
		// Check if relationship is in the table and that argument is valid
		// If VALID, store the relationship type to the respective object
		if (isInteger(wordsArr.at(i))) {
			if (relationshipTable.isArgsValid(relationshipType, i + 1, VARIABLETYPE_CONSTANT)) {
				if (i == 0) {
					clauseObj.setFirstArg(wordsArr.at(i));
					clauseObj.setFirstArgType(VARIABLETYPE_NUMBER);
				}
				else {
					clauseObj.setSecondArg(wordsArr.at(i));
					clauseObj.setSecondArgType(VARIABLETYPE_NUMBER);
				}
			}
			else {
				return false;
			}

		}
		else if (isVariableNameExists(wordsArr.at(i)) && getVariableType(wordsArr.at(i)).compare(VARIABLETYPE_PROG_LINE) == 0) {

			if (relationshipTable.isArgsValid(relationshipType, i + 1, VARIABLETYPE_PROG_LINE)) {
				if (i == 0) {
					clauseObj.setFirstArg(wordsArr.at(i));
					clauseObj.setFirstArgType(VARIABLETYPE_PROG_LINE);
				}
				else {
					clauseObj.setSecondArg(wordsArr.at(i));
					clauseObj.setSecondArgType(VARIABLETYPE_PROG_LINE);
				}
			}
			else {
				return false;
			}

		}
		else {
			vector<string> variable = split(wordsArr.at(i), SYMBOL_FULLSTOP);

			if (variable.size() != 2) {
				return false;
			}

			if (isVariableNameExists(variable.at(0))) {
				string varType = getVariableType(variable.at(0));

				if (relationshipTable.isArgsValid(relationshipType, i + 1, varType)) {
					if (varType.compare(VARIABLETYPE_CONSTANT) == 0) {
						if (variable.at(1).compare(VARIABLETYPE_VALUE) == 0) {
							if (i == 0) {
								clauseObj.setFirstArg(variable.at(0));
								clauseObj.setFirstArgType(varType);
							}
							else {
								clauseObj.setSecondArg(variable.at(0));
								clauseObj.setSecondArgType(varType);
							}
						}
						else {
							return false;
						}

					}
					else {
						if (variable.at(1).compare(VARIABLETYPE_STMT) == 0) {
							if (i == 0) {
								clauseObj.setFirstArg(variable.at(0));
								if (varType.compare(VARIABLETYPE_CALL) == 0) {
									clauseObj.setFirstArgType(toLower(VARIABLETYPE_CALLSTMT));
								}
								else {
									clauseObj.setFirstArgType(varType);
								}
							}
							else {
								clauseObj.setSecondArg(variable.at(0));
								if (varType.compare(VARIABLETYPE_CALL) == 0) {
									clauseObj.setSecondArgType(toLower(VARIABLETYPE_CALLSTMT));
								}
								else {
									clauseObj.setSecondArgType(varType);
								}
							}
						}
						else {
							return false;
						}
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}

	if (query.size() == 2) {
		subquery = query.at(1);
	}
	else {
		subquery = EMPTY_QUERY;
	}

	return true;
}

/*
 * Checks if the "with" clause is a string
 * If it is a string and is VALID, store the value as string and return true
 * If it is a string but is INVALID, return false and move onto next query
 */
bool QueryValidator::findWithClauseString(string &subquery, string &relationshipType, vector<string> &variableArr, vector<string> &variableType)
{
	// Splits by "="
	// So if the clause is c.procName = "HELLO", wordsArr.at(0) will be "c.procName" and wordsArr.at(1) will be "HELLO"
	vector<string> arrWords = split(subquery, SYMBOL_EQUALS, 2);
	relationshipType = RELATIONSHIP_TYPE_WITH_STRING;

	if (!relationshipTable.isNumOfArgsEqual(relationshipType, arrWords.size())) {
		return false;
	}

	vector<string> query = split(arrWords.at(1), SYMBOL_SPACE, 2);
	arrWords.at(1) = query.at(0);

	for (int i = 0; i < arrWords.size(); i++) {
		// Check if relationship is in the table and that argument is valid
		// If VALID, store the relationship type to the respective object
		if (isString(arrWords.at(i))) {
			if (relationshipTable.isArgsValid(relationshipType, i + 1, VARIABLETYPE_STRING)) {
				if (i == 0) {
					clauseObj.setFirstArg(getStringContents(arrWords.at(i)));
					clauseObj.setFirstArgType(VARIABLETYPE_STRING);
				}
				else {
					clauseObj.setSecondArg(getStringContents(arrWords.at(i)));
					clauseObj.setSecondArgType(VARIABLETYPE_STRING);
				}
			}
			else {
				return false;
			}

		}
		else {
			vector<string> variable = split(arrWords.at(i), SYMBOL_FULLSTOP);

			if (variable.size() != 2) {
				return false;
			}

			if (isVariableNameExists(variable.at(0))) {
				string varType = getVariableType(variable.at(0));

				if (relationshipTable.isArgsValid(relationshipType, i + 1, varType)) {
					if (varType.compare(VARIABLETYPE_VARIABLE) == 0) {
						if (variable.at(1).compare(VARIABLETYPE_VARNAME) == 0) {
							if (i == 0) {
								clauseObj.setFirstArg(variable.at(0));
								clauseObj.setFirstArgType(varType);
							}
							else {
								clauseObj.setSecondArg(variable.at(0));
								clauseObj.setSecondArgType(varType);
							}
						}
						else {
							return false;
						}

					}
					else {
						if (variable.at(1).compare(VARIABLETYPE_PROCNAME) == 0) {							
							if (i == 0) {
								clauseObj.setFirstArg(variable.at(0));
								if (varType.compare(VARIABLETYPE_CALL) == 0) {
									clauseObj.setFirstArgType(toLower(VARIABLETYPE_CALLPROCNAME));
								}
								else {
									clauseObj.setFirstArgType(varType);
								}
							}
							else {
								clauseObj.setSecondArg(variable.at(0));
								if (varType.compare(VARIABLETYPE_CALL) == 0) {
									clauseObj.setSecondArgType(toLower(VARIABLETYPE_CALLPROCNAME));
								}
								else {
									clauseObj.setSecondArgType(varType);
								}
							}
						}
						else {
							return false;
						}
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}

	if (query.size() == 2) {
		subquery = query.at(1);
	}
	else {
		subquery = EMPTY_QUERY;
	}

	return true;
}

/*
 *	Removes un-necessary whitespaces in query
 */
string QueryValidator::trim(string queryTrim) {

	// Remove leading and trailing whitespaces
	queryTrim.erase(queryTrim.begin(), find_if(queryTrim.begin(), queryTrim.end(), bind1st(not_equal_to<char>(), ' ')));
	queryTrim.erase(find_if(queryTrim.rbegin(), queryTrim.rend(), bind1st(not_equal_to<char>(), ' ')).base(), queryTrim.end());

	// Remove multiple whitespaces
	queryTrim = regex_replace(queryTrim, regex("[' ']{2,}"), " ");

	return queryTrim;
}

/*
 *	Checks if variable name is declared
 */
bool QueryValidator::isVariableNameExists(string variableName) {

	unordered_map<string, string>::iterator itMap = map.find(variableName);

	// Variable does not exist
	if (itMap == map.end()) {
		return false;
	}

	return true;
}

/*
 * Gets the variable type mapped to the variable declared
 */
string QueryValidator::getVariableType(string variableName)
{
	return map.find(variableName)->second;
}

/*
 * Checks if the argument is a string
 * (i.e. Starts with " and ends with ")
 */
bool QueryValidator::isString(string variableStr)
{
	// Check if string has " in front and " at the back
	if (!(variableStr.front() == SYMBOL_QUOTE && variableStr.back() == SYMBOL_QUOTE)) {
		return false;
	}
	return true;
}

/*
 * To get the contents of a string
 */
string QueryValidator::getStringContents(string word)
{
	return word.substr(1, word.size() - 2);
}

/*
 * Checks if argument is an integer
 * If it is an integer, make sure integer is more than 0
 * Returns true if integer > 0, otherwise return false
 */
bool QueryValidator::isInteger(string content) {

	if (content.empty()) {
		return false;
	}
	
	int size = strlen(content.c_str());

	// Make sure that contents of the string is an integer
	for (int i = 0; i < size; i++) {
		if (!isdigit(content.at(i))) {
			return false;
		}
	}

	// If it is an integer, convert string to long integer of base 10
	// Returns a long int value if successful, otherwise returns 0
	char *ptr;
	int contentInteger = strtol(content.c_str(), &ptr, 10);

	// Integer must be at least 1
	if (contentInteger >= 1) {
		return true;
	}

	return false;
}

/*
 * Counts the number of "(" in the argument
 */
int QueryValidator::numOfLeftBrackets(string stmt)
{
	int numCountLeft = count(stmt.begin(), stmt.end(), SYMBOL_OPEN_BRACKET);
	return numCountLeft;
}

/*
 * Counts the number of ")" in the argument
 */
int QueryValidator::numOfRightBrackets(string stmt)
{
	int numCountRight = count(stmt.begin(), stmt.end(), SYMBOL_CLOSE_BRACKET);
	return numCountRight;
}

/*
 * Tokenizer to split the queries given
 */
vector<string> QueryValidator::split(string str, char c) {

	vector<string> splitResult;
	const char *strChar = str.c_str();

	do {
		const char *begin = strChar;

		while (*strChar != c && *strChar) {
			strChar++;
		}

		splitResult.push_back(trim(string(begin, strChar)));
	} while (0 != *strChar++);

	return splitResult;
}

/*
 * Tokenizer to split the queries given into n number of parts, where you can choose the num
 */
vector<string> QueryValidator::split(string str, char c, int num) {
	vector<string> splitResult;
	const char *strChar = str.c_str();
	int i = 1;

	do {
		const char *begin = strChar;

		while (*strChar != c && *strChar) {
			strChar++;
		}

		splitResult.push_back(trim(string(begin, strChar)));
	} while (0 != *strChar++ && ++i < num);

	if (i == num) {
		const char *begin = strChar;

		while (0 != *strChar++  && *strChar) {
			strChar++;
		}

		splitResult.push_back(trim(string(begin, strChar)));
	}

	return splitResult;
}

/*
 * To make queries lower case to allow for non-case sensitivity
 */
string QueryValidator::toLower(string str) {
	transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

/*
 * To clear stored data in the Objects so that future queries will not be affected
 */
void QueryValidator::clearDeclarationObject(void)
{
	declarationObj.setVarName("");
	declarationObj.setVarType("");
}

void QueryValidator::clearSelectObject(void)
{
	selectObj.setVarName("");
	selectObj.setVarType("");
}

void QueryValidator::clearClauseObject(void)
{
	clauseObj.setClauseType("");
	clauseObj.setFirstArg("");
	clauseObj.setSecondArg("");
	clauseObj.setMainArg("");
	clauseObj.setFirstArgType("");
	clauseObj.setSecondArgType("");
	clauseObj.setMainArgType("");
}