#include "stdafx.h"
#include "atsplugin.h"
#include "result.h"
#include "evaluate.h"
#include "stationDB.h"
#include "speedNoice.h"
#include "gSensor.h"
#include "dengo.h"
#include <cmath>
// ------------------------------------------------------------------
void DENGO::init() {
	station.init();
	evalute.init();
	s_noice.init();
	result.init();

	p_station      = station.getStationDataPointer();
	p_box          = evalute.getBoxPointer();
	p_s_itemsCount = result.getScoringItemsCountPointer();
	p_cList        = result.getCheckedListPointer();

	s_noice.setBoxPointer(p_box);
	s_noice.setChechedListPointer(p_cList);
	s_noice.setScoringItemsCountPointer(p_s_itemsCount);
	evalute.setChechedListPointer(p_cList);
	evalute.setScoringItemsCountPointer(p_s_itemsCount);

	gsensor.setChechedListPointer(p_cList);
	gsensor.setScoringItemsCountPointer(p_s_itemsCount);
	gsensor.setBoxPointer(p_box);

	update = true;
	updateCurrentStation = 0;
	finalStop = false;
	currentStation = 0;
	nextStation = 0;
	nextStopStation = 0;
}
// ------------------------------------------------------------------
void DENGO::main(ATS_VEHICLESTATE vehicleState, int* panel, int* sound){
	sound[0] = ATS_SOUND_CONTINUE;
	sound[1] = ATS_SOUND_CONTINUE;
	sound[2] = ATS_SOUND_CONTINUE;
	sound[3] = ATS_SOUND_CONTINUE;
	sound[4] = ATS_SOUND_CONTINUE;
	sound[5] = ATS_SOUND_CONTINUE;

	currentSpeed = vehicleState.Speed;
	currentTime = vehicleState.Time;
	currentZposition = vehicleState.Location;

	gsensor.calc(vehicleState);
	s_noice.main(vehicleState, panel, sound);
	evalute.main(vehicleState, panel, sound);
	result.main(vehicleState, panel, sound);

	panelOut(panel);
}
// ------------------------------------------------------------------
void DENGO::brakeState(int notch) {
	b_notch = notch;
	evalute.setNotchState(b_notch, p_notch);
}
// ------------------------------------------------------------------
void DENGO::powerState(int notch) { 
	p_notch = notch; 
	evalute.setNotchState(b_notch, p_notch);
}
// ------------------------------------------------------------------
void DENGO::keyDown(int keyCode) {
	if (keyCode == 0) {
		evalute.setKey(true);
		s_noice.setKey(true);
		result.setKey(true);
		return;
	}
}
// ------------------------------------------------------------------
void DENGO::keyUp(int keyCode) {
	if (keyCode == 0) {
		evalute.setKey(false);
		s_noice.setKey(false);
		result.setKey(false);
		return;
	}
}
// ------------------------------------------------------------------
void DENGO::doorState(bool state) { 
	doorOpen = state; 
	result.setDoorState(state);
	evalute.setDoorState(state);
	s_noice.setDoorState(state);
}
// ------------------------------------------------------------------
void DENGO::beaconData(ATS_BEACONDATA beaconData) {
	int beaconType = beaconData.Type;
	int sendData = beaconData.Optional;
	switch (beaconType) {
		case DGO_UPDATE:
			update = true;
			break;
		case DGO_SET_MISSION:
			station.setScenarioData(sendData);
			break;
		case DGO_SET_STATION:
			station.setNum(sendData);
			break;
		case DGO_SET_ARRIVETIME:
			station.setArriveTime(sendData);
			break;
		case DGO_SET_LEAVETIME:
			station.setLeaveTime(sendData);
			break;
		case DGO_SET_STOP_POSITION:
			station.setStopDistance(sendData);
			break;
		case DGO_SET_NOICE_SPEEDLIMIT:
			s_noice.setSpeedLimit(sendData);
			break;
		case DGO_SET_NOICE_CONSTANTSPEED:
			s_noice.setConstantSpeed(sendData);
			break;
		case DGO_SET_CURRENT_STATIOM:
			updateCurrentStation = sendData - 1;
			break;
		case DGO_SET_IN_STATION:
			evalute.setInStation(sendData);
			break;
		case  DGO_SET_HORN:
			evalute.setHornInfo(sendData);
			break;
		default:
			break;
	}
}
int DENGO::speedLimit() { return s_noice.getCurrentSpeedLimit(); }
// ------------------------------------------------------------------
void DENGO::emergencyBrake(int notch) { evalute.setEBnotch(notch); }
void DENGO::reverserState(int pos) { reverser = pos; }
void DENGO::hornBlow(int hornType) { evalute.setHornKey(hornType); }
// ------------------------------------------------------------------
void DENGO::panelOut(int* panel) {
	
	// --------------------------------------------------------------
	// 現在速度表示
	panel[0] = getDigitOfNumber((int)currentSpeed, 3, 10);
	panel[1] = getDigitOfNumber((int)currentSpeed, 2, 10);
	panel[2] = getDigitOfNumber((int)currentSpeed, 1,  0);
	// --------------------------------------------------------------
	// 制限速度表示
	int currentSpeedLimit = s_noice.getCurrentSpeedLimit();
	panel[3] = getDigitOfNumber(currentSpeedLimit, 3, 10);
	panel[4] = getDigitOfNumber(currentSpeedLimit, 2, 10);
	panel[5] = getDigitOfNumber(currentSpeedLimit, 1,  0);
	// --------------------------------------------------------------
	// 現在時刻表示
	if (target && !finalStop) {
		int time = currentTime / 1000;
		int time_h = time / 3600;
		int time_m = (time - time_h * 3600) / 60;
		int time_s = time % 60;
		panel[6] = time_h;
		panel[7] = time_m;
		panel[8] = time_s;
	} else {
		panel[6] = 25;
		panel[7] = 61;
		panel[8] = 61;
	}
	// --------------------------------------------------------------
	// レバーサー表示
	if (reverser == 0) {
		panel[9] = 0;
	} else if (reverser == 1) {
		panel[9] = 1;
	} else if(reverser == -1) {
		panel[9] = 2;
	}
	// --------------------------------------------------------------
	// ノッチ段表示
	panel[10] = b_notch;
	panel[11] = p_notch;
	// --------------------------------------------------------------
	// Gセンサー
	gsensor.dispGsensor(panel);
	// --------------------------------------------------------------
	// 残り時間
	remainningTime(panel);
	// --------------------------------------------------------------
	// 残距離
	remainningDistance(panel);

	// 更新処理
	if (update) updateInfo(panel);
}
// ------------------------------------------------------------------
// 残距離を計算する処理
void DENGO::remainningDistance(int* panel) {
	if (finalStop) {
		panel[34] = 30;
		panel[35] = 30;
		panel[36] = 30;
		panel[37] = 30;
		panel[38] = 4;
		panel[43] = 4;
		return;
	}

	int stopDistance = station.getStopDistance(nextStation);
	double remainningDistance = stopDistance - currentZposition;
	stationData s = station.getStationData(nextStation);
	bool isPass = station.isPass(s);
	int color = 0;
	double unit = 1.0;
	int over = 1;
	if (!isPass) {
		over = 0;
		if (abs(remainningDistance) < 10.0) {
			color = 10;
			if (remainningDistance > -5.0 && remainningDistance < 5.0) 
				unit = 1000.0;
		} else if (remainningDistance < -5) {
			color = 20;
		}
		if (remainningDistance < 0.0) over = 2;
	}
	result.setRemainnigDistance(remainningDistance*unit);
	panel[34] = getDigitOfNumber((int)(abs(remainningDistance)*unit), 4, 30)+color;
	panel[35] = getDigitOfNumber((int)(abs(remainningDistance)*unit), 3, 30)+color;
	panel[36] = getDigitOfNumber((int)(abs(remainningDistance)*unit), 2, 30)+color;
	panel[37] = getDigitOfNumber((int)(abs(remainningDistance)*unit), 1,  0)+color;
	panel[38] = over;
	panel[43] = (unit == 1) ? 0 : 1;
}
// ------------------------------------------------------------------
// 残り時間を計算する処理
void DENGO::remainningTime(int* panel) {
	if (finalStop) {
		panel[31] = 30;
		panel[32] = 30;
		panel[33] = 30;
		panel[39] = 30;
		return;
	}

	int remainningTime = 0;
	int color = 0;
	int over = 0;
	int mode = 0;

	if (mode == 0) {
		int arriveTime = station.getArriveTime(nextStopStation-1);
		// 12:34:56
		int h = arriveTime / 10000;
		int m = arriveTime / 100 % 100;
		int s = arriveTime % 100;
		remainningTime = (h * 60 * 60 + m * 60 + s) - (currentTime / 1000);
		color = 0;
		over = 0;
		if (abs(remainningTime) <= 10) {
			color = 10;
		} else if (remainningTime < -10) {
			color = 20;
		}
		if (remainningTime < 0) over = 2;
	}
	result.setRemainningTime(remainningTime);
	panel[31] = getDigitOfNumber(abs(remainningTime), 3, 30) + color;
	panel[32] = getDigitOfNumber(abs(remainningTime), 2, 30) + color;
	panel[33] = getDigitOfNumber(abs(remainningTime), 1,  0) + color;
	panel[39] = over;
}
// ------------------------------------------------------------------
// 指定桁の数字を返す
// 0の時rtを返す
int DENGO::getDigitOfNumber(int num, int digit, int rt) {
	int n = 0;
	for (int i = 0; i < 10; ++i) {
		if (num / pow(10, i) < 1) {
			n = i;
			break;
		}
	}
	if (digit > n) return rt;
	int result = (int)(num / pow(10, digit - 1)) % 10;
	if (digit >= n && result == 0) return rt;
	return result;
}
// ------------------------------------------------------------------
// 
void DENGO::updateInfo(int* panel) {
	int updateMode = 0;
	bool passed = station.isPass(updateCurrentStation);	// 現在駅を通過したか
	if (!passed && !doorOpen) {
		// 次駅停車駅のとき(停止位置-5mで受信)
		updateMode = 1;
		return;
	} else if (!passed && doorOpen) {
		// 停車駅に停車したとき(停止位置-5mで受信)
		updateMode = 2;
	} else if (passed) {
		// 通過駅を通過したとき(通過駅停止位置0mで受信)
		updateMode = 3;
	} else {
		update = false;
		return;
	}
	currentStation = updateCurrentStation;	// 自車現在駅を更新
	nextStation = currentStation + 1;		// 次駅を設定
	stationData nextStopData =				// 次駅停車駅を設定
		station.getNextStopStationData(currentStation);
	nextStopStation = station.getNum(nextStopData);		// 次駅駅番号
	finalStop = (nextStopStation < 0) ? true : false;	// 終着駅判定
	result.setStaNum(nextStopStation);
	if (finalStop) {
		// 走行区間表示
		panel[25] = 0;
		panel[26] = 0;
		// 目標停車駅
		panel[27] = 0;
		panel[28] = 0;
		panel[29] = 0;
		panel[30] = 0;
		// 目標停車駅
		panel[27] = 0;
		panel[28] = 25;
		panel[29] = 61;
		panel[30] = 61;
		panel[40] = 0;
		panel[41] = 0;
		return;
	}
	// --------------------------------------------------------------
	// シナリオ設定
	if (updateMode == 2) {
		panel[22] = station.getDifficulty(0);	// 運転難易度
		panel[23] = station.getRouteName(0);	// 路線名
		panel[24] = station.getMissionName(0);	// コメント
	}
	// --------------------------------------------------------------
	// 走行区間表示
	if (updateMode == 2) {
		panel[25] = station.getNum(currentStation);	// 発
		panel[26] = station.getNum(nextStopData);	// 着
	}
	// --------------------------------------------------------------
	// 目標停車駅
	stationData nextTargetStationData =
		station.getNextTargetStationData(currentStation);
	int nextTargetStatonArriveTime =
		station.getArriveTime(nextTargetStationData);
	target =
		(station.getStopDistance(nextTargetStationData) < 0) ? false : true;

	if (nextTargetStatonArriveTime > 0) {
		bool targetIsPass = station.isPass(nextTargetStationData);
		panel[27] = station.getNum(nextTargetStationData);	// 駅名
		panel[28] = nextTargetStatonArriveTime / 10000;		// hh
		panel[29] = nextTargetStatonArriveTime / 100 % 100;	// mm
		panel[30] = nextTargetStatonArriveTime % 100;		// ss
		panel[40] = 1;
		panel[41] = (targetIsPass) ? 2 : 1;
	} else {
		panel[27] = 0;
		panel[28] = 61;
		panel[29] = 61;
		panel[30] = 61;
		panel[40] = 0;
		panel[41] = 0;
	}
}
// ------------------------------------------------------------------
void DENGO::setGsensorLimit(int n) { gsensor.setUpper((double)n/10); }