#include "PKB.h"
using namespace std;

bool PKB::PKBInstanceFlag = false;
PKB* PKB::PKBInstance = NULL;

PKB* PKB::getPKBInstance() {
	if (!PKBInstanceFlag) {
		PKBInstance = new PKB();
		PKBInstanceFlag = true;
		return PKBInstance;
	}
	return PKBInstance;
}

void PKB::removePKBInstance() {
	delete PKBInstance;
	PKBInstance = false;
}


void PKB::updateSourceList(int statementNum, int statementLevel, int numOfCloseBraces, string statementType, string statementData) {
	int progLineNum = statementNum;
	Statement statement = Statement(progLineNum, statementLevel, numOfCloseBraces, statementType, statementData);
	sourceList.push_back(statement);
	sourceListIndex[progLineNum] = sourceList.size() - 1;
	//private map ( 1 to 1 mapping )
	if ((statementType != "procedure") && statementType != "else") {
		stmtTypeMap[statementNum] = statementType;
	}
	//assign if while call procedure 
}

vector<Statement> PKB::getSourceList() {
	return sourceList;
}

list<STMTNO> PKB::getStmtLst() {
	return stmtLst;
}

unordered_map<int, int> PKB::getSourceListIndex() {
	return sourceListIndex;
}

int PKB::getTotalNumOfProgLine() {
	return getAssignPatternMapSize() + getIfPatternMapSize() + getWhilePatternMapSize() + getStmtCallsMapSize();
}


//Calls

void PKB::setCalls(PROCID p1, PROCID p2) {
	getCalls().setCalls(p1, p2);
}

void PKB::sortCallsMap() {
	return getCalls().sortCallsMap();
}

list<PROCID> PKB::getCalls(PROCID p1) {
	return getCalls().getCalls(p1);
}

list<PROCID> PKB::getCalledBy(PROCID p2) {
	 return getCalls().getCalledBy(p2);
}

list<PROCID> PKB::getCalls(PROCNAME p1) {
	int id1 = getProcTable().getProcID(p1);
	return getCalls().getCalls(id1);
}

list<PROCID> PKB::getCalledBy(PROCNAME p2) {
	int id2 = getProcTable().getProcID(p2);
	return getCalls().getCalledBy(id2);
}

bool PKB::isCallsValid(PROCID p1, PROCID p2) {
	return getCalls().isCallsValid(p1, p2);
}

bool PKB::isCallsValid(PROCNAME p1, PROCNAME p2) {
	int id1 = getProcTable().getProcID(p1);
	int id2 = getProcTable().getProcID(p2);
	return getCalls().isCallsValid(id1, id2);
}

unordered_map<int, list<int>> PKB::getCallsMap() {
	return getCalls().getCallsMap();
}

unordered_map<int, list<int>> PKB::getCallsMapReverse() {
	return getCalls().getCallsMapReverse();
}

int PKB::getCallsMapSize() {
	return getCalls().getCallsMapSize();
}

int PKB::getCallsMapReverseSize() {
	return getCalls().getCallsMapReverseSize();
}

int PKB::getStmtCallsMapSize() {
	return getCalls().getStmtCallsMapSize();
}

unordered_map<STMTNO, PROCID> PKB::getStmtCallsMap() {
	return getCalls().getStmtCallsMap();
}

unordered_map<PROCID, list<STMTNO>> PKB::getStmtCallsMapReverse() {
	return getCalls().getStmtCallsMapReverse();
}

int PKB::getProcCalledByStmt(STMTNO s1) {
	return getCalls().getProcCalledByStmt(s1);
}

list<int> PKB::getStmtCallsProc(PROCID p1) {
	return getCalls().getStmtCallsProc(p1);
}

bool PKB::isStmtCallsValid(STMTNO s1, PROCID p1) {
	return getCalls().isStmtCallsValid(s1, p1);
}

void PKB::setStmtCalls(STMTNO s1, PROCID p1) {
	getCalls().setStmtCalls(s1, p1);
}

//Calls Star

void PKB::setCallsStar(PROCID p1, PROCID p2) {
	getCallsStar().setCallsStar(p1, p2);
}

void PKB::sortCallsStarMap() {
	return getCallsStar().sortCallsStarMap();
}

list<PROCID> PKB::getCallsStar(PROCID p1) {
	return getCallsStar().getCallsStar(p1);
}

list<PROCID> PKB::getCalledStarBy(PROCID p2) {
	return getCallsStar().getCalledStarBy(p2);
}

list<PROCID> PKB::getCallsStar(PROCNAME p1) {
	int id1 = getProcTable().getProcID(p1);
	return getCallsStar().getCallsStar(id1);
}

