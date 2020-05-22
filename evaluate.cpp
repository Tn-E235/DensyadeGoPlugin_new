#include "stdafx.h"
#include "atsplugin.h"
#include "result.h"
#include "evaluate.h"
// ------------------------------------------------------------------
void EVALUTE::init() {
	currentSpeed = 0;
	currentTime = 0;
	currentDistance = 0.0;
	delta_T = 0;
	b_notch = 0;
	p_notch = 0;
	doorOpen = false;
	keyPush = false;
	hornKey = false;
	hornDuration = 0;
	inStation = false;
	for (int i = 0; i < 3; ++i) {
		box[i].idx = 0;
		box[i].totalTime = 0;
		box[i].score = 0;
		hornInfo[i].enable = false;
		hornInfo[i].distance = 0;
		hornInfo[i].noicePoint = 0.0;
	}
}
// ------------------------------------------------------------------
void EVALUTE::init(int n) {
	box[n].idx = 0;
	box[n].totalTime = 0;
	box[n].score = 0;
}
// ------------------------------------------------------------------
void EVALUTE::init(dispEvalute* po, int n) {
	po[n].idx = 0;
	po[n].totalTime = 0;
	po[n].score = 0;
}
// ------------------------------------------------------------------
void EVALUTE::main(ATS_VEHICLESTATE vehicleState, int* panel, int* sound) {
	currentTime = vehicleState.Time;
	delta_T = currentTime - delta_T;
	currentDistance = vehicleState.Location;
	currentTime = vehicleState.Time;
	currentSpeed = (int)vehicleState.Speed;

	// 停止位置取得
	if (doorOpen) lastStopDistance = currentDistance;
	// 戸閉後指差喚呼
	pointingPilotLamp(sound);
	// 戸閉後加速
	acclerateAfterDoorClose(sound);
	// 速度計指差喚呼
	//					実装済み
	// 制限速度遵守
	//					実装済み
	// 定速ﾎﾟｲﾝﾄ遵守
	//					実装済み
	// 保線作業員に警笛
	// 鉄橋に警笛
	// ホーム乗客に警笛
	hornTo(sound);
	// すれ違い車両に減光
	//					実装しません
	// Gセンサー超過
	// 
	// 20km/h以上で非常ブレーキ→急制動
	// 20km/h以下で非常ブレーキ→非常停車
	emergencyBrake(sound);
	// 構内再加速
	reAccelerateInForm(sound);
	// ブレーキ込め直し
	brakeReload(sound);

	disp(panel);
	updateInfo();
}
// ------------------------------------------------------------------
void EVALUTE::setDisp(int i, int s) {
	if (box[0].idx > 0) pushup();
	box[0].idx = i;
	box[0].score = s;
	box[0].totalTime = 0;
}
// ------------------------------------------------------------------
void EVALUTE::setDisp(dispEvalute* po, int i, int s) {
	if (po == nullptr) {
		MessageBox(NULL, TEXT("ぬるぽ"),
			TEXT("メッセージボックス"),
			MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (po[0].idx > 0) pushup(po);
	po[0].idx = i;
	po[0].score = s;
	po[0].totalTime = 0;
}
// ------------------------------------------------------------------
void EVALUTE::updateInfo() {
	for (int i = 0; i < 5; ++i) {
		if (box[i].idx > 0) box[i].totalTime = (int)(box[i].totalTime + (1000.0/60.0));// 1/60秒;
		//  if (box[i].idx > 0) box[i].totalTime = box[i].totalTime + delta_T;// 1/60秒;
		if (box[i].totalTime > 3000) init(i);
	}
	hornDuration += delta_T;
	if (hornDuration > 5000) hornKey = false;
}
// ------------------------------------------------------------------
void EVALUTE::pushup() {
	int idx = 0;
	int totalTime = 0;
	int score = 0;
	for (int i = 4; i > 0; --i) {
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
// ------------------------------------------------------------------
void EVALUTE::pushup(dispEvalute* po) {
	int idx = 0;
	int totalTime = 0;
	int score = 0;
	for (int i = 4; i > 0; --i) {
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
// ------------------------------------------------------------------
void EVALUTE::disp(int* panel) {
	for (int i = 0; i < 5; ++i) {
		if (box[i].idx < 1) {
			panel[70 + i] = 0;
			panel[75 + i] = 0;
			panel[80 + i] = 0;
			continue;
		}
		panel[70 + i] = box[i].idx;
		panel[75 + i] = (box[i].score > 0) ? 1 : 2;
		panel[80 + i] = box[i].score + 1;
	}
}
void EVALUTE::reset() { }
// ------------------------------------------------------------------
void EVALUTE::pointingPilotLamp(int* sound) {
	if (!doorOpen && isStopPosition()) {
		if (p_notch == 0 && b_notch > 0 && currentSpeed == 0) {
			if (keyPush) {
				// ☆3
				if (p_cList->pointingPilotLamp) return;
				p_cList->pointingPilotLamp = true;
				sound[0] = ATS_SOUND_PLAY;
				setDisp(1, 3);
			}
		} else if (currentSpeed > 0) {
			// ☆0
			if (p_cList->pointingPilotLamp) return;
			p_cList->pointingPilotLamp = true;
			setDisp(1, 0);
		}
	}
}
// ------------------------------------------------------------------
void EVALUTE::acclerateAfterDoorClose(int* sound) {
	if (isStopPosition() && p_notch > 0) {
		if (p_cList->accelerateAfterDoorClose) return;
		if (!doorOpen) {
			// ☆3
			sound[0] = ATS_SOUND_PLAY;
			setDisp(2, 3);
		} else {
			// ☆0
			setDisp(2, 0);
		}
		p_cList->accelerateAfterDoorClose = true;
	}
}
// ------------------------------------------------------------------
bool EVALUTE::isStopPosition() {
	if (currentDistance >= lastStopDistance - offset &&
		currentDistance <= lastStopDistance + offset)
		return true;
	return false;
}
// ------------------------------------------------------------------
int EVALUTE::getStar(int i, double d) {
	if (d == 0.0) return 0;
	double val = d / (double)i;
	if (val > 1.0 / 3.0 * 2.0) {
		return 3;
	} else if (val > 1.0 / 3.0) {
		return 2;
	} else {
		return 1;
	}
	return 0;
}
// ------------------------------------------------------------------
void EVALUTE::hornTo(int* sound) {
	for (int i = 0; i < 3;++i) {
		if (!hornInfo[i].enable) continue;
		double remainingDistance = 
			hornInfo[i].noicePoint + (double)hornInfo[i].distance - currentDistance;
		if (hornKey) {
			int star = getStar(hornInfo[i].distance, remainingDistance);
			setDisp(6+i, star);
			hornInfo[i].enable = false;
			continue;
		}
		if (remainingDistance < 0) {
			setDisp(6 + i, 0);
			hornInfo[i].enable = false;
		}
	}
}
// ------------------------------------------------------------------
void EVALUTE::emergencyBrake(int*) {
	if(b_notch != ebNotch) isEB = false;
	if (b_notch == ebNotch && !isEB && currentSpeed > 0) {
		isEB = true;
		if (currentSpeed >= 20) {
			setDisp(11, 0);
		} else {
			setDisp(12, 0);
		}
	}
}
// ------------------------------------------------------------------
void EVALUTE::reAccelerateInForm(int*) {
	if (!inStation || p_cList->reAccelerateInForm) return;
	if (maxPnotchInStation < p_notch) { 
		p_cList->reAccelerateInForm = true;
		// setDisp(1, 0);
	}
}
// ------------------------------------------------------------------
void EVALUTE::brakeReload(int*) {
	if (!inStation || p_cList->brakeReload) return;
	if (maxBnotchInStation == 0) return;
	if (b_notch > maxBnotchInStation) maxBnotchInStation = b_notch;
	if (b_b_notch == b_notch) brakeDuration += delta_T;
	if (b_b_notch < b_notch && brakeDuration < 500) {
		brakeDuration = 0;
	} else if (brakeDuration > 500) {
		maxBnotchInStation = b_notch;
	}
	b_b_notch = b_notch;
}
// ------------------------------------------------------------------
void EVALUTE::setHornInfo(int sendData) {
	int idx = sendData / 1000000;
	int distance = sendData % 1000000;
	if (idx > 3 || idx < 1) return;
	hornInfo[idx - 1].enable = true;
	hornInfo[idx - 1].distance = distance;
	hornInfo[idx - 1].noicePoint = currentDistance;
}
// ------------------------------------------------------------------
void EVALUTE::setHornKey(int type) {
	if (type >= 0) {
		hornKey = true; 
		hornDuration = 0;
	} 
}
// ------------------------------------------------------------------
void EVALUTE::setInStation(int sendData) {
	inStation = true;
	maxPnotchInStation = p_notch;
	maxBnotchInStation = b_notch;
	b_b_notch = b_notch;
}
// ------------------------------------------------------------------
void EVALUTE::setKey(bool b) { keyPush = b; }
void EVALUTE::setDoorState(bool b) { doorOpen = b; }
void EVALUTE::setNotchState(int b, int p) { b_notch = b; p_notch = p; }
void EVALUTE::setEBnotch(int notch) { ebNotch = notch; }
void EVALUTE::setLastStopDistance(int dis) { if (doorOpen) lastStopDistance = dis; }
void EVALUTE::setScoringItemsPointer(scoringItems* p) { p_s_item = p; }
void EVALUTE::setScoringItemsCountPointer(scoringItemsCount* p) { p_s_itemCount = p; }
void EVALUTE::setChechedListPointer(checkedList* p) { p_cList = p; }
dispEvalute* EVALUTE::getBoxPointer() { return p; }
