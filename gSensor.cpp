#include "stdafx.h"
#include "atsplugin.h"
#include "result.h"
#include "evaluate.h"
#include "gSensor.h"
#include <cmath>
// ------------------------------------------------------------------
void G_SENSOR::calc(ATS_VEHICLESTATE vehicleState) {
	double Gp = 0.0;
	double gValue_b = g_value;	// 前回の値保持
	// 加速度計算
	double gSum = 0.0;
	int gTime = 0;
	int dT = 0;

	for (int i = 9; i > 0; --i) {
		d_acceleration[i] = d_acceleration[i - 1];
		acceleration[i] = acceleration[i - 1];
		deltaTime[i] = deltaTime[i - 1];
		gSum += d_acceleration[i];
	}
	acceleration[0] = (double)vehicleState.Speed;
	deltaTime[0] = vehicleState.Time;
	d_acceleration[0] = 
		abs((acceleration[1] - acceleration[0]) / (double)(deltaTime[1] - deltaTime[0]));
	gSum += d_acceleration[0];
	Gp = 1.0 + ((gSum - b_gSum) / b_gSum)
		+ 5.0 * (double)((160.0 - acceleration[0]) / 1000.0);
	g_value = 325.0 * gSum * Gp * 100.0 / g_max;
	if (g_value > 325) { 
		if (!g_over) { 
			if (acceleration[0] >= 0.5) {
				p_s_itemCount->gSensor++;
				p_cList->Gsenser = true;
				evalute.setDisp(p_box, 10, 0);
			}
		}
		g_over = true;
	} else {
		g_over = false;
	}
	b_gSum = gSum;
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
void G_SENSOR::setUpper(double d) { g_max = d; }
int G_SENSOR::getValue() { return (g_over) ? -1 : (int)g_value; }
void G_SENSOR::setScoringItemsCountPointer(scoringItemsCount* p) { p_s_itemCount = p; }
void G_SENSOR::setChechedListPointer(checkedList* p) { p_cList = p; }
void G_SENSOR::setBoxPointer(dispEvalute* p) { p_box = p; }