list<PROCID> PKB::getCalledStarBy(PROCNAME p2) {
	int id2 = getProcTable().getProcID(p2);
	return getCallsStar().getCalledStarBy(id2);
}

bool PKB::isCallsStarValid(PROCID p1, PROCID p2) {
	return getCallsStar().isCallsStarValid(p1, p2);
}

bool PKB::isCallsStarValid(PROCNAME p1, PROCNAME p2) {
	int id1 = getProcTable().getProcID(p1);
	int id2 = getProcTable().getProcID(p2);
	return getCallsStar().isCallsStarValid(id1, id2);
}

unordered_map<int, list<int>> PKB::getCallsStarMap() {
	return getCallsStar().getCallsStarMap();
}

unordered_map<int, list<int>> PKB::getCallsStarMapReverse() {
	return getCallsStar().getCallsStarMapReverse();
}

int PKB::getCallsStarMapSize() {
	return getCallsStar().getCallsStarMapSize();
}

int PKB::getCallsStarMapReverseSize() {
	return getCallsStar().getCallsStarMapReverseSize();
}

//Follows
unordered_map<int, int> PKB::getFollowsMap() {
	return getFollows().getFollowsMap();
}

unordered_map<int, int> PKB::getFollowsMapReverse() {
	return getFollows().getFollowsMapReverse();
}

void PKB::setFollows(STMTNO s1, STMTNO s2) {
	getFollows().setFollows(s1, s2);
}

int PKB::getFollows(STMTNO s2) {
	return getFollows().getFollows(s2);
}

int PKB::getFollowedBy(STMTNO s1) {
	return getFollows().getFollowedBy(s1);
}

bool PKB::isFollowsValid(STMTNO s1, STMTNO s2) {
	return getFollows().isFollowsValid(s1, s2);
}

int PKB::getFollowsMapSize() {
	return getFollows().getFollowsMapSize();
}

int PKB::getFollowsMapReverseSize() {
	return getFollows().getFollowsMapReverseSize();
}

//End of Follows

//FollowsStar
unordered_map<int, list<int>> PKB::getFollowsStarMap() {
	return getFollowsStar().getFollowsStarMap();
}

unordered_map<int, list<int>> PKB::getFollowsStarMapReverse() {
	return getFollowsStar().getFollowsStarMapReverse();
}


void PKB::setFollowsStar(int s1, list<int> s2List) {
	getFollowsStar().setFollowsStar(s1, s2List);
}

void PKB::setFollowsStarMapReverse(unordered_map<int, list<int>> unordered_map) {
	getFollowsStar().setFollowsStarMapReverse(unordered_map);
}

list<STMTNO> PKB::getFollowsStar(STMTNO s2) {
	return getFollowsStar().getFollowsStar(s2);
}

list<STMTNO> PKB::getFollowsStarBy(STMTNO s1) {
	return getFollowsStar().getFollowsStarBy(s1);
}

bool PKB::isFollowsStarValid(STMTNO s1, STMTNO s2) {
	return getFollowsStar().isFollowsStarValid(s1, s2);
}

int PKB::getFollowsStarMapSize() {
	return getFollowsStar().getFollowsStarMapSize();
}

int PKB::getFollowsStarMapReverseSize() {
	return getFollowsStar().getFollowsStarMapReverseSize();
}
//End of FollowsStar

//Parent
void PKB::setParent(STMTNO s1, STMTNO s2) {
	getParent().setParent(s1, s2);
}

STMTNO PKB::getParent(STMTNO s2) {
	return getParent().getParent(s2);
}

list<STMTNO> PKB::getAllChildren(STMTNO s1) {
	return getParent().getAllChildren(s1);
}

bool PKB::isParentValid(STMTNO s1, STMTNO s2) {
	return getParent().isParentValid(s1, s2);
}

int PKB::getParentMapSize() {
	return getParent().getParentMapSize();
}

int PKB::getParentMapReverseSize() {
	return getParent().getParentMapReverseSize();
}
//End of Parent


unordered_map<int, list<int>> PKB::getParentMap() {
	return getParent().getParentMap();
}

unordered_map<int, int> PKB::getParentMapReverse() {
	return getParent().getParentMapReverse();
}

//ParentStar
unordered_map<int, list<int>> PKB::getParentStarMap() {
	return getParentStar().getParentStarMap();
}

unordered_map<int, list<int>> PKB::getParentStarMapReverse() {
	return getParentStar().getParentStarMapReverse();
}

void PKB::setParentStar(int parent, list<int> childList) {
	getParentStar().setParentStar(parent, childList);
}

