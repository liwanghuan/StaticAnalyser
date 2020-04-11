
#include "CFG.h"
const string EXCEPTION = "out of bound exception";

CFG::CFG()
{
}

void CFG::buildCFG(vector<Statement> statementList)
{
		typeTable.resize(statementList.size(), string());
		statBuffer.clear();
		codeLst = statementList;
		codeIterator = statementList.begin(); 
		nodeIndex = 0;
		size = 0;
		currentProcCount = -1;
		procMap.clear();
		procTable.clear();
		initializeStack(); 

		while (codeIterator != statementList.end())
		{
			solveCode();
			codeIterator++;
		}
		storeTable();
}

void CFG::solveCode()
{
	string stmtData = codeIterator->getStatementData();
	int stmtNo = codeIterator->getStatementNum();
	string stmtType = codeIterator->getstatementType();
	if (stmtNo != -1 || stmtType == "else")
	{
		procMap.insert(make_pair(stmtNo, currentProcCount));
		typeTable[stmtNo] = codeIterator->getstatementType();
		if (!isProcFirstStmt)
		{
			procTable.push_back(stmtNo);
			isProcFirstStmt = true;
		}
	}
	// procedure statement type
	if (stmtType == "procedure")
	{
		currentProcCount++;
		isProcFirstStmt = false;
		initializeStack();
		statBuffer.clear();
		nodeInOperation.push(std::make_pair(-1, "procedure"));
	}

	//if || while container statement type
	else if (stmtType == "if" || stmtType == "while")
	{
		int tempNodeIndex = createNormalStmtNode();
		int tempContainerNodeIndex = createContainerNode(stmtNo);
		if (tempNodeIndex != -1 || stmtType == "else")
		{
			solveNode(tempNodeIndex, "normal");
		}
		solveNode(tempContainerNodeIndex, stmtType);
	}

	else //not container and not procedure statement type
	{
		statBuffer.push_back(stmtNo); //buffer to push multiple stmtNo into 1 node, with commas
		int brace = codeIterator->getNumOfCloseBraces();
		for (int i = 0; i < brace; i++) //cater for nested loops
		{
			int tempNodeIndex = createNormalStmtNode(); 
			if (tempNodeIndex != -1 || stmtType == "else") //buffer is not empty
			{
				solveNode(tempNodeIndex, "normal");
			}
			pair<int, string> temp = nodeInOperation.top();
			nodeInOperation.pop();
			pair<int, string> top = nodeInOperation.top();
			string typetemp = temp.second;
			string typetop = top.second;
			if (top.second == "while")
			{
				insertNext(temp.first, top.first);
				top.second = "normal";
				nodeInOperation.pop();
				nodeInOperation.push(top);
			}
			else if (top.second == "if")
			{
				top.second = "else";
				nodeInOperation.pop();
				nodeInOperation.push(temp);
				nodeInOperation.push(top);
				codeIterator++;
			}
			else if (top.second == "else")
			{
				nodeInOperation.pop();
				pair<int, string> temp2 = nodeInOperation.top();
				nodeInOperation.pop();
				int dummy = createDummyNode();
				insertNext(temp2.first, dummy);
				insertNext(temp.first, dummy);
				nodeInOperation.push(std::make_pair(dummy, "normal"));
			}
			else if (top.second == "normal")
			{
				insertNext(top.first, temp.first);
				nodeInOperation.pop();
				nodeInOperation.push(temp);
				initializeStack();
			}
			else if (top.second == "procedure")
			{
				insertNext(temp.first, -1);
				initializeStack();
			}
			else
			{
				continue;
			}
		}
	}
}

int CFG::createNormalStmtNode()
{
	CFGNode* temp = NULL;
	if (!statBuffer.empty())
	{
		int begin = statBuffer.front();
		int end = statBuffer.back();
		temp = new CFGNode(nodeIndex, begin, end);
		statBuffer.clear();
		return insertNode(temp);
	}
	else//buffer is empty
	{
		return -1;
	}
}

//Reset nodeInOperation Stack to empty
void CFG::initializeStack()
{
	while (!nodeInOperation.empty())
	{
		nodeInOperation.pop();
	}
}

//Container node
int CFG::createContainerNode(int index)
{
	CFGNode* temp = new CFGNode(nodeIndex, index, index);
	return insertNode(temp);
}

//Dummy node
int CFG::createDummyNode()
{
	CFGNode* temp = new CFGNode(nodeIndex, -1, -1);
	return insertNode(temp);
}

//insert into nodeMap
int CFG::insertNode(CFGNode* node)
{
	nodeMap.insert(std::make_pair(nodeIndex, node));
	nodeIndex++;
	return nodeIndex - 1;
}

//insert into nextCfgNode 
void CFG::insertNext(int position, int value)
{
	if (position >= 0)
	{

		if (nextCfgNode[position].empty() || value != nextCfgNode[position].front())
		{
			nextCfgNode[position].push_back(value);
		}
	}
}
//insert into previousTable
void CFG::insertPreviousTable(int position, int value, unordered_map<int, list<int>>& previousTable)
{
	if (position >= 0 && value != -1)
	{
		previousTable[position].push_back(value);
	}
}

