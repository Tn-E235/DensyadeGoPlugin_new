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

		void setKey(bool);
		void setDoorState(bool);
		int getStar(int, double);
		void setChechedListPointer(checkedList*);
		void setScoringItemsCountPointer(scoringItemsCount*);
	private:
		int speedLimit;
		int currentSpeedLimit;
		int constantSpeed;
		int currentConstantSpeed;
		bool keyPush;
		bool doorOpen;
		speedNoice sLimit = { false,0,0,false };
		speedNoice cLimit = { false,0,0,false };
		EVALUTE evalute;
		struct dispEvalute* p_box = nullptr;
		struct checkedList* p_cList = nullptr;
		struct scoringItemsCount* p_s_itemCount = nullptr;
};

