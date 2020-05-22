#pragma once
struct speedNoice {
	bool scoring;
	int speed;
	int distance;
	double noicePoint;
};
class SPEED_NOICE {
	public:
		void init();
		void main(ATS_VEHICLESTATE, int*, int*);
		void setSpeedLimit(int);
		void setConstantSpeed(int);
		void setBoxPointer(dispEvalute*);
		int getSpeedLimit();
		int getCurrentSpeedLimit();
		int getDigitOfNumber(int num, int digit, int rt);

	private:
		int speedLimit;
		int currentSpeedLimit;
		int constantSpeed;
		int currentConstantSpeed;

		speedNoice sLimit;
		speedNoice cLimit;
		EVALUTE evalute;
		struct dispEvalute *p_box = nullptr;
};

