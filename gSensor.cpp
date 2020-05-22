#include "stdafx.h"
#include "atsplugin.h"
#include "result.h"
#include "gSensor.h"
#include <cmath>
void G_SENSOR::calc(ATS_VEHICLESTATE vehicleState) {
	double Gp = 0.0;
	double g_value_b = g_value;

	double gSum = 0.0;
	int gTime = 0;
	int dT = 0;

	for (int i = 9; i > 0; --i) {
		d_acceleration[i] = d_acceleration[i - 1];
		acceleration[i] = acceleration[i - 1];
		deltaTime[i] = deltaTime[i - 1];
		gSum += d_acceleration[i];
	}
	acceleration[0] = vehicleState.Speed;
	deltaTime[0] = vehicleState.Time;
	d_acceleration[0] =
		(float)abs((acceleration[1] - acceleration[0]) / (deltaTime[1] - deltaTime[0]));
	gSum += d_acceleration[0];
	Gp = 1 + ((gSum - b_gSum) / b_gSum)
		+ 5 * (double)((160 - vehicleState.Speed) / 1000);
	g_value = (325 * (gSum * Gp * 10000 / 10)) / (g_max * 10);
	if ((int)g_value > 325) {
		g_over = true;
	} else {
		g_over = false;
	}
	b_gSum = gSum;
}
void G_SENSOR::setUpper(double d) { g_max = d; }
int G_SENSOR::getValue() { return (g_over) ? -1 : (int)g_value; }
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
		if ((int)g_value >= 31 * (i + 1)) {
			panel[i+offset] = 31;
		} else {
			panel[i+offset] = (int)g_value - (31 * i);
			for (int j = i; j < 11; ++j) 
				panel[j+offset] = 40;
			return;
		}
	}
}