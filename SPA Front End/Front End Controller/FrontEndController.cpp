#include "FrontEndController.h"

using namespace std;

FrontEndController::FrontEndController() {
}

vector<Statement> FrontEndController::processSourceCode(string code) {
	return parser.processSourceCode(code);
}

void FrontEndController::createFollowsStarMap() {
	designExtractor.setFollowsStarMap();
}

void FrontEndController::createFollowsStarMapReverse() {
	designExtractor.setFollowsStarMapReverse();
}

void FrontEndController::createParentStarMap() {
	designExtractor.setParentStarMap();
}

void FrontEndController::createParentStarMapReverse() {
	designExtractor.setParentStarMapReverse();
}

void FrontEndController::createCallsMap() {
	designExtractor.setCallsMap();
}

void FrontEndController::createCallsStarMap() {
	designExtractor.setCallsStarMap();
}

void FrontEndController::createStmtCallsMap() {
	designExtractor.setStmtCallsMap();
}

void FrontEndController::updateProcUsesMap() {
	designExtractor.updateProcUsesMap();
}

void FrontEndController::updateProcModifiesMap() {
	designExtractor.updateProcModifiesMap();
}

void FrontEndController::updateStmtUsesMap() {
	designExtractor.updateStmtUsesMap();
}

void FrontEndController::updateStmtModifiesMap() {
	designExtractor.updateStmtModifiesMap();
}

void FrontEndController::sortUsesModifiesMap() {
	designExtractor.sortUsesModifiesMap();
}

void FrontEndController::createCFG() {
	designExtractor.buildCFG();
}
