#pragma once
struct checkedList {
	bool pointingPilotLamp;			// ËÂw·«Ä
	bool accelerateAfterDoorClose;	// ËÂãÁ¬
	bool pointingSpeed;				// ¬xvw·«Ä
	bool pointingConstant;			// ¬xvw·«Ä
	bool keepSpeedLimit;			// §À¬xç
	bool keepConstantSpeed;			// è¬Îß²ÝÄç
	bool hornToWolker;				// ÛüìÆõÉxJ
	bool hornToBridge;				// S´ÉxJ
	bool hornToPassenger;			// z[æqÉxJ
	bool reducedLight;				// ·êá¢Ô¼É¸õ
	bool Gsenser;					// GZT[ì®
	bool ebOver20;					// }§®(20km/hÅEB)
	bool ebStopping;				// ñíâÔ(EB)
	bool reAccelerateInForm;		// \àÄÁ¬
	bool brakeReload;				// u[Lß¼µ
	bool overRun;					// I[o[
	bool speedOver;
};
// XRA
struct  scoringItemsCount {
	int pointingPilotLamp;			// ËÂw·«Ä
	int accelerateAfterDoorClose;	// ËÂãÁ¬
	int pointingSpeed;				// ¬xvw·«Ä
	int keepSpeedLimit;				// §À¬xç
	int keepConstantSpeed;			// è¬Îß²ÝÄç
	int hornTo;						// xJ
	int reducedLight;				// ·êá¢Ô¼É¸õ
	int gSensor;					// GZT[
	int eBrake;						// ñíu[L
	bool reAccelerateInForm;		// \àÄÁ¬
	bool brakeReload;				// u[Lß¼µ
	int speedOver;
};
class RESULT {
	public:
		void init();
		void resetScoringItemsCount();
		void resetCheckedList();
		void main(ATS_VEHICLESTATE, int*, int*);
		void reset();
		void dispResult(int*);
		void dispResult(bool,int*);
		int calcScore();
		int evaluteScore(int);
		void setKey(bool);
		void setDoorState(bool);
		void setRemainnigDistance(int);
		void setRemainningTime(int);
		void setStaNum(int);
		int getDigitOfNumber(int, int, int);
		scoringItemsCount* getScoringItemsCountPointer();
		checkedList* getCheckedListPointer();

	private:
		int score;
		int totalScore;
		bool doorOpen;
		bool reseted;
		int remainningDistance;
		int remainningTime;
		int staNum;
		bool keyPush;
		struct scoringItemsCount s_itemCount;
		struct checkedList cList;
		struct scoringItemsCount* ps_itemCount = &s_itemCount;
		struct checkedList* p_cList = &cList;
};