void PKB::setParentStarMapReverse(unordered_map<int, list<int>> unordered_map) {
	getParentStar().setParentStarMapReverse(unordered_map);
}

list<STMTNO> PKB::getAllChildrenStar(STMTNO s1) {
	return getParentStar().getAllChildrenStar(s1);
}

list<STMTNO> PKB::getParentStar(STMTNO s2) {
	return getParentStar().getParentStar(s2);
}

bool PKB::isParentStarValid(STMTNO s1, STMTNO s2) {
	return getParentStar().isParentStarValid(s1, s2);
}

int PKB::getParentStarMapSize() {
	return getParentStar().getParentStarMapSize();
}

int PKB::getParentStarMapReverseSize() {
	return getParentStar().getParentStarMapReverseSize();
}
//End of ParentStar

//Next
void PKB::buildCFG() {
	getCFG().buildCFG(getSourceList());
}
int PKB::getProcFirstStmt(int ProcNo) {
	return getCFG().getProcFirstStmt(ProcNo);
}
list<STMTNO> PKB::getNext(STMTNO value) {
	return getCFG().getNext(value);
}

list<STMTNO> PKB::getPrevious(STMTNO key) {
	return getCFG().getPrevious(key);
}

bool PKB::isNextValid(STMTNO key, STMTNO value) {
	return getCFG().isNextValid(key, value);
}

//NextStar
list<STMTNO> PKB::getNextStar(STMTNO value) {
	return getCFG().getNextStar(value);
}

list<STMTNO> PKB::getPreviousStar(STMTNO key) {
	return getCFG().getPreviousStar(key);
}

bool PKB::isNextStarValid(STMTNO key, STMTNO value) {
	return getCFG().isNextStarValid(key, value);
}

// Next and Next* end

//VarTable
int PKB::getVarTableSize() {
	return getVarTable().getVarTableSize();
}

VARID PKB::insertVar(VARNAME varName) {
	return getVarTable().insertVar(varName);
}

VARID PKB::getVarID(VARNAME varName) {
	return getVarTable().getVarID(varName);
}

VARNAME PKB::getVarName(VARID index) {
	return getVarTable().getVarName(index);
}
//End of VarTable


//ProcTable
int PKB::getProcTableSize() {
	return getProcTable().getProcTableSize();
}

PROCID PKB::insertProc(PROCNAME procName) {
	return getProcTable().insertProc(procName);
}

PROCID PKB::getProcID(PROCNAME procName) {
	return getProcTable().getProcID(procName);
}

PROCNAME PKB::getProcName(PROCID index) {
	return getProcTable().getProcName(index);
}
//End of ProcTable

//Uses

unordered_map<int, list<int>> PKB::getProcUsesMap() {
	return getUses().getProcUsesMap();
}

unordered_map<int, list<int>> PKB::getProcUsesMapReverse() {
	return getUses().getProcUsesMapReverse();
}

unordered_map<int, list<int>> PKB::getStmtUsesMap() {
	return getUses().getStmtUsesMap();
}

unordered_map<int, list<int>> PKB::getStmtUsesMapReverse() {
	return getUses().getStmtUsesMapReverse();
}

void PKB::setUses(PROCID procID, STMTNO stmtNo, VARID varID) {
	getUses().setUses(procID, stmtNo, varID);
}

void PKB::setStmtUses(STMTNO stmtNo, VARID varID) {
	getUses().setStmtUses(stmtNo, varID);
}

void PKB::setProcUses(PROCID procID, VARID varID) {
	getUses().setProcUses(procID, varID);
}

void PKB::sortUsesMap() {
	getUses().sortUsesMap();
}

list<STMTNO> PKB::getUses(VARNAME variable) {
	int varID = getVarTable().getVarID(variable);
	return  getUses().getUses(varID);

}

list<VARID> PKB::getUsedBy(STMTNO stmtNo) {
	return	getUses().getUsedBy(stmtNo);
}

bool PKB::isUsesValid(STMTNO stmtNumber, VARNAME variable) {
	int varID = getVarTable().getVarID(variable);
	return  getUses().isUsesValid(stmtNumber, varID);

}

list<PROCID> PKB::getProcUses(VARNAME variable) {
	int varID = getVarTable().getVarID(variable);
	return  getUses().getProcUses(varID);

}

list<VARID> PKB::getProcUsedBy(PROCNAME procName) {
	int procID = getProcTable().getProcID(procName);
	return  getUses().getProcUsedBy(procID);
}

bool PKB::isProcUsesValid(PROCNAME procName, VARNAME variable) {
	int procID = getProcTable().getProcID(procName);
	int varID = getVarTable().getVarID(variable);
	return  getUses().isProcUsesValid(procID, varID);

}

