#include "stdafx.h"
#include "atsplugin.h"
#include "result.h"
// ------------------------------------------------------------------
void RESULT::init() {
	resetScoringItems();
	resetScoringItemsCount(true);
	resetCheckedList();
	score = 0;
	totalScore = 0;
	doorOpen = false;
	reseted = true;
}
// ------------------------------------------------------------------
void RESULT::resetScoringItems() {
	s_item.pointingPilotLamp = false;
	s_item.accelerateAfterDoorClose = false;
	s_item.pointingSpeed = 0;
	s_item.keepSpeedLimit = 0;
	s_item.keepConstantSpeed = 0;
	s_item.hornToWolker = 0;
	s_item.hornToPassenger = 0;
	s_item.hornToBridge = 0;
	s_item.reducedLight = 0;
	s_item.Gsenser = false;
	s_item.ebOver20 = false;
	s_item.ebStopping = false;
	s_item.reAccelerateInForm = false;
	s_item.brakeReload = false;
}
// ------------------------------------------------------------------
void RESULT::resetScoringItemsCount(bool b) {
	for (int i = 0; i < 2;++i) {
		s_itemCount.pointingSpeed[i] = 0;
		s_itemCount.keepSpeedLimit[i] = 0;
		s_itemCount.keepConstantSpeed[i] = 0;
		s_itemCount.hornToWolker[i] = 0;
		s_itemCount.hornToBridge[i] = 0;
		s_itemCount.hornToPassenger[i] = 0;
		s_itemCount.reducedLight[i] = 0;
		if (b) break;
	}
}
// ------------------------------------------------------------------
void RESULT::resetCheckedList() {
	p_cList->pointingPilotLamp = false;
	p_cList->accelerateAfterDoorClose = false;
	p_cList->pointingSpeed = false;
	p_cList->keepSpeedLimit = false;
	p_cList->keepConstantSpeed = false;
	p_cList->hornToWolker = false;
	p_cList->hornToBridge = false;
	p_cList->hornToPassenger = false;
	p_cList->reducedLight = false;
	p_cList->Gsenser = false;
	p_cList->ebOver20 = false;
	p_cList->ebStopping = false;
	p_cList->reAccelerateInForm = false;
	p_cList->brakeReload = false;
}
// ------------------------------------------------------------------
void RESULT::main(ATS_VEHICLESTATE vehicleState, int* panel, int* sound) {
	if (doorOpen && !reseted) {
		dispResult(panel);
		reset();
		reseted = true;
	} else if (!doorOpen) {
		reseted = false;
	}
}
// ------------------------------------------------------------------
void RESULT::reset() {
	resetScoringItems();
	resetScoringItemsCount(true);
	resetCheckedList();
	MessageBox(NULL, TEXT("reset"),
		TEXT("メッセージボックス"),
		MB_OK | MB_ICONINFORMATION);
}
// ------------------------------------------------------------------
void RESULT::dispResult(int* panel) {
}
// ------------------------------------------------------------------
int RESULT::calcScore() {
	return 0;
}
// ------------------------------------------------------------------
void RESULT::setDoorState(bool b) { doorOpen = b; }
scoringItems* RESULT::getScoringItemsPointer() { return ps_item; }
scoringItemsCount* RESULT::getScoringItemsCountPointer() { return ps_itemCount; }
checkedList* RESULT::getCheckedListPointer() { return p_cList; }
// ------------------------------------------------------------------