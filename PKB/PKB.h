#pragma once

#include <vector>

#include "PKB.h"
#include "Follows.h"
#include "FollowsStar.h"
#include "Modifies.h"
#include "Parent.h"
#include "ParentStar.h"
#include "PatternTable.h"
#include "ProcTable.h"
#include "Statement.h"
#include "Uses.h"
#include "VarTable.h"
#include "Calls.h"
#include "CallsStar.h"
#include "CFG.h"

using namespace std;

typedef int STMTNO;
typedef int VARID;
typedef int PROCID;
typedef int PATTERNSIDE;
typedef string VARNAME;
typedef string PROCNAME;
typedef string MATCHSTRING;
typedef string LEFTPATTERN;
typedef string RIGHTPATTERN;
typedef string STMTTYPE;

class PKB {
public:
	static PKB* getPKBInstance();
	static void removePKBInstance();

	void updateSourceList(int, int, int, string, string);
	vector<Statement> getSourceList();

	list<STMTNO> getStmtLst();

	void insertStmtLst(int s1);
	unordered_map<int, int> getSourceListIndex();
	int getTotalNumOfProgLine();

	//Calls
	void setCalls(PROCID, PROCID);
	void sortCallsMap();

	list<PROCID> getCalls(PROCID);
	list<PROCID> getCalledBy(PROCID);
	unordered_map<int, list<int>> getCallsMap();
	unordered_map<int, list<int>> getCallsMapReverse();
	list<PROCID> getCalls(PROCNAME);
	list<PROCID> getCalledBy(PROCNAME);
	bool isCallsValid(PROCNAME, PROCNAME);
	bool isCallsValid(PROCID, PROCID);
	int getCallsMapSize();
	int getStmtCallsMapSize();
	int getCallsMapReverseSize();


	/* New added! */
	unordered_map<STMTNO, PROCID> getStmtCallsMap();
	unordered_map<PROCID, list<STMTNO>> getStmtCallsMapReverse();
	int getProcCalledByStmt(STMTNO); // get proc called by stmt
	list<int> getStmtCallsProc(PROCID); // get list of stmt that calls proc
	bool isStmtCallsValid(STMTNO, PROCID); // get bool whether stmt calls proc
	void setStmtCalls(STMTNO, PROCID);

	//CallsStar
	void setCallsStar(PROCID, PROCID);
	void sortCallsStarMap();

	list<PROCID> getCallsStar(PROCID);
	list<PROCID> getCalledStarBy(PROCID);
	unordered_map<int, list<int>> getCallsStarMap();
	unordered_map<int, list<int>> getCallsStarMapReverse();
	list<PROCID> getCallsStar(PROCNAME);
	list<PROCID> getCalledStarBy(PROCNAME);
	bool isCallsStarValid(PROCNAME, PROCNAME);
	bool isCallsStarValid(PROCID, PROCID);
	int getCallsStarMapSize();
	int getCallsStarMapReverseSize();

	//Follows
	unordered_map<int, int> getFollowsMap();
	unordered_map<int, int> getFollowsMapReverse();
	void setFollows(STMTNO, STMTNO);
	STMTNO getFollows(STMTNO);
	STMTNO getFollowedBy(STMTNO);
	bool isFollowsValid(STMTNO, STMTNO);
	int getFollowsMapSize();
	int getFollowsMapReverseSize();

	//FollowsStar
	unordered_map<int, list<int>> getFollowsStarMap();
	unordered_map<int, list<int>> getFollowsStarMapReverse();
	void setFollowsStar(int, list<int>);
	void setFollowsStarMapReverse(unordered_map<int, list<int>>);
	list<STMTNO> getFollowsStar(STMTNO);
	list<STMTNO> getFollowsStarBy(STMTNO);
	bool isFollowsStarValid(STMTNO, STMTNO);
	int getFollowsStarMapSize();
	int getFollowsStarMapReverseSize();

	//Parent
	void setParent(STMTNO, STMTNO);
	STMTNO getParent(STMTNO);
	unordered_map<int, list<int>> getParentMap();
	unordered_map<int, int> getParentMapReverse();
	list<STMTNO> getAllChildren(STMTNO);
	bool isParentValid(STMTNO, STMTNO);
	int getParentMapSize();
	int getParentMapReverseSize();

	//ParentStar
	unordered_map<int, list<int>> getParentStarMap();
	unordered_map<int, list<int>> getParentStarMapReverse();
	void setParentStar(int, list<int>);
	void setParentStarMapReverse(unordered_map<int, list<int>>);
	list<STMTNO> getAllChildrenStar(STMTNO);
	list<STMTNO> getParentStar(STMTNO);
	bool isParentStarValid(STMTNO, STMTNO);
	int getParentStarMapSize();
	int getParentStarMapReverseSize();
	
	//Next
	void buildCFG();
	int getProcFirstStmt(int ProcNo);
	list<STMTNO> getNext(STMTNO);
	list<STMTNO> getPrevious(STMTNO);
	bool isNextValid(STMTNO, STMTNO);


	//NextStar
	list<STMTNO> getNextStar(STMTNO);
	list<STMTNO> getPreviousStar(STMTNO);
	bool isNextStarValid(STMTNO, STMTNO);

	
	//VarTable
	int getVarTableSize();
	VARID insertVar(VARNAME);
	VARID getVarID(VARNAME);
	VARNAME getVarName(VARID);


	//ProcTable
	int getProcTableSize();
	PROCID insertProc(PROCNAME);
	PROCID getProcID(PROCNAME);
	PROCNAME getProcName(PROCID);