int PKB::getStmtUsesMapSize() {
	return getUses().getStmtUsesMapSize();
}

int PKB::getStmtUsesMapReverseSize() {
	return getUses().getStmtUsesMapReverseSize();
}

int PKB::getProcUsesMapSize() {
	return getUses().getProcUsesMapSize();
}

int PKB::getProcUsesMapReverseSize() {
	return getUses().getProcUsesMapReverseSize();
}
//End of uses


//Modifies
unordered_map<int, list<int>> PKB::getProcModifiesMap() {
	return getModifies().getProcModifiesMap();
}

unordered_map<int, list<int>> PKB::getProcModifiesMapReverse() {
	return getModifies().getProcModifiesMapReverse();
}

unordered_map<int, list<int>> PKB::getStmtModifiesMap() {
	return getModifies().getStmtModifiesMap();
}

unordered_map<int, list<int>> PKB::getStmtModifiesMapReverse() {
	return getModifies().getStmtModifiesMapReverse();
}

void PKB::setModifies(PROCID procID, STMTNO stmtNo, VARID varID) {
	getModifies().setModifies(procID, stmtNo, varID);
}

void PKB::setStmtModifies(STMTNO stmtNo, VARID varID) {
	getModifies().setStmtModifies(stmtNo, varID);
}

void PKB::setProcModifies(PROCID procID, VARID varID) {
	getModifies().setProcModifies(procID, varID);
}

void PKB::sortModifiesMap() {
	getModifies().sortModifiesMap();
}

list<STMTNO> PKB::getModifies(VARNAME variable) {
	int varID = getVarTable().getVarID(variable);
	return  getModifies().getModifies(varID);
}

list<VARID> PKB::getModifiedBy(STMTNO stmtNo) {
	return	getModifies().getModifiedBy(stmtNo);
}

bool PKB::isModifiesValid(STMTNO stmtNumber, VARNAME variable) {
	int varID = getVarTable().getVarID(variable);
	return  getModifies().isModifiesValid(stmtNumber, varID);

}

list<PROCID> PKB::getProcModifies(VARNAME variable) {
	int varID = getVarTable().getVarID(variable);
	return  getModifies().getProcModifies(varID);

}

list<VARID> PKB::getProcModifiedBy(PROCNAME procName) {
	int procID = getProcTable().getProcID(procName);
	return  getModifies().getProcModifiedBy(procID);
}

bool PKB::isProcModifiesValid(PROCNAME procName, VARNAME variable) {
	int procID = getProcTable().getProcID(procName);
	int varID = getVarTable().getVarID(variable);
	return  getModifies().isProcModifiesValid(procID, varID);

}

int PKB::getStmtModifiesMapSize() {
	return getModifies().getStmtModifiesMapSize();
}

int PKB::getStmtModifiesMapReverseSize() {
	return getModifies().getStmtModifiesMapReverseSize();
}

int PKB::getProcModifiesMapSize() {
	return getModifies().getProcModifiesMapSize();
}

int PKB::getProcModifiesMapReverseSize() {
	return getModifies().getProcModifiesMapReverseSize();
}
//End of Modifies

//Affects
list<int> PKB::getAffectedBy(int s1) {
    unordered_map<int, list<int>>::iterator itKey = affectedByS1Map.find(s1);
    
    if (itKey != affectedByS1Map.end()) {
        return itKey->second;
    }
    
    else {
        
        list<int> affectResult;
        //not assignment statement
        if (getStmtType(s1) != "assign")
            return affectResult;
        
        //else
        int varModifiesIndex = getModifies().getModifiedBy(s1).front();
        queue<int> path;
        vector<int> visit;
        visit.resize(getTotalNumOfProgLine() + 1, 0);
        visit[s1] = -1;
        path.push(s1);
        while (!path.empty()) {
            int temp = path.front();
            path.pop();
            if (visit[temp] == -1) {
                //initialization. first
                visit[temp] = 1;
                transfer(temp, path, true);
            }
            else {
                //check if visited
                if (visit[temp] == 1) {
                    //check whether being used
                    if (getStmtType(temp) == "assign") {
                        list<int> varUsesIndex = getUses().getUsedBy(temp);
                        if (contains(varUsesIndex, varModifiesIndex)) {
                            affectResult.push_back(temp);
                        }
                    }
                }
                
                else {
                    //visit[temp]=0
                    visit[temp] = 1;
                    //for non-assign statements
                    if ((getStmtType(temp) == "if") || (getStmtType(temp) == "while")) {
                        transfer(temp, path, true);
                    }
                    else
                    {
                        //check if uses var
                        if (getStmtType(temp) == "assign") {
                            list<int> varUsesIndex = getUses().getUsedBy(temp);
                            if (contains(varUsesIndex, varModifiesIndex)) {
                                affectResult.push_back(temp);
                            }
                        }
                        
                        list<int> tempModifes = getModifies().getModifiedBy(temp);
                        //calls statement. if call statement has modified then dead
                        if (!contains(tempModifes, varModifiesIndex)) {
                            transfer(temp, path, true);
                        }
                        else
                        {
                            //path is dead, terminate is being modified
                            ;
                        }
                    }
                }
            }
        }
        affectResult.sort();
        affectResult.unique();
        affectedByS1Map.insert(pair<int, list<int>>(s1, affectResult));
        return affectResult;
    }
}

