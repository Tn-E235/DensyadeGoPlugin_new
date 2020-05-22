#include "stdafx.h"
#include "atsplugin.h"
#include "evaluate.h"

void EVALUTE::init() {
	currentTime = 0;
	delta_T = 0;
	for (int i = 0; i < 3; ++i) {
		box[i].idx = 0;
		box[i].totalTime = 0;
		box[i].score = 0;
	}
}

void EVALUTE::init(int n) {
	box[n].idx = 0;
	box[n].totalTime = 0;
	box[n].score = 0;
}

void EVALUTE::main(ATS_VEHICLESTATE vehicleState, int* panel, int* sound) {
	currentTime = vehicleState.Time;
	delta_T = currentTime - delta_T;
	disp(panel);
	updateInfo();
}

void EVALUTE::setDisp(int i, int s) {
	if (box[0].idx > 0) pushup();
	box[0].idx = i;
	box[0].score = s;
	box[0].totalTime = 0;
}

void EVALUTE::setDisp(dispEvalute* po, int i, int s) {
	if (po == nullptr) {
		MessageBox(NULL, TEXT("ぬるぽ"),
			TEXT("メッセージボックス"),
			MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (po[0].idx > 0) pushup();
	po[0].idx = i;
	po[0].score = s;
	po[0].totalTime = 0;
}

dispEvalute* EVALUTE::getBoxPointer() { return p; }

void EVALUTE::updateInfo() {
	for (int i = 0; i < 3; ++i) {
		if (box[i].idx > 0) box[i].totalTime = (int)(box[i].totalTime + (1000.0/60.0));// 1/60秒;
		//  if (box[i].idx > 0) box[i].totalTime = box[i].totalTime + delta_T;// 1/60秒;
		if (box[i].totalTime > 3000) init(i);
	}
}

void EVALUTE::pushup() {
	int idx = 0;
	int totalTime = 0;
	int score = 0;
	for (int i = 2; i > 0; --i) {
		idx = box[i - 1].idx;
		totalTime = box[i - 1].totalTime;
		score = box[i - 1].score;
		box[i].idx = idx;
		box[i].totalTime = totalTime;
		box[i].score = score;
	}
	box[0].idx = 0;
	box[0].totalTime = 0;
	box[0].score = 0;
}

void EVALUTE::pushup(dispEvalute* po) {
	int idx = 0;
	int totalTime = 0;
	int score = 0;
	for (int i = 2; i > 0; --i) {
		idx = po[i - 1].idx;
		totalTime = po[i - 1].totalTime;
		score = po[i - 1].score;
		po[i].idx = idx;
		po[i].totalTime = totalTime;
		po[i].score = score;
	}
	po[0].idx = 0;
	po[0].totalTime = 0;
	po[0].score = 0;
}

void EVALUTE::disp(int* panel) {
	for (int i = 0; i < 3; ++i) {
		if (box[i].idx < 1) {
			panel[70 + i] = 0;
			panel[73 + i] = 0;
			panel[76 + i] = 0;
			continue;
		}
		panel[70 + i] = box[i].idx;
		panel[73 + i] = (box[i].score > 0) ? 1 : 2;
		panel[76 + i] = box[i].score + 1;
	}
}
