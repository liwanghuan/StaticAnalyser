#pragma once

#include "DesignExtractor.h"

using namespace std;

void DesignExtractor::setCallsMap() {

	unordered_map<int, list<string>> callsProcMap = PKB::getPKBInstance()->getCallsProcMap();

	for (unordered_map<int, list<string>>::iterator it = callsProcMap.begin(); it != callsProcMap.end(); ++it) {
		int procID1 = (*it).first;
		list<string> procNameList = (*it).second;
		for (list<string>::iterator it2 = procNameList.begin(); it2 != procNameList.end(); ++it2) {
			int procID2 = PKB::getPKBInstance()->getProcID(*it2);
			if (procID2 == -1) {
				cerr << "error! Procecedure called does not exist!" << *it2 << endl;
				exit(-1);
			}
			PKB::getPKBInstance()->setCalls(procID1, procID2);
		}
	}
	PKB::getPKBInstance()->sortCallsMap();
}

void DesignExtractor::setStmtCallsMap() {
	list<pair<STMTNO, PROCNAME>> callsStmtList = PKB::getPKBInstance()->getCallsStmtList();
	for (list<pair<STMTNO, PROCNAME >>::iterator it = callsStmtList.begin(); it != callsStmtList.end(); ++it) {
		int stmtNo = (*it).first;
		string procName = (*it).second;
		int procID = PKB::getPKBInstance()->getProcID(procName);
		if (procID == -1) {
			cerr << procName;
			cerr << "error! Procecedure called does not exist!" << procName << endl;
			exit(-1);
		}
		else {
			PKB::getPKBInstance()->setStmtCalls(stmtNo, procID);
		}
		PKB::getPKBInstance()->sortCallsMap();
	}
}
void DesignExtractor::setCallsStarMap() {
	int procTableSize = PKB::getPKBInstance()->getProcTableSize();
	vector<bool> isVisited;
	isVisited.resize(procTableSize + 1);
	for (int source = 1; source <= procTableSize; ++source) {
		fill(isVisited.begin(), isVisited.end(), false);
		setCallsStarMapDFS(source, isVisited, list<int>());
	}
	PKB::getPKBInstance()->sortCallsStarMap();
}

void DesignExtractor::setCallsStarMapDFS(int source, vector<bool>& isVisited, list<int> visitedNeighbour) {
	isVisited.at(source) = true;
	visitedNeighbour.push_back(source);//Add current procID to visitedNeighbourList
	list<int> neighbourList = PKB::getPKBInstance()->getCalls(source);
	for (list<int>::iterator it = neighbourList.begin(); it != neighbourList.end(); ++it) {
		int neighbour = *it;

		// Test for Cyclic calls
		list<int>::iterator itList = find(visitedNeighbour.begin(), visitedNeighbour.end(), neighbour);
		if (itList != visitedNeighbour.end()) {
			cerr << "error! Cyclic call detected!: " << PKB::getPKBInstance()->getProcName(source) << endl;
			exit(-1);
		}

		if (isVisited.at(neighbour) == false) {
			setCallsStarMapDFS(neighbour, isVisited, visitedNeighbour);
		}
		PKB::getPKBInstance()->setCallsStar(source, neighbour);
		list<int> callsList = PKB::getPKBInstance()->getCallsStar(neighbour);
		for (list<int>::iterator it2 = callsList.begin(); it2 != callsList.end(); ++it2) {
			int neighbourStar = *it2;
			PKB::getPKBInstance()->setCallsStar(source, neighbourStar);
		}
	}
}

void DesignExtractor::updateProcUsesMap() {
	unordered_map<int, list<int>> callsStarMap = PKB::getPKBInstance()->getCallsStarMap();
	for (unordered_map<int, list<int>>::iterator it = callsStarMap.begin(); it != callsStarMap.end(); ++it) {
		list<int> callsStarList = it->second;
		for (list<int>::iterator it2 = callsStarList.begin(); it2 != callsStarList.end(); ++it2) {
			string procName = PKB::getPKBInstance()->getProcName(*it2);
			list<int> varList = PKB::getPKBInstance()->getProcUsedBy(procName);
			varList.sort();
			varList.unique();
			for (list<int>::iterator it3 = varList.begin(); it3 != varList.end(); ++it3) {
				PKB::getPKBInstance()->setProcUses(it->first, *it3);
			}
		}
	}
}