list<int> PKB::getAffects(int s2) {
    /*
     To cache within query
     */
    unordered_map<int, list<int>>::iterator itKey = affectsS2Map.find(s2);
    
    if (itKey != affectsS2Map.end()) {
        return itKey->second;
    }
    
    else {
        list<int> affectResult;
        //if s2 is not an assignment statement, return;
        if (getStmtType(s2) != "assign")
            return affectResult;
        
        //else
        list<int> varUsesIndex = getUses().getUsedBy(s2);
        queue<int> path;
        vector<int> visit;
        
        for (auto& tempUses : varUsesIndex)
        {
            clearQueue(path);
            visit.resize(getTotalNumOfProgLine() + 1, 0);
            //reset to 0 for new var
            visit.assign(visit.size(), 0);
            visit[s2] = -1;
            path.push(s2);
            while (!path.empty())
            {
                int temp = path.front();
                path.pop();
                if (visit[temp] == -1)
                {
                    //initial statement
                    visit[temp] = 1;
                    transfer(temp, path, false);
                }
                else
                {
                    //end of statement (previous)
                    if (temp == -1) {
                        continue;
                    }
                    //check whether Modifies
                    if (getStmtType(temp) == "assign")
                    {
                        list<int> varModifiesIndex = getModifies().getModifiedBy(temp);
                        if (contains(varModifiesIndex, tempUses))
                        {
                            affectResult.push_back(temp);
                        }
                        else
                        {
                            transfer(temp, path, false);
                        }
                        visit[temp] = 1;
                    }
                    else if (getStmtType(temp) == "if" ||
                             getStmtType(temp) == "while")
                    {
                        if (visit[temp] != 1)
                        {
                            transfer(temp, path, false);
                            visit[temp] = 1;
                        }
                    }
                    else
                    {
                        //Call statement
                        if (visit[temp] != 1)
                        {
                            list<int> varModifiesIndex = getModifies().getModifiedBy(temp);
                            if (!contains(varModifiesIndex, tempUses))
                            {
                                transfer(temp, path, false);
                            }
                            visit[temp] = 1;
                        }
                    }
                }
            }
        }
        
        affectResult.sort();
        affectResult.unique();
        affectsS2Map.insert(pair<int, list<int>>(s2, affectResult));
        return affectResult;
    }
}

void PKB::processAffectsMap() {
    unordered_map<int, pair<string, string>> assignPatternMap = getPatternTable().getassignPatternMap();
    list<int> toDo;
    for (unordered_map<int, pair<string, string>>::iterator it = assignPatternMap.begin(); it != assignPatternMap.end(); ++it) {
        toDo.push_back(it->first);
    }
    
    //iterate through map, use the int as s1
    toDo.sort();
    for (std::list<int>::iterator it = toDo.begin(); it != toDo.end(); ++it) {
        int s1 = *it;
        list<int> affectResult;
        //not assignment statement
        if (getStmtType(s1) != "assign") {
            ;//nothing to return skip
        }
        //else
        int varModifiesIndex = getModifies().getModifiedBy(s1).front();
        queue<int> path;
        vector<int> visit;
        visit.resize(getTotalNumOfProgLine() + 1, 0);
        visit[s1] = -1;
        path.push(s1);
        while (!path.empty()) {
            int temp = path.front();
            path.pop();
            if (visit[temp] == -1) {
                //initialization. first
                visit[temp] = 1;
                transfer(temp, path, true);
            }
            else {
                //check if visited
                if (visit[temp] == 1) {
                    //check whether being used
                    if (getStmtType(temp) == "assign") {
                        list<int> varUsesIndex = getUses().getUsedBy(temp);
                        if (contains(varUsesIndex, varModifiesIndex)) {
                            affectResult.push_back(temp);
                            insertIntoS2Map(s1, temp);
                        }
                    }
                }
                
                else {
                    //visit[temp]=0
                    visit[temp] = 1;
                    //for non-assign statements
                    if ((getStmtType(temp) == "if") || (getStmtType(temp) == "while")) {
                        transfer(temp, path, true);
                    }
                    else
                    {
                        //check if uses var
                        if (getStmtType(temp) == "assign") {
                            list<int> varUsesIndex = getUses().getUsedBy(temp);
                            if (contains(varUsesIndex, varModifiesIndex)) {
                                affectResult.push_back(temp);
                                //insert into s2map
                                insertIntoS2Map(s1, temp);
                            }
                        }
                        
                        list<int> tempModifes = getModifies().getModifiedBy(temp);
                        //calls statement. if call statement has modified then dead
                        if (!contains(tempModifes, varModifiesIndex)) {
                            transfer(temp, path, true);
                            
                        }
                        else
                        {
                            //path is dead, terminate is being modified
                            ;
                        }
                    }
                }
            }
        }
        affectResult.sort();
        affectResult.unique();
        affectedByS1Map.insert(pair<int, list<int>>(s1, affectResult));
        //nothing to returnreturn affectResult;
    }
    
    //Sort and unique affectsS2Map (cleanup)
    for (auto itS2Map = affectsS2Map.begin(); itS2Map != affectsS2Map.end(); ++itS2Map) {
        itS2Map->second.sort();
        itS2Map->second.unique();
    }
    
}