	//Uses
	unordered_map<int, list<int>> getProcUsesMap();
	unordered_map<int, list<int>> getProcUsesMapReverse();
	unordered_map<int, list<int>> getStmtUsesMap();
	unordered_map<int, list<int>> getStmtUsesMapReverse();

	void setUses(PROCID, STMTNO, VARID);
	void setStmtUses(STMTNO, VARID);
	void setProcUses(PROCID, VARID);
	void sortUsesMap();

	list<STMTNO> getUses(VARNAME);
	list<VARID> getUsedBy(STMTNO);
	bool isUsesValid(STMTNO, VARNAME);

	list<PROCID> getProcUses(VARNAME);
	list<VARID> getProcUsedBy(PROCNAME);
	bool isProcUsesValid(PROCNAME, VARNAME);

	int getStmtUsesMapSize();
	int getStmtUsesMapReverseSize();
	int getProcUsesMapSize();
	int getProcUsesMapReverseSize();

	//Modifies
	unordered_map<int, list<int>> getProcModifiesMap();
	unordered_map<int, list<int>> getProcModifiesMapReverse();
	unordered_map<int, list<int>> getStmtModifiesMap();
	unordered_map<int, list<int>> getStmtModifiesMapReverse();

	void setModifies(PROCID, STMTNO, VARID);
	void setStmtModifies(STMTNO, VARID);
	void setProcModifies(PROCID, VARID);
	void sortModifiesMap();

	list<STMTNO> getModifies(VARNAME);
	list<VARID> getModifiedBy(STMTNO);
	bool isModifiesValid(STMTNO, VARNAME);


	list<PROCID> getProcModifies(VARNAME);
	list<VARID> getProcModifiedBy(PROCNAME);
	bool isProcModifiesValid(PROCNAME, VARNAME);

	int getStmtModifiesMapSize();
	int getStmtModifiesMapReverseSize();
	int getProcModifiesMapSize();
	int getProcModifiesMapReverseSize();
	
	//Affects
	//getAffects(s2)
	list<int> getAffects(int);
	list<int> getAffectedBy(int);
	void transfer(int, queue<int>&, bool);
	void clearQueue(queue<int>&);
	STMTTYPE getStmtType(STMTNO);
	bool contains(list<int>, int);
	void processAffectsMap();
	void insertIntoS2Map(int, int);
	void clearCacheMaps();
	bool isAffectsValid(int, int);
	unordered_map<int, list<int>> affectedByS1Map;
	unordered_map<int, list<int>> affectsS2Map;
	//to get StmtType use getStmtType

	//AffectsStar
	list<int> getAffectsStar(int);
	list<int> getAffectedByStar(int);
	bool isAffectsStarValid(int, int);
	list<int> insertAll(list<int>&, list<int>&);
	list<int>::iterator search(list<int>::iterator, list<int>::iterator, int);
	unordered_map<int, list<int>> affectedByS1StarMap;
	unordered_map<int, list<int>> affectsS2StarMap;

	//PatternTable
	void setAssignPattern(STMTNO, LEFTPATTERN, RIGHTPATTERN);
	void setWhilePattern(STMTNO, VARID);
	void setIfPattern(STMTNO, VARID);

	list<STMTNO> getAssignPatternStmtNumber(PATTERNSIDE, MATCHSTRING);
	LEFTPATTERN getAssignPatternLHS(STMTNO);
	RIGHTPATTERN getAssignPatternRHS(STMTNO);

	list<STMTNO> getWhilePatternStmtNumber(VARNAME);
	list<STMTNO> getIfPatternStmtNumber(VARNAME);

	VARNAME getIfPatternUses(STMTNO);
	VARNAME getWhilePatternUses(STMTNO);
	list<STMTNO> getStmtNoWithString(PATTERNSIDE, MATCHSTRING);
	unordered_map<int, pair<string, string>> getAssignPatternMap();
	unordered_map<int, int> getWhilePatternMap();
	unordered_map<int, int> getIfPatternMap();

	int getAssignPatternMapSize();
	int getWhilePatternMapSize();
	int getWhilePatternMapReverseSize();
	int getIfPatternMapSize();
	int getIfPatternMapReverseSize();

	//Constant List
	void insertConst(int val);
	list<int> getConstList();

	// Calls Map and List
	void insertCallsProcMap(PROCID, PROCNAME);
	void insertCallsStmtList(STMTNO, PROCNAME);
	unordered_map<PROCID, list<PROCNAME>> getCallsProcMap();
	list<pair<STMTNO, PROCNAME>> getCallsStmtList();
	
	//Cleanup
	void sortUsesModifiesMap();
	void sortConstList();
	void sortCallsProcMap();

private:
	static PKB* PKBInstance;
	static bool PKBInstanceFlag;

	PatternTable patternTable;
	ProcTable procTable;
	VarTable varTable;
	Parent parent;
	ParentStar parentStar;
	Follows follows;
	FollowsStar followsStar;
	Modifies modifies;
	Uses uses;
	Calls calls;
	CallsStar callsStar;
	CFG cfg;
	
	PatternTable& getPatternTable();
	ProcTable& getProcTable();
	VarTable& getVarTable();
	Parent& getParent();
	ParentStar& getParentStar();
	Follows& getFollows();
	FollowsStar& getFollowsStar();
	Modifies& getModifies();
	Uses& getUses();
	Calls& getCalls();
	CallsStar& getCallsStar();
	CFG& getCFG();

	
	vector<Statement> sourceList;
	list<STMTNO> stmtLst;
	unordered_map<int, STMTTYPE> stmtTypeMap;
	unordered_map<PROCID, list<PROCNAME>> callsProcMap;
	list<pair<STMTNO, PROCNAME>> callsStmtList;
	unordered_map<int, int> sourceListIndex;
	list<int> constList;
};
