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
	bool Gsenser;					// Gセンサー作動
	bool ebOver20;					// 急制動(20km/hでEB)
	bool ebStopping;				// 非常停車(EB)
	bool reAccelerateInForm;		// 構内再加速
	bool brakeReload;				// ブレーキ込め直し
	bool overRun;					// オーバーラン
	bool speedOver;					// 制限速度オーバー
};
// スコア
struct  scoringItemsCount {
	int pointingPilotLamp;			// 戸閉指差喚呼
	int accelerateAfterDoorClose;	// 戸閉後加速
	int pointingSpeed;				// 速度計指差喚呼
	int keepSpeedLimit;				// 制限速度遵守
	int keepConstantSpeed;			// 定速ﾎﾟｲﾝﾄ遵守
	int hornTo;						// 警笛
	int reducedLight;				// すれ違い車両に減光
	int gSensor;					// Gセンサー
	int eBrake;						// 非常ブレーキ
	bool reAccelerateInForm;		// 構内再加速
	bool brakeReload;				// ブレーキ込め直し
	int speedOver;					// 制限速度オーバー
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