void PKB::insertIntoS2Map(int s1, int s2) {
    auto it2 = affectsS2Map.find(s2);
    if (it2 != affectsS2Map.end()) {
        affectsS2Map[s2].push_back(s1);
    }
    else {
        affectsS2Map[s2] = list<int>();
        affectsS2Map[s2].push_back(s1);
    }
}

void PKB::clearCacheMaps(){
    //dont clear map
    affectedByS1Map = unordered_map<int, list<int>>();
    affectsS2Map = unordered_map<int, list<int>>();
    affectedByS1StarMap = unordered_map<int, list<int>>();
    affectsS2StarMap = unordered_map<int, list<int>>();
	getCFG().clearStarMap();
}


bool PKB::isAffectsValid(int s1, int s2) {
    //check cases, return false faster
    //Either 1 not assignment statements --> false
    if ((getStmtType(s1) != "assign") || (getStmtType(s2) != "assign")) {
        return false;
    }
    
    //Not same procedure --> false
    
    if (getCFG().getProcMap(s1) != getCFG().getProcMap(s2)) {
        return false;
    }
    
    
    int varModifiesIndex = getModifies().getModifiedBy(s1).front();
    list<int> varUsesIndex = getUses().getUsedBy(s2);
    //if s2 does not use variable modified in s1--> false
    if (!contains(varUsesIndex, varModifiesIndex)) {
        return false;
    }
    
    //main loop
    queue<int> path;
    vector<int> visit;
    visit.resize(getTotalNumOfProgLine() + 1, 0);
    visit[s1] = -1;
    path.push(s1);
    
    while (!path.empty()) {
        int temp = path.front();
        path.pop();
        
        //there is path and not itself (-1 init)
        if (temp == s2 && visit[temp] != -1) {
            return true;
        }
        
        else if (visit[temp] == 1) {
            //visited
        }
        
        else if (getStmtType(temp) == "while") {
            visit[temp] = 1;
            list<int> tempChildrenStarList = getParentStar().getAllChildrenStar(temp);
            tempChildrenStarList.sort();
            //s2 contain within children star (loop)
            if (s2 >= tempChildrenStarList.front() && s2 <= tempChildrenStarList.back()) {
                //go next stmt
                int whileNext = temp + 1;
                path.push(whileNext);
            }
            
            else {
                //not contained inside, skip the next into loop
                list<int> tempNextList = getCFG().getNext(temp);
                for (auto& tempNext : tempNextList) {
                    int whileNext = temp + 1;
                    if (tempNext != whileNext) {
                        path.push(tempNext);
                    }
                }
            }
        }
        
        else if (getStmtType(temp) == "if") {
            //add all next statements
            visit[temp] = 1;
            transfer(temp, path, true);
        }
        
        else {
            //assignment & calls statement base case
            list<int> tempModifies = getModifies().getModifiedBy(temp);
            //initial stmt --> add or calls not modified --> add
            if (visit[temp] == -1 || !contains(tempModifies, varModifiesIndex)) {
                transfer(temp, path, true);
            }
            visit[temp] = 1;
        }
    }
    //default return false
    return false;
}


