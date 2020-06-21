#pragma once
#define DGO_UPDATE 300
#define DGO_SET_MISSION 301
#define DGO_SET_STATION 302
#define DGO_SET_ARRIVETIME 303
#define DGO_SET_LEAVETIME 304
#define DGO_SET_STOP_POSITION 305
#define DGO_SET_NOICE_SPEEDLIMIT 306
#define DGO_SET_NOICE_CONSTANTSPEED 307

#define DGO_SET_CURRENT_STATIOM 311
#define DGO_SET_IN_STATION 312
#define DGO_SET_HORN 313

class DENGO{
	public:
		void init();
		void main(ATS_VEHICLESTATE, int*, int*);
		void brakeState(int);
		void powerState(int);
		void emergencyBrake(int);
		void reverserState(int);
		void keyDown(int);
		void keyUp(int);
		void hornBlow(int);
		void doorState(bool);
		void beaconData(ATS_BEACONDATA);
		int speedLimit();
		int getDigitOfNumber(int, int, int);
		void setGsensorEnable(int);
		void setGsensorLimit(int);
		void setGsensorMode(int);
	private:
		void panelOut(int*);
		void remainningDistance(int*);
		void remainningTime(int*);
		void updateInfo(int*);

		bool doorOpen;				// ドア状態
		int b_notch;				// Bレーキノッチ
		int p_notch;				// Pノッチ
		int reverser;				// レバーサー
		float currentSpeed;			// 現在速度
		int currentTime;			// 現在時刻
		double currentZposition;	// 現在位置(z座標)
		int updateCurrentStation;	// 次駅駅番号
		bool target;				// 目標到着/通過駅
		int currentStation;	// 現在停車中/通過/発車した駅 -> 地上子で即時更新
		int nextStopStation;// 次駅停車駅 -> 更新後DBから停車駅を参照
		int nextStation;	// 次駅(通過/停車) -> 現在駅の次駅を参照
		bool update;		// 更新判定 -> 300番地上子
		bool finalStop;		// 終着駅判定 -> 次駅到着駅がないとき終着駅判定

		G_SENSOR gsensor;
		STATION_DB station;
		SPEED_NOICE s_noice;
		EVALUTE evalute;
		RESULT result;

		struct stationData* p_station = nullptr;
		struct scenarioData* p_scenario = nullptr;
		struct speedNoice* p_s_noice = nullptr;
		struct dispEvalute* p_box = nullptr;
		struct scoringItems* p_s_items = nullptr;
		struct scoringItemsCount* p_s_itemsCount = nullptr;
		struct checkedList* p_cList = nullptr;
};

