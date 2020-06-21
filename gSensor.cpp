#include "stdafx.h"
#include "atsplugin.h"
#include "result.h"
#include "evaluate.h"
#include "gSensor.h"
#include <cmath>

void G_SENSOR::init() { 
	g_value = 0.0;
	g_over = false;
	for (int i = 0; i < G_ARRAY; ++i) {
		v_deltaTime[i] = 0;
		v_speed[i] = 0.0;
		v_time[i] = 0;
		v_gValue[i] = 0.0;
	}
}
// ------------------------------------------------------------------
void G_SENSOR::calc(ATS_VEHICLESTATE vehicleState) {
	delta_T = vehicleState.Time - currentTime;
	currentTime = vehicleState.Time;
	double currentSpeed = (double)vehicleState.Speed;
	double g_sum = 0.0;
	double acc_sum = 0.0;

	// 要素削除
	for (int i = G_ARRAY - 1; i > 0; --i) {
		v_time[i] = v_time[i - 1];
		v_deltaTime[i] = v_deltaTime[i - 1];
		v_speed[i] = v_speed[i - 1];
		v_acceleration[i] = v_acceleration[i - 1];
		v_gValue[i] = v_gValue[i - 1];
		g_sum += v_gValue[i];
		acc_sum += v_acceleration[i];
	}

	// 加速度計算
	double acc = abs((currentSpeed - v_speed[0]) / (double)(currentTime - v_time[0]));// ★

	// 現在の情報入力
	v_deltaTime[0] = delta_T;	// 前ステップとの時間差
	v_speed[0] = currentSpeed;	// 現在ステップの速度
	v_time[0] = currentTime;	// 現在時刻
	v_acceleration[0] = acc;	// 加速度
	// --------------------------------------------------------------
	if (!enable) {
		g_value = 0;
	} else if (mode == 1) {
		acc_sum += acc;
		double acc_avg = acc_sum / (double)G_ARRAY;
		double g_sum_avg = g_sum / (double)G_ARRAY-1.0;
		double Gp = 1.0 + ((acc_avg - g_sum_avg) / g_sum_avg)
			+ 5.0 * (double)((160.0 - currentSpeed) / 10.0);
		g_value = 325.0 * acc_avg * Gp / g_max;
		v_gValue[0] = g_value;
	} else if (mode == 2) {
		acc_sum += acc;
		// 加速度の変化率
		// double rate = abs((v_acceleration[0] - v_acceleration[29]) / v_acceleration[29]);// ★
		// double rate = abs((acc - acc_sum / (double)G_ARRAY) / (acc_sum / (double)G_ARRAY));// ★
		// double rate = abs((acc + acc_sum) / (double)G_ARRAY)*100.0;// ★

		// 加速度の差
		double rate = abs((acc - acc_sum / (double)G_ARRAY))*10000.0;// ★

		// 出力値
		g_value = 325.0 * rate / g_max;
		v_gValue[0] = g_value;	

		g_value = (g_sum + g_value) / (double)G_ARRAY;
	} else {
		g_value = 0;
	}
	// --------------------------------------------------------------
	// 共通
	if (g_value > 325) { 
		if (!g_over) { 
			p_s_itemCount->gSensor++;
			p_cList->Gsenser = true;
			evalute.setDisp(p_box, 10, 0);
		}
		g_over = true;
	} else {
		g_over = false;
	}
}
// ------------------------------------------------------------------
void G_SENSOR::dispGsensor(int* panel) {
	int offset = 44;
	if ((int)g_value >= 325) {
		panel[55] = 1;
		for (int i = 0; i < 11; ++i)
			panel[i+offset] = 40;
		return;
	}
	panel[55] = 0;
	for (int i = 0; i < 11; ++i) {
		if ((int)g_value >= 32 * (i + 1)) {
			panel[i+offset] = 31;
		} else {
			panel[i+offset] = (int)g_value - (32 * i);
			for (int j = i+1; j < 11; ++j) 
				panel[j+offset] = 40;
			return;
		}
	}
}
// ------------------------------------------------------------------
void G_SENSOR::setEnable(int i) { enable = (i == 1) ? true : false; } 
void G_SENSOR::setMode(int i) { mode = i; }
void G_SENSOR::setUpper(double d) { g_max = d; }
int G_SENSOR::getValue() { return (g_over) ? -1 : (int)g_value; }
void G_SENSOR::setScoringItemsCountPointer(scoringItemsCount* p) { p_s_itemCount = p; }
void G_SENSOR::setChechedListPointer(checkedList* p) { p_cList = p; }
void G_SENSOR::setBoxPointer(dispEvalute* p) { p_box = p; }
