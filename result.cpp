#include "stdafx.h"
#include "atsplugin.h"
#include "result.h"
// ------------------------------------------------------------------
void RESULT::init() {
	reset();
	score = -1;
	totalScore = 0;
	doorOpen = false;
	reseted = true;
	keyPush = true;
}
// ------------------------------------------------------------------
void RESULT::resetScoringItemsCount() {
	ps_itemCount->pointingPilotLamp = 0;		// 戸閉指差喚呼
	ps_itemCount->accelerateAfterDoorClose = 0;	// 戸閉後加速
	ps_itemCount->pointingSpeed = 0;			// 速度計指差喚呼
	ps_itemCount->keepSpeedLimit = 0;			// 制限速度遵守
	ps_itemCount->keepConstantSpeed = 0;		// 定速ﾎﾟｲﾝﾄ遵守
	ps_itemCount->hornTo = 0;					// 警笛
	ps_itemCount->reducedLight = 0;				// すれ違い車両に減光
	ps_itemCount->gSensor = 0;					// Gセンサー
	ps_itemCount->eBrake = 0;					// 非常ブレーキ
	ps_itemCount->reAccelerateInForm = 0;		// 構内再加速
	ps_itemCount->brakeReload = 0;				// ブレーキ込め直し
	ps_itemCount->speedOver = 0;				// 制限速度オーバー
}
// ------------------------------------------------------------------
void RESULT::resetCheckedList() {
	p_cList->pointingPilotLamp = false;			// 戸閉指差喚呼
	p_cList->accelerateAfterDoorClose = false;	// 戸閉後加速
	p_cList->pointingSpeed = false;				// 速度計指差喚呼
	p_cList->pointingConstant = false;			// 速度計指差喚呼
	p_cList->keepSpeedLimit = false;			// 制限速度遵守
	p_cList->keepConstantSpeed = false;			// 定速ﾎﾟｲﾝﾄ遵守
	p_cList->hornToWolker = false;				// 保線作業員に警笛
	p_cList->hornToBridge = false;				// 鉄橋に警笛
	p_cList->hornToPassenger = false;			// ホーム乗客に警笛
	p_cList->reducedLight = false;				// すれ違い車両に減光
	p_cList->Gsenser = false;					// Gセンサー作動
	p_cList->ebOver20 = false;					// 急制動(20km/hでEB)
	p_cList->ebStopping = false;				// 非常停車(EB)
	p_cList->reAccelerateInForm = false;		// 構内再加速
	p_cList->brakeReload = false;				// ブレーキ込め直し
	p_cList->overRun = false;					// オーバーラン
	p_cList->speedOver = false;					// 制限速度オーバー
}
// ------------------------------------------------------------------
void RESULT::main(ATS_VEHICLESTATE vehicleState, int* panel, int* sound) {
	if (doorOpen && !reseted) {
		score = calcScore();
		dispResult(panel);
		reset();
		reseted = true;
	} else if (!doorOpen) {
		reseted = false;
	}
	dispResult(keyPush, panel);
}
// ------------------------------------------------------------------
void RESULT::reset() {
	resetScoringItemsCount();
	resetCheckedList();
	score = 0;
}
// ------------------------------------------------------------------
void RESULT::dispResult(int* panel) {
	int unitDis = (remainningDistance <= 5.0) ? 1 : 0;
	int hugou = 0;
	if (abs(remainningDistance) >= 1000) {
		hugou = 3 + 3 * unitDis;
	} else if (abs(remainningDistance) >= 100) {
		hugou = 2 + 3 * unitDis;
	} else {
		hugou = 1 + 3 * unitDis;
	}
	panel[56] = 1;// リザルト画面
	panel[57] = unitDis;
	panel[58] = hugou;
	panel[59] = getDigitOfNumber(abs(remainningDistance), 4, 10);
	panel[60] = getDigitOfNumber(abs(remainningDistance), 3, 10);
	panel[61] = getDigitOfNumber(abs(remainningDistance), 2,  0);
	panel[62] = getDigitOfNumber(abs(remainningDistance), 1,  0);
	panel[63] = (remainningTime == 0) ? 1 : (remainningTime > 0) ? 2 : 3;
	panel[64] = getDigitOfNumber(abs(remainningTime), 3, 10);
	panel[65] = getDigitOfNumber(abs(remainningTime), 2, 10);
	panel[66] = getDigitOfNumber(abs(remainningTime), 1,  0);
	panel[67] = evaluteScore(1);
	panel[68] = evaluteScore(2);
	panel[69] = staNum;
	panel[85] = 0;
	panel[86] = (cList.reAccelerateInForm) ? 1 : 4;
	panel[87] = (cList.brakeReload) ? 1 : 4 ;
	panel[88] = (cList.Gsenser) ? 1 : 4;
	panel[89] = 0;

	totalScore += score;
	int out_s = (score < 0) ? 0 : score;
	int out_ts = (totalScore < 0) ? 0 : totalScore;

	panel[90] = getDigitOfNumber(out_s, 8, 10);
	panel[91] = getDigitOfNumber(out_s, 7, 10);
	panel[92] = getDigitOfNumber(out_s, 6, 10);
	panel[93] = getDigitOfNumber(out_s, 5, 10);
	panel[94] = getDigitOfNumber(out_s, 4, 10);
	panel[95] = getDigitOfNumber(out_s, 3, 10);
	panel[96] = getDigitOfNumber(out_s, 2, 10);
	panel[97] = getDigitOfNumber(out_s, 1,  0);
	panel[98] = getDigitOfNumber(out_ts, 8, 10);
	panel[99] = getDigitOfNumber(out_ts, 7, 10);
	panel[100] = getDigitOfNumber(out_ts, 6, 10);
	panel[101] = getDigitOfNumber(out_ts, 5, 10);
	panel[102] = getDigitOfNumber(out_ts, 4, 10);
	panel[103] = getDigitOfNumber(out_ts, 3, 10);
	panel[104] = getDigitOfNumber(out_ts, 2, 10);
	panel[105] = getDigitOfNumber(out_ts, 1,  0);
	panel[106] = 0;
	panel[107] = 0;
	panel[108] = 0;
	panel[109] = 0;
	panel[110] = 0;
	panel[111] = 0;
	panel[112] = 0;
	panel[113] = 0;
	panel[114] = 0;
	panel[115] = 0;
	panel[116] = 0;

}
// ------------------------------------------------------------------
void RESULT::dispResult(bool b, int* panel) {
	if (!b || !doorOpen) return;
	panel[56] = 0;// リザルト画面
	panel[57] = 2;
	panel[58] = 7;
	panel[59] = 10;
	panel[60] = 10;
	panel[61] = 10;
	panel[62] = 10;
	panel[63] = 0;
	panel[64] = 10;
	panel[65] = 10;
	panel[66] = 10;
	panel[67] = 0;
	panel[68] = 0;
	panel[69] = 0;
	panel[85] = 0;
	panel[86] = 0;
	panel[87] = 0;
	panel[88] = 0;
	panel[89] = 0;

	panel[90] = 10;
	panel[91] = 10;
	panel[92] = 10;
	panel[93] = 10;
	panel[94] = 10;
	panel[95] = 10;
	panel[96] = 10;
	panel[97] = 10;
	panel[98] = 10;
	panel[99] = 10;
	panel[100] = 10;
	panel[101] = 10;
	panel[102] = 10;
	panel[103] = 10;
	panel[104] = 10;
	panel[105] = 10;
	panel[106] = 0;
	panel[107] = 0;
	panel[108] = 0;
	panel[109] = 0;
	panel[110] = 0;
	panel[111] = 0;
	panel[112] = 0;
	panel[113] = 0;
	panel[114] = 0;
	panel[115] = 0;
	panel[116] = 0;
}
// ------------------------------------------------------------------
int RESULT::calcScore() {
	// 始発駅には変な値が入るためスコアに加算しない
	int subScore = 0;
	// 停止位置誤差評価(評価値)
	int distance = 
		(int)pow((3000.0-(double)abs(remainningDistance))/100.0, 3);
	if (distance < 0) distance = 0;
	// 停止時間誤差評価(評価値)
	int time = (int)pow(30.0 - (double)abs(remainningTime), 3);
	if (time < 0) time = 0;
	// 指差喚呼評価(評価値)
	int pointing = ps_itemCount->pointingPilotLamp;
		pointing += ps_itemCount->accelerateAfterDoorClose;
		pointing += ps_itemCount->pointingSpeed;
	// 制限速度評価(評価値)
	int speedLimit = ps_itemCount->keepSpeedLimit;
		speedLimit += ps_itemCount->keepConstantSpeed;
	// 警笛評価(評価値)
	int horn = ps_itemCount->hornTo;
	// Gセンサー評価(回数)
	int gsensor = ps_itemCount->gSensor * -2500;
	// 非常ブレーキ評価(回数)
	int eBrake = ps_itemCount->eBrake * -1000;
	// 構内再加速の評価(T/F)
	int reAcc = (p_cList->reAccelerateInForm) ? -5000 : 0;
	// ブレーキ込め直し評価(T/F)
	int breakReload = (p_cList->brakeReload) ? -2500 : 0;
	// オーバーラン判定(T/F)
	int overRun = (p_cList->overRun) ? -10000 : 0;
	if (p_cList->overRun) distance = 0;
	
	subScore =
		distance + 
		time + 
		pointing + 
		speedLimit +
		horn + 
		gsensor + 
		eBrake + 
		reAcc + 
		breakReload + 
		overRun;

	return 	(subScore > 0) ? subScore : 0 ;
}
// ------------------------------------------------------------------
int RESULT::evaluteScore(int n) {
	if (n == 1) {
		// 停止位置判定
		if (abs(remainningDistance) > 5000) {
			return 5;
		} else if (abs(remainningDistance) > 3000) {
			return 4;
		} else if (abs(remainningDistance) > 1500) {
			return 3;
		} else if (abs(remainningDistance) > 350) {
			return 2;
		} else {
			return 1;
		}
	}
	if (n == 2) {
		// 停止時間判定
		if (abs(remainningTime) > 20) {
			return 5;
		}
		else if (abs(remainningTime) > 15) {
			return 4;
		}
		else if (abs(remainningTime) > 10) {
			return 3;
		}
		else if (abs(remainningTime) > 5) {
			return 2;
		}
		else {
			return 1;
		}
	}
	return 0;
}
// ------------------------------------------------------------------
void RESULT::setDoorState(bool b) { doorOpen = b; }
int RESULT::getDigitOfNumber(int num, int digit, int rt) {
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
scoringItemsCount* RESULT::getScoringItemsCountPointer() { return ps_itemCount; }
checkedList* RESULT::getCheckedListPointer() { return p_cList; }
void RESULT::setRemainnigDistance(int dis) { remainningDistance = dis; }
void RESULT::setRemainningTime(int time) { remainningTime = time; }
void RESULT::setStaNum(int num) { staNum = num; }
void RESULT::setKey(bool b) { keyPush = b; }
// ------------------------------------------------------------------