void CFG::solveNode(int index, string type)
{
	int topIndex = nodeInOperation.top().first;
	string topType = nodeInOperation.top().second;
	if (topType != "procedure")  //solve node in a container
	{
		insertNext(topIndex, index);
		if (topType == "normal")
		{
			nodeInOperation.pop();
		}
	}
	nodeInOperation.push(std::make_pair(index, type));
}

//store NextTable and PreviousTable using nextCfgNode
void CFG::storeTable()
{
	list<int> empty;
	for (int index = 0; index < (nextCfgNode.size()+1); index++)
	{
		try {
			CFGNode* node = nodeMap.at(index);
			int begin = node->getStart();
			int end = node->getEnd();
			int i = 0;
			list<int> temp;
			list<int> buffer;
			
			for (i = begin; i < end; i++) //for next and previous storage within a MultipleStmt Node
			{
				temp.push_back(i + 1);
				nextTable[i] = temp;
				insertPreviousTable(i + 1, i, previousTable);
				temp.clear();
				size++;
			}

			temp = nextCfgNode[index];
			for (auto& x : temp) //for next and previous storage across nodes
			{
				while (x != -1)
				{
					CFGNode* tempNode = nodeMap.at(x);
					if (tempNode->getStart() != -1)
					{
						buffer.push_back(tempNode->getStart());
						insertPreviousTable(tempNode->getStart(), end, previousTable);
						break;
					}
					else
					{
						x = nextCfgNode[x].front();
					}
				}
			}
			if (buffer.size() != 0 && end != -1) {
			nextTable[end] = buffer; //insertNextTable
			}
			size++;
		}
		catch (...) {
			break;
		}
	}
}

//to get Next || Previous Star
list<int> CFG::traverse(int index, unordered_map<int, list<int>> table)
{
	list<int> starList; //list of stmtNo. to be inserted to the respective Star table row
	vector<bool> hasVisited; //ensure no duplication of stmtNo.
	queue<int> toVisit; //to be visited as key in the table
	list<int> temp = table[index];
	hasVisited.resize(size + 1, false);
	for (auto& x : temp)
	{
		toVisit.push(x);
		hasVisited[x] = true;
	}
	while (!toVisit.empty())
	{
		int tempIndex = toVisit.front();
		toVisit.pop();
		starList.push_back(tempIndex);
		temp = table[tempIndex];
		for (auto& x : temp)
		{
			if (!hasVisited[x]) {
				toVisit.push(x);
				hasVisited[x] = true;
			}
		}
	}
	return starList;
}
int CFG::getProcFirstStmt(int ProcNo)
{
	return procTable[ProcNo];
}

int CFG::getProcMap(int statementNo)
{
	return procMap.at(statementNo);
}

list<int> CFG::getPrevious(int value)
{
	list<int> buffer; 
	if (value <= size && value >= 1)
	{
		return previousTable[value];
	}
	else {
		return buffer;
	}
}

list<int> CFG::getNext(int key)
{
	list<int> buffer;
	if (key <= size && key >= 1)
	{
		return nextTable[key];
	}
	else {
		return buffer;
	}

}

bool CFG::isNextValid(int i, int j)
{
	if (i <= size && i >= 1 &&
		j <= size && j >= 1)
	{
		list<int> temp = getNext(i);
		for (auto& x : temp)
		{
			if (x == j)
			{
				return true;
			}
		}
		return false;
	}
	else {
		return false;
	}
}

list<int> CFG::getPreviousStar(int value)
{
	list<int> buffer;
	if (value <= size && value >= 1)
	{
		unordered_map<int, list<int>>::iterator itKey = previousStarTable.find(value);

		if (itKey != previousStarTable.end()) {
			return itKey->second;
		}
		else {
			buffer = traverse(value, previousTable);
			previousStarTable.insert(pair<int, list<int>>(value, buffer));
			return buffer;
		}
	}
	else {
		return buffer;
	}
}

list<int> CFG::getNextStar(int key)
{
	list<int> buffer;

	if (key <= size && key >= 1)
	{
		unordered_map<int, list<int>>::iterator itKey = nextStarTable.find(key);

		if (itKey != nextStarTable.end()) {
			return itKey->second;
		}
		else {
			buffer = traverse(key, nextTable);
			nextStarTable.insert(pair<int, list<int>>(key, buffer));
			return buffer;
		}
	}
	else {
		return buffer;
	}
}

bool CFG::isNextStarValid(int i, int j)
{
	if (!(i <= size && i >= 1)) {
		return false;
	}
	vector<bool> hasVisited;
	queue<int> toVisit;
	list<int> temp = nextTable[i];
	hasVisited.resize(size + 1, false);
	for (auto& x : temp)
	{
		toVisit.push(x);
		hasVisited[x] = true;
	}
	while (!toVisit.empty())
	{
		int tempIndex = toVisit.front();
		toVisit.pop();
		if (tempIndex == j)
		{
			return true;
		}
		temp = nextTable[tempIndex];
		for (auto& x : temp)
		{
			if (!hasVisited[x]) {
				toVisit.push(x);
				hasVisited[x] = true;
			}
		}
	}
	return false;
}

void CFG::clearStarMap() {
	//dont clear map
	nextStarTable = unordered_map<int, list<int>>();
	previousStarTable = unordered_map<int, list<int>>();
}