void PKB::transfer(int temp, queue<int>& q, bool mode)
{
    list<int> tempNext;
    if (mode)
    {
        tempNext = getCFG().getNext(temp);
    }
    else
    {
        tempNext = getCFG().getPrevious(temp);
    }
    if (!tempNext.empty())
    {
        for (auto& x : tempNext)
        {
            q.push(x);
        }
    }
}

void PKB::clearQueue(queue<int>& q)
{
    while (!q.empty())
    {
        q.pop();
    }
}

bool PKB::contains(list<int> lst, int i)
{
    for (auto& x : lst)
    {
        if (x == i)
            return true;
    }
    return false;
}


STMTTYPE PKB::getStmtType(STMTNO stmtNo) {
    unordered_map<int, string>::iterator itKey = stmtTypeMap.find(stmtNo);
    if (itKey == stmtTypeMap.end()) {
        string nullResult = "";
        return nullResult;
    }
    else {
        return itKey->second;
    }
}
//End of Affects


//AffectsStar
list<int> PKB::getAffectsStar(int s2) {
	unordered_map<int, list<int>>::iterator itKey = affectsS2StarMap.find(s2);

	if (itKey != affectsS2StarMap.end()) {
		return itKey->second;
	}

	else {

		list<int> buffer;
		list<int> temp;
		list<int> todo;
		temp = getAffects(s2);
		temp.sort();
		todo = insertAll(buffer, temp);
		while (!todo.empty())
		{
			for (auto& x : todo)
			{
				list<int> temp2 = getAffects(x);
				temp2.sort();
				insertAll(temp, temp2);
			}
			todo = insertAll(buffer, temp);
		}
		affectsS2StarMap.insert(pair<int, list<int>>(s2, buffer));
		return buffer;
	}
}

list<int> PKB::getAffectedByStar(int s1) {
	unordered_map<int, list<int>>::iterator itKey = affectedByS1StarMap.find(s1);

	if (itKey != affectedByS1StarMap.end()) {
		return itKey->second;
	}

	else {

		list<int> buffer;
		list<int> temp;
		list<int> todo;
		temp = getAffectedBy(s1);
		temp.sort();
		todo = insertAll(buffer, temp);
		while (!todo.empty())
		{
			for (auto& x : todo)
			{
				list<int> temp2 = getAffectedBy(x);
				temp2.sort();
				insertAll(temp, temp2);
			}
			todo = insertAll(buffer, temp);
		}
		affectedByS1StarMap.insert(pair<int, list<int>>(s1, buffer));
		return buffer;
	}
}

bool PKB::isAffectsStarValid(int s1, int s2) {
	list<int> buffer;
	list<int> temp;
	list<int> todo;
	temp = getAffectedBy(s1);
	temp.sort();
	todo = insertAll(buffer, temp);
	while (!todo.empty())
	{
		for (auto& x : todo)
		{
			if (x == s2)
				return true;
			list<int> temp2 = getAffectedBy(x);
			temp2.sort();
			insertAll(temp, temp2);
		}
		todo = insertAll(buffer, temp);
	}
	return false;
}

list<int> PKB::insertAll(list<int>& insertTo, list<int>& insertFrom)
{
	list<int>::iterator begin = insertTo.begin();
	list<int>::iterator end = insertTo.end();
	list<int> newElements;
	for (auto& x : insertFrom)
	{
		list<int>::iterator it = search(begin, end, x);
		if (it == end || *it != x) //not in insertTo list
		{
			insertTo.insert(it, x);
			newElements.push_back(x);
		}
		begin = it;
	}
	return newElements;
}
//Binary Search Algorithm
list<int>::iterator PKB::search(list<int>::iterator first, list<int>::iterator last, int value)
{
	list<int>::difference_type len = distance(first, last); //count number of elements between first and last
	while (len > 0)
	{
		list<int>::iterator it = first;
		list<int>::difference_type halfLen = len / 2;
		advance(it, halfLen); //Advances the iterator it to middle position
		if (*it < value)
		{
			first = ++it;
			len -= halfLen + 1;
		}
		else
		{
			len = halfLen;
		}
	}
	return first;
}
//End of AffectsStar


//Pattern
void PKB::setAssignPattern(STMTNO stmtNo,LEFTPATTERN LHS, RIGHTPATTERN RHS) {
	getPatternTable().setAssignPattern(stmtNo, LHS, RHS);
}

void PKB::setWhilePattern(STMTNO stmtNo, VARID varID) {
	getPatternTable().setWhilePattern(stmtNo, varID);
}

void PKB::setIfPattern(STMTNO stmtNo, VARID varID) {
	getPatternTable().setIfPattern(stmtNo, varID);
}

