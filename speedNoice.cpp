#include "stdafx.h"
#include "atsplugin.h"
#include "result.h"
#include "evaluate.h"
#include "speedNoice.h"
#include <cmath>
// ------------------------------------------------------------------
void SPEED_NOICE::init() {
	speedLimit = 0;
	currentSpeedLimit = sLimit.speed;
	sLimit.scoring = false;
	sLimit.distance = 0;
	sLimit.speed = 0;
	sLimit.noicePoint = -1.0;
	cLimit.scoring = false;
	cLimit.distance = 0;
	cLimit.speed = 0;
	cLimit.noicePoint = -1.0;
	doorOpen = false;
}
// ------------------------------------------------------------------
void SPEED_NOICE::main(ATS_VEHICLESTATE vehicleState, int* panel, int* sound) {
	float currentSpeed = vehicleState.Speed;
	double currentLocation = vehicleState.Location;
	if (doorOpen) {
		sLimit.scoring = false;
		sLimit.distance = 0;
		sLimit.speed = 0;
		sLimit.noicePoint = -1.0;
		cLimit.scoring = false;
		cLimit.distance = 0;
		cLimit.speed = 0;
		cLimit.noicePoint = -1.0;

		panel[12] = 10;
		panel[13] = 10;
		panel[14] = 10;
		panel[18] = 0;
		panel[20] = 0;

		panel[15] = 10;
		panel[16] = 10;
		panel[17] = 10;
		panel[19] = 0;
		panel[21] = 0;
	}
	// if (currentSpeed == 0.0) return;
	// --------------------------------------------------------------
	// 制限速度
	bool limitEnd = false;
	if (sLimit.speed > 0) {
		if (sLimit.distance < 1) limitEnd = true;
		if (sLimit.noicePoint < 0.0) sLimit.noicePoint = currentLocation; 
		double remainningDistance = 
			currentLocation - (sLimit.noicePoint + sLimit.distance);
		if (remainningDistance >= 0.0) {
			limitEnd = true;
		} else {
			double  value = abs(remainningDistance) / sLimit.distance;
			int idx = (int)(200.0 - 200.0 * value + 1.0);
			limitEnd = false;
			panel[12] = getDigitOfNumber(sLimit.speed, 3, 10);
			panel[13] = getDigitOfNumber(sLimit.speed, 2, 10);
			panel[14] = getDigitOfNumber(sLimit.speed, 1,  0);
			panel[18] = 1;
			panel[20] = idx;	// 制限速度バー
			if (keyPush && !p_cList->pointingSpeed) {
				p_cList->pointingSpeed = true;
				int star = 
					getStar(sLimit.distance, sLimit.distance - abs(remainningDistance));
				evalute.setDisp(p_box, 3, star);
				p_s_itemCount->pointingSpeed += star * 100;
				sound[0] = ATS_SOUND_PLAY;
			}
		}
		if (limitEnd) {
			panel[12] = 10;
			panel[13] = 10;
			panel[14] = 10;
			panel[18] = 0;
			panel[20] = 0;
			if (sLimit.speed + 1 > (int)currentSpeed && !doorOpen) {
				evalute.setDisp(p_box, 4, 3);
				p_s_itemCount->keepSpeedLimit += 300;
				sound[2] = ATS_SOUND_PLAY;
			} else {
				p_s_itemCount->keepSpeedLimit -= 300;
				evalute.setDisp(p_box,4, 0);
			}
			currentSpeedLimit = sLimit.speed;
			sLimit.scoring = false;
			sLimit.distance = 0;
			sLimit.speed = 0;
			sLimit.noicePoint = -1.0;
			if (p_cList->pointingSpeed == false) evalute.setDisp(p_box, 3, 0);
			p_cList->pointingSpeed = false;
		}
	}
	limitEnd = false;
	// --------------------------------------------------------------
	// 定速速度
	if (cLimit.speed > 0) {
		if (cLimit.noicePoint < 0.0) cLimit.noicePoint = currentLocation;
		double remainningDistance = 
			currentLocation - (cLimit.noicePoint + cLimit.distance);
		if (remainningDistance >= 0.0) {
			limitEnd = true;
		} else {
			double value = abs(remainningDistance) / cLimit.distance;
			int idx = (int)(200.0 - 200.0 * value + 1.0);
			limitEnd = false;
			panel[15] = getDigitOfNumber(cLimit.speed, 3, 10);
			panel[16] = getDigitOfNumber(cLimit.speed, 2, 10);
			panel[17] = getDigitOfNumber(cLimit.speed, 1, 0);
			panel[19] = 1;
			panel[21] = idx;	// 制限速度バー
			if (keyPush && !p_cList->pointingConstant) {
				p_cList->pointingConstant = true;
				int star =
					getStar(cLimit.distance, cLimit.distance - abs(remainningDistance));
				evalute.setDisp(p_box, 3, star);
				p_s_itemCount->pointingSpeed += star * 100;
				sound[0] = ATS_SOUND_PLAY;
			}
		}
		if (limitEnd) {
			panel[15] = 10;
			panel[16] = 10;
			panel[17] = 10;
			panel[19] = 0;
			panel[21] = 0;
			double tolerance = abs((int)currentSpeed - cLimit.speed);
			if (tolerance < 2) {
				sound[2] = ATS_SOUND_PLAY;
				p_s_itemCount->keepConstantSpeed += 300;
				evalute.setDisp(p_box, 5, 3);
			} else if (tolerance < 6) {
				sound[3] = ATS_SOUND_PLAY;
				p_s_itemCount->keepConstantSpeed += 200;
				evalute.setDisp(p_box, 5, 2);
			} else if (tolerance < 11) {
				sound[4] = ATS_SOUND_PLAY;
				p_s_itemCount->keepConstantSpeed += 100;
				evalute.setDisp(p_box, 5, 1);
			} else {
				evalute.setDisp(p_box, 5, 0);
			}
			// 制限速度更新
			currentConstantSpeed = cLimit.speed;
			constantSpeed = 0;
			cLimit.scoring = false;
			cLimit.distance = 0;
			cLimit.speed = 0;
			cLimit.noicePoint = -1.0;
			if (p_cList->pointingConstant == false) evalute.setDisp(p_box, 3, 0);
			p_cList->pointingConstant = false;
		}
	}
}
// ------------------------------------------------------------------
void SPEED_NOICE::setSpeedLimit(int sendData) {
	sLimit.scoring = (sendData / 1000000 > 0) ? true : false;
	sLimit.distance = sendData / 1000 % 1000;
	sLimit.speed = sendData % 1000;
	sLimit.noicePoint = -1.0;
	speedLimit = sLimit.speed;
}
// ------------------------------------------------------------------
void SPEED_NOICE::setConstantSpeed(int sendData) {
	cLimit.scoring = (sendData / 1000000 > 0) ? true : false;
	cLimit.distance = sendData / 1000 % 1000;
	cLimit.speed = sendData % 1000;
	cLimit.noicePoint = -1.0;
	constantSpeed = cLimit.speed;
}
// ------------------------------------------------------------------
int SPEED_NOICE::getStar(int i, double d) {
	double val = d / i;
	if (val > 1.0 / 3.0 * 2.0) {
		return 1;
	} else if (val > 1.0 / 3.0) {
		return 2;
	} else {
		return 3;
	}
	return 0;
}
// ------------------------------------------------------------------
// 構造体ポインタ取得
void SPEED_NOICE::setBoxPointer(dispEvalute *p) { p_box = p; }
int SPEED_NOICE::getSpeedLimit() { return speedLimit; }
int SPEED_NOICE::getCurrentSpeedLimit() { return currentSpeedLimit; }
void SPEED_NOICE::setKey(bool b) { keyPush = b; }
void SPEED_NOICE::setDoorState(bool b) { doorOpen = b; }
void SPEED_NOICE::setChechedListPointer(checkedList* p) { p_cList = p; }
void SPEED_NOICE::setScoringItemsCountPointer(scoringItemsCount* p) { p_s_itemCount = p; }
// ------------------------------------------------------------------
// 指定桁の数字を返す
// 0の時rtを返す
int SPEED_NOICE::getDigitOfNumber(int num, int digit, int rt) {
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