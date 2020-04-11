#include "WithStringEvaluator.h"

WithStringEvaluator::WithStringEvaluator() {

}

WithStringEvaluator::~WithStringEvaluator() {

}

/*
Input: arg and its type in one side
Output: answers for this side
*/
vector<string> WithStringEvaluator::evaluateOneSide(string arg, string argType) {
	vector<string> result;
	if (argType == "procedure") {
		for (int i = 1; i <= PKB::getPKBInstance()->getProcTableSize(); i++) {
			result.push_back(PKB::getPKBInstance()->getProcName(i));
		}
	}
	else if (argType == "variable") {
		for (int i = 1; i <= PKB::getPKBInstance()->getVarTableSize(); i++) {
			result.push_back(PKB::getPKBInstance()->getVarName(i));
		}
	}
	else if (argType == "callprocname") {
		unordered_map<int,int> callsProc = PKB::getPKBInstance()->getStmtCallsMap();
		for (auto it = callsProc.begin(); it != callsProc.end(); it++) {
			string current = PKB::getPKBInstance()->getProcName(it->second);
			if (find(result.begin(), result.end(), current) == result.end()) {
				result.push_back(current);
			}
		}
	}
	return result;
}

/*
Input: with string clause
TODO: generate with string result
*/
void WithStringEvaluator::evaluateWithString(Clause clause) {
	string arg1 = clause.getFirstArg();
	string arg1Type = clause.getFirstArgType();
	string arg2 = clause.getSecondArg();
	string arg2Type = clause.getSecondArgType();
	arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
	arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), ' '), arg2.end());
	arg2.erase(remove(arg2.begin(), arg2.end(), '\t'), arg2.end());
	pair<int, int> result;
	if (arg1Type == "string" && arg2Type == "string") {
		if (arg1 == arg2) {
			result = { 0,0 };
			withStringResult.push_back(result);
		}
	} 
	else if (arg2Type == "string") {// a.name = "string"
		vector<string> arg1Result = evaluateOneSide(arg1, arg1Type);
		if (find(arg1Result.begin(), arg1Result.end(), arg2) != arg1Result.end()) {
			if (arg1Type == "variable") {
				int varID = PKB::getPKBInstance()->getVarID(arg2);
				result = { varID,varID };
				withStringResult.push_back(result);
			}
			else if (arg1Type == "callprocname") {
				int procID = PKB::getPKBInstance()->getProcID(arg2);
				list<int> callStmts = PKB::getPKBInstance()->getStmtCallsProc(procID);
				while (!callStmts.empty()) {
					result = { callStmts.front(),callStmts.front() };
					withStringResult.push_back(result);
					callStmts.pop_front();
				}
			}
			else {
				int ProcID = PKB::getPKBInstance()->getProcID(arg2);
				result = { ProcID,ProcID };
				withStringResult.push_back(result);
			}
		}
	}
	else if (arg1Type == "string") {// "a" = v.VarName
		vector<string> arg2Result = evaluateOneSide(arg2, arg2Type);
		if (find(arg2Result.begin(), arg2Result.end(), arg1) != arg2Result.end()) {
			if (arg2Type == "variable") {
				int varID = PKB::getPKBInstance()->getVarID(arg1);
				result = { varID,varID };
				withStringResult.push_back(result);
			}
			else if (arg2Type == "callprocname") {
				list<int> callStmts = PKB::getPKBInstance()->getStmtCallsProc(PKB::getPKBInstance()->getProcID(arg1));
				while (!callStmts.empty()) {
					result = { callStmts.front(),callStmts.front() };
					withStringResult.push_back(result);
					callStmts.pop_front();
				}
			}
			else {
				int ProcID = PKB::getPKBInstance()->getProcID(arg1);
				result = { ProcID,ProcID };
				withStringResult.push_back(result);
			}
		}
	}
	else {
		vector<string> arg1Result = evaluateOneSide(arg1, arg1Type);
		vector<string> arg2Result = evaluateOneSide(arg2, arg2Type);
		if (arg1 == arg2 && arg1Type == arg2Type) {
			for (int i = 0; i < arg1Result.size(); i++) {
				list<int> current;
				if (arg1Type == "variable") {
					current.push_back(PKB::getPKBInstance()->getVarID(arg1Result.at(i)));
				}
				else if (arg1Type == "callprocname") {
					current = PKB::getPKBInstance()->getStmtCallsProc(PKB::getPKBInstance()->getProcID(arg1Result.at(i)));
				}
				else {
					current.push_back(PKB::getPKBInstance()->getProcID(arg1Result.at(i)));
				}
				// fill in result table
				while (!current.empty()) {
					result = { current.front(),current.front() };
					withStringResult.push_back(result);
					current.pop_front();
				}
			}
		}
		else {// c.procName = v.Varname 
			for (int i = 0; i < arg1Result.size(); i++) {
				string current = arg1Result.at(i);
				if (find(arg2Result.begin(), arg2Result.end(), current) != arg2Result.end()) {
					list<int> arg1ID;
					list<int> arg2ID;
					// get Arg1 result
					if (arg1Type == "variable") {
						arg1ID.push_front(PKB::getPKBInstance()->getVarID(current));
					}
					else if (arg1Type == "callprocname") {
						arg1ID = PKB::getPKBInstance()->getStmtCallsProc(PKB::getPKBInstance()->getProcID(current));
					}
					else {
						arg1ID.push_front(PKB::getPKBInstance()->getProcID(current));
					}
					// get Arg2 result
					if (arg2Type == "variable") {
						arg2ID.push_front(PKB::getPKBInstance()->getVarID(current));
					}
					else if (arg2Type == "callprocname") {
						arg2ID = PKB::getPKBInstance()->getStmtCallsProc(PKB::getPKBInstance()->getProcID(current));
					}
					else {
						arg2ID.push_back(PKB::getPKBInstance()->getProcID(current));
					}
					// fill in result table
					while (!arg1ID.empty()) {
						int currentArg1 = arg1ID.front();
						list<int> temp = arg2ID;
						while (!temp.empty()) {
							result = { currentArg1, temp.front() };
							withStringResult.push_back(result);
							temp.pop_front();
						}
						arg1ID.pop_front();
					}
				}
			}
		}
	}
}

/*
TODO: return the with string result
*/
vector<pair<int, int>> WithStringEvaluator::getWithStringResult() {
	return withStringResult;
}