list<STMTNO> PKB::getAssignPatternStmtNumber(PATTERNSIDE side, MATCHSTRING pattern) {
	return getPatternTable().getAssignPatternStmtNumber(side, pattern);
	
}

list<STMTNO> PKB::getStmtNoWithString(PATTERNSIDE side, MATCHSTRING pattern) {
	return getPatternTable().getStmtNoWithString(side, pattern);

}

LEFTPATTERN PKB::getAssignPatternLHS(STMTNO stmtNo) {
	return getPatternTable().getAssignPatternLHS(stmtNo);

}


RIGHTPATTERN PKB::getAssignPatternRHS(STMTNO stmtNo) {
	return getPatternTable().getAssignPatternRHS(stmtNo);
}

list<STMTNO> PKB::getIfPatternStmtNumber(VARNAME varName) {
	int varID = getVarTable().getVarID(varName);
	return getPatternTable().getIfPatternStmtNumber(varID);
}

list<STMTNO> PKB::getWhilePatternStmtNumber(VARNAME varName) {
	int varID = getVarTable().getVarID(varName);
	return getPatternTable().getWhilePatternStmtNumber(varID);
}

VARNAME PKB::getWhilePatternUses(STMTNO stmtNo) {
	int varID = getPatternTable().getWhilePatternUses(stmtNo);
	return getVarTable().getVarName(varID);
}

VARNAME PKB::getIfPatternUses(STMTNO stmtNo) {
	int varID = getPatternTable().getIfPatternUses(stmtNo);
	return getVarTable().getVarName(varID);
}

unordered_map<int, pair<string, string>> PKB::getAssignPatternMap() {
	return getPatternTable().getassignPatternMap();
}

unordered_map<int, int> PKB::getWhilePatternMap() {
	return getPatternTable().getWhilePatternMap();
}

unordered_map<int, int> PKB::getIfPatternMap() {
	return getPatternTable().getIfPatternMap();
}

int PKB::getAssignPatternMapSize() {
	return getPatternTable().getAssignPatternMapSize();
}

int PKB::getWhilePatternMapSize() {
	return getPatternTable().getWhilePatternMapSize();
}

int PKB::getWhilePatternMapReverseSize() {
	return getPatternTable().getWhilePatternMapReverseSize();
}

int PKB::getIfPatternMapSize() {
	return getPatternTable().getIfPatternMapSize();
}

int PKB::getIfPatternMapReverseSize() {
	return getPatternTable().getIfPatternMapReverseSize();
}

void PKB::insertConst(int val) {
	constList.push_back(val);
}

void PKB::insertCallsProcMap(PROCID p1, PROCNAME p2) {
	auto it1 = callsProcMap.find(p1);
	if (it1 != callsProcMap.end()) {
		callsProcMap[p1].push_back(p2);
	} else {
		callsProcMap[p1] = list<PROCNAME>();
		callsProcMap[p1].push_back(p2);
	}
}

void PKB::insertStmtLst(int s1) {
	stmtLst.push_back(s1);
}

void PKB::insertCallsStmtList(STMTNO s, PROCNAME p) {
	callsStmtList.push_back(pair<STMTNO, PROCNAME>(s, p));
}

unordered_map<PROCID, list<PROCNAME>> PKB::getCallsProcMap() {
	return callsProcMap;
}

list<pair<STMTNO, PROCNAME>> PKB::getCallsStmtList() {
	return callsStmtList;
}

list<int> PKB::getConstList() {
	return constList;
}

//CleanUp
void PKB::sortUsesModifiesMap() {
	getUses().sortUsesMap();
	getModifies().sortModifiesMap();
}

void PKB::sortConstList() {
	constList.sort();
	constList.unique();
}

void PKB::sortCallsProcMap() {
	for (auto it1 = callsProcMap.begin(); it1 != callsProcMap.end(); ++it1) {
		it1->second.sort();
		it1->second.unique();
	}
}

PatternTable& PKB::getPatternTable() {
	return patternTable;
}

ProcTable& PKB::getProcTable() {
	return procTable;
}

VarTable& PKB::getVarTable() {
	return varTable;
}

Parent& PKB::getParent() {
	return parent;
}

ParentStar& PKB::getParentStar() {
	return parentStar;
}

Follows& PKB::getFollows() {
	return follows;
}

FollowsStar& PKB::getFollowsStar() {
	return followsStar;
}

Modifies& PKB::getModifies() {
	return modifies;
}

Uses& PKB::getUses() {
	return uses;
}

Calls& PKB::getCalls() {
	return calls;
}

CallsStar& PKB::getCallsStar() {
	return callsStar;
}

CFG& PKB::getCFG() {
	return cfg;
}