void DesignExtractor::updateProcModifiesMap() {
	unordered_map<int, list<int>> callsStarMap = PKB::getPKBInstance()->getCallsStarMap();
	for (unordered_map<int, list<int>>::iterator it = callsStarMap.begin(); it != callsStarMap.end(); ++it) {
		list<int> callsStarList = it->second;
		for (list<int>::iterator it2 = callsStarList.begin(); it2 != callsStarList.end(); ++it2) {
			string procName = PKB::getPKBInstance()->getProcName(*it2);
			list<int> varList = PKB::getPKBInstance()->getProcModifiedBy(procName);
			varList.sort();
			varList.unique();
			for (list<int>::iterator it3 = varList.begin(); it3 != varList.end(); ++it3) {
				PKB::getPKBInstance()->setProcModifies(it->first, *it3);
			}
		}
	}
}

void DesignExtractor::updateStmtUsesMap() {
	list<pair<STMTNO, PROCNAME>> callsStmtList = PKB::getPKBInstance()->getCallsStmtList();
	for (list<pair<STMTNO, PROCNAME >>::iterator it = callsStmtList.begin(); it != callsStmtList.end(); ++it) {
		int stmtNo = (*it).first;
		string procName = (*it).second;
		int procID = PKB::getPKBInstance()->getProcID(procName);
		if (procID == -1) {
			cerr << procName;
			cerr << "error! Procecedure called does not exist!" << procName << endl;
			exit(-1);
		}
		list<int> parentStarList = PKB::getPKBInstance()->getParentStar(stmtNo);
		list<int> varList = PKB::getPKBInstance()->getProcUsedBy(procName);
		varList.sort();
		varList.unique();
		for (list<int>::iterator it2 = varList.begin(); it2 != varList.end(); ++it2) {
			int varID = *it2;
			PKB::getPKBInstance()->setStmtUses(stmtNo, varID);
			for (list<int>::iterator it3 = parentStarList.begin(); it3 != parentStarList.end(); ++it3) {
				int parentStarStmtNo = *it3;
				PKB::getPKBInstance()->setStmtUses(parentStarStmtNo, varID);
			}
		}
	}
}

void DesignExtractor::updateStmtModifiesMap() {
	list<pair<STMTNO, PROCNAME>> callsStmtList = PKB::getPKBInstance()->getCallsStmtList();
	for (list<pair<STMTNO, PROCNAME >>::iterator it = callsStmtList.begin(); it != callsStmtList.end(); ++it) {
		int stmtNo = (*it).first;
		string procName = (*it).second;
		int procID = PKB::getPKBInstance()->getProcID(procName);
		if (procID == -1) {
			cerr << "error! Procecedure called does not exist!" << procName << endl;
			exit(-1);
		}
		list<int> parentStarList = PKB::getPKBInstance()->getParentStar(stmtNo);
		list<int> varList = PKB::getPKBInstance()->getProcModifiedBy(procName);
		varList.sort();
		varList.unique();
		for (list<int>::iterator it2 = varList.begin(); it2 != varList.end(); ++it2) {
			int varID = *it2;
			PKB::getPKBInstance()->setStmtModifies(stmtNo, varID);
			for (list<int>::iterator it3 = parentStarList.begin(); it3 != parentStarList.end(); ++it3) {
				int parentStarStmtNo = *it3;
				PKB::getPKBInstance()->setStmtModifies(parentStarStmtNo, varID);
			}
		}
		PKB::getPKBInstance()->sortModifiesMap();
	}
}

void DesignExtractor::setFollowsStarMapReverse() {

	unordered_map<int, list<int>> followsStarMap = PKB::getPKBInstance()->getFollowsStarMap();

	PKB::getPKBInstance()->setFollowsStarMapReverse(reverseListMap(followsStarMap));
}

void DesignExtractor::setParentStarMapReverse() {

	unordered_map<int, list<int>> parentStarMap = PKB::getPKBInstance()->getParentStarMap();

	PKB::getPKBInstance()->setParentStarMapReverse(reverseListMap(parentStarMap));
}

