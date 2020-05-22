#pragma once
class G_SENSOR {
private:
	int value = 0;
	float acceleration[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int deltaTime[10] = { 0,0,0,0,0,0,0,0,0,0 };
	float d_acceleration[10] = { 0,0,0,0,0,0,0,0,0,0 };
	double b_gSum = 0;
	double g_max = 5.0;
	double g_value = 0;
	bool g_over = false;
public:
	void calc(ATS_VEHICLESTATE);
	void setUpper(double);
	int getValue();

	void dispGsensor(int*);
};
