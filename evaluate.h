#pragma once
struct horn {
	bool enable;
	int distance;
	double noicePoint;
};
struct dispEvalute {
	int idx;		// 出力するパネルIdx
	int totalTime;	// 表示した時間
	int score;		// 表示するスコア
};
class EVALUTE {
	public:
		void init();
		void init(int);
		void init(dispEvalute*, int);
		void main(ATS_VEHICLESTATE, int*, int*);
		void setDisp(int, int);
		void setDisp(dispEvalute*, int, int);
		void updateInfo();
		void pushup();
		void pushup(dispEvalute*);
		void disp(int*);
		void reset();

		void pointingPilotLamp(int*);
		void acclerateAfterDoorClose(int*);
		void hornTo(int*);
		// void reducedLight(int*);
		void emergencyBrake(int*);
		void reAccelerateInForm(int*);
		void brakeReload(int*);

		void setKey(bool);
		void setHornKey(int);
		void setDoorState(bool);
		void setNotchState(int, int);
		void setEBnotch(int);
		void setLastStopDistance(int);
		void setHornInfo(int);
		bool isStopPosition();
		void setInStation(int);
		int getStar(int, double);

		void setScoringItemsCountPointer(scoringItemsCount*);
		void setChechedListPointer(checkedList*);

		int getDigitOfNumber(int,int,int);
		
		dispEvalute* getBoxPointer();
	private:
		int delta_T = 0;
		int currentTime = 0;
		int beforeTime;
		int currentSpeed;
		double lastStopDistance;
		double currentDistance;
		int p_notch;
		int b_notch;
		int b_b_notch;
		int ebNotch;
		int maxBnotchInStation;
		int maxPnotchInStation;
		bool isEB;
		bool doorOpen;
		bool keyPush;
		bool hornKey;
		int hornDuration;
		int brakeDuration;
		bool inStation;
		const int offset = 5;

		struct dispEvalute box[5] = {
			{0,0,0},
			{0,0,0},
			{0,0,0},
			{0,0,0},
			{0,0,0}
		};
		struct horn hornInfo[3];
		struct dispEvalute *p = box;
		struct scoringItemsCount* p_s_itemCount = nullptr;
		struct checkedList* p_cList = nullptr;
};