//reverse function for map<int, int> tables (1-to-1)
unordered_map<int, int> DesignExtractor::reverseMap(unordered_map<int, int> nonReverseMap) {
	unordered_map<int, int> reverseMap;

	for (unordered_map<int, int>::iterator it = nonReverseMap.begin(); it != nonReverseMap.end(); ++it) {

		reverseMap[(*it).second] = (*it).first;
	}

	return reverseMap;
}

//reverse function for map<int, String> tables (1-to-1)
unordered_map<string, int> DesignExtractor::reverseStringTable(unordered_map<int, string> stringTable) {

	unordered_map<string, int> reverseStringTable;

	for (unordered_map<int, string>::iterator it = stringTable.begin(); it != stringTable.end(); ++it) {

		reverseStringTable[(*it).second] = (*it).first;
	}

	return reverseStringTable;
}

//reverse function for map<int, list<int>> tables (many-to-many)
unordered_map<int, list<int>> DesignExtractor::reverseListMap(unordered_map<int, list<int>> listMap) {

	unordered_map<int, list<int>> reverseListMap;

	for (unordered_map<int, list<int>>::iterator it = listMap.begin(); it != listMap.end(); ++it) {

		for (list<int>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2) {

			if (reverseListMap.find(*it2) == reverseListMap.end()) {

				list<int> temp;
				temp.push_back((*it).first);
				reverseListMap[*it2] = temp;
			}

			else {

				list<int> temp = reverseListMap.at(*it2);
				temp.push_back((*it).first);
				reverseListMap[*it2] = temp;
			}
		}
	}

	return reverseListMap;
}

void DesignExtractor::setFollowsStarMap() {

	unordered_map<int, int> followsMap = PKB::getPKBInstance()->getFollowsMap();

	list<int> starList; //list of stmtNo. to be inserted to the respective Star table row
	vector<bool> hasVisited; //ensure no duplication of stmtNo.
	queue<int> toVisit; //to be visited as key in the table

	for (unordered_map<int, int>::iterator it = followsMap.begin(); it != followsMap.end(); ++it) {
		int itKey = (*it).first;
		int temp = (*it).second;
		hasVisited.clear();
		hasVisited.resize(10000, false);
		if (itKey != 0 && temp != 0) {
			toVisit.push(temp);
			hasVisited[temp] = true;
		}
		while (!toVisit.empty())
		{
			int tempIndex = toVisit.front();
			toVisit.pop();
			temp = followsMap[tempIndex];
			starList.push_back(tempIndex);
			if (!hasVisited[temp] && temp != 0) {
				toVisit.push(temp);
				hasVisited[temp] = true;
			}
		}
		if (starList.size() != 0) {
			starList.sort();
			PKB::getPKBInstance()->setFollowsStar(itKey, starList);
		}
		starList.clear();
	}
}

void DesignExtractor::setParentStarMap() {

	unordered_map<int, list<int>> parentMap = PKB::getPKBInstance()->getParentMap();

	list<int> starList; //list of stmtNo. to be inserted to the respective Star table row
	vector<bool> hasVisited; //ensure no duplication of stmtNo.
	queue<int> toVisit; //to be visited as key in the table

	for (unordered_map<int, list<int>>::iterator it = parentMap.begin(); it != parentMap.end(); ++it) {
		int itKey = (*it).first;
		list<int> temp = (*it).second;
		hasVisited.clear();
		hasVisited.resize(10000, false);
		for (auto& x : temp)
		{
			if (itKey != 0 && x != 0) {
				toVisit.push(x);
				hasVisited[x] = true;
			}
		}
		while (!toVisit.empty())
		{
			int tempIndex = toVisit.front();
			toVisit.pop();
			temp = parentMap[tempIndex];
			starList.push_back(tempIndex);
			for (auto& x : temp)
			{
				if (!hasVisited[x] && x != 0) {
					toVisit.push(x);
					hasVisited[x] = true;
				}
			}
		}
		if (starList.size() != 0) {
			starList.sort();
			PKB::getPKBInstance()->setParentStar(itKey, starList);
		}
		starList.clear();
	}
}

void DesignExtractor::sortUsesModifiesMap() {
	PKB::getPKBInstance()->sortUsesModifiesMap();
}

void DesignExtractor::buildCFG() {
	PKB::getPKBInstance()->buildCFG();
}
