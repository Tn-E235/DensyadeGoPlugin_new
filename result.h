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
	bool Gsenser;					// GZT[ç
	bool ebOver20;					// }§®(20km/hÅEB)
	bool ebStopping;				// ñíâÔ(EB)
	bool reAccelerateInForm;		// \àÄÁ¬
	bool brakeReload;				// u[Lß¼µ
};
struct scoringItems {
	bool pointingPilotLamp;			// ËÂw·«Ä
	bool accelerateAfterDoorClose;	// ËÂãÁ¬
	int pointingSpeed;				// ¬xvw·«Ä
	int keepSpeedLimit;				// §À¬xç
	int keepConstantSpeed;			// è¬Îß²ÝÄç
	int hornToWolker;				// ÛüìÆõÉxJ
	int hornToBridge;				// S´ÉxJ
	int hornToPassenger;			// z[æqÉxJ
	int reducedLight;				// ·êá¢Ô¼É¸õ
	bool Gsenser;					// GZT[ç
	bool ebOver20;					// }§®(20km/hÅEB)
	bool ebStopping;				// ñíâÔ(EB)
	bool reAccelerateInForm;		// \àÄÁ¬
	bool brakeReload;				// u[Lß¼µ
};
struct  scoringItemsCount {
	int pointingSpeed[2];			// ¬xvw·«Ä
	int keepSpeedLimit[2];			// §À¬xç
	int keepConstantSpeed[2];		// è¬Îß²ÝÄç
	int hornToWolker[2];			// ÛüìÆõÉxJ
	int hornToBridge[2];			// S´ÉxJ
	int hornToPassenger[2];			// z[æqÉxJ
	int reducedLight[2];			// ·êá¢Ô¼É¸õ
};
class RESULT {
	public:
		void init();
		void resetScoringItems();
		void resetScoringItemsCount(bool);
		void resetCheckedList();
		void main(ATS_VEHICLESTATE, int*, int*);
		void reset();
		void dispResult(int*);
		int calcScore();
		void setDoorState(bool);
		scoringItems* getScoringItemsPointer();
		scoringItemsCount* getScoringItemsCountPointer();
		checkedList* getCheckedListPointer();

	private:
		int score;
		int totalScore;
		bool doorOpen;
		bool reseted;
		struct scoringItems s_item;
		struct scoringItemsCount s_itemCount;
		struct checkedList cList;
		struct scoringItems* ps_item = &s_item;
		struct scoringItemsCount* ps_itemCount = &s_itemCount;
		struct checkedList* p_cList = &cList;
};

