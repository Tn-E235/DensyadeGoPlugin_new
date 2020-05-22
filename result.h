#pragma once
struct checkedList {
	bool pointingPilotLamp;			// 戸閉指差喚呼
	bool accelerateAfterDoorClose;	// 戸閉後加速
	bool pointingSpeed;				// 速度計指差喚呼
	bool pointingConstant;			// 速度計指差喚呼
	bool keepSpeedLimit;			// 制限速度遵守
	bool keepConstantSpeed;			// 定速ﾎﾟｲﾝﾄ遵守
	bool hornToWolker;				// 保線作業員に警笛
	bool hornToBridge;				// 鉄橋に警笛
	bool hornToPassenger;			// ホーム乗客に警笛
	bool reducedLight;				// すれ違い車両に減光
	bool Gsenser;					// Gセンサー遵守
	bool ebOver20;					// 急制動(20km/hでEB)
	bool ebStopping;				// 非常停車(EB)
	bool reAccelerateInForm;		// 構内再加速
	bool brakeReload;				// ブレーキ込め直し
};
struct scoringItems {
	bool pointingPilotLamp;			// 戸閉指差喚呼
	bool accelerateAfterDoorClose;	// 戸閉後加速
	int pointingSpeed;				// 速度計指差喚呼
	int keepSpeedLimit;				// 制限速度遵守
	int keepConstantSpeed;			// 定速ﾎﾟｲﾝﾄ遵守
	int hornToWolker;				// 保線作業員に警笛
	int hornToBridge;				// 鉄橋に警笛
	int hornToPassenger;			// ホーム乗客に警笛
	int reducedLight;				// すれ違い車両に減光
	bool Gsenser;					// Gセンサー遵守
	bool ebOver20;					// 急制動(20km/hでEB)
	bool ebStopping;				// 非常停車(EB)
	bool reAccelerateInForm;		// 構内再加速
	bool brakeReload;				// ブレーキ込め直し
};
struct  scoringItemsCount {
	int pointingSpeed[2];			// 速度計指差喚呼
	int keepSpeedLimit[2];			// 制限速度遵守
	int keepConstantSpeed[2];		// 定速ﾎﾟｲﾝﾄ遵守
	int hornToWolker[2];			// 保線作業員に警笛
	int hornToBridge[2];			// 鉄橋に警笛
	int hornToPassenger[2];			// ホーム乗客に警笛
	int reducedLight[2];			// すれ違い車両に減光
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

