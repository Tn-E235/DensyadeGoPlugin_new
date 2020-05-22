#pragma once
struct stationData {
	int num;			// �w�ԍ�
	int arriveTime;		// ��������
	int leaveTime;		// �o������
	int stopDistance;	// ��~�ʒu(������)
	bool isPass;		// �ʉߔ���
	bool isTarget;		// 
};
struct scenarioData {
	int difficulty;
	int routeName;
	int missionName;
};
class STATION_DB {
	public:
		void init();
		void setNum(int);
		void setArriveTime(int);
		void setLeaveTime(int);
		void setStopDistance(int);
		void setNextStation(int);
		void setNextStopStation(int);

		int getNum(stationData);
		int getArriveTime(stationData);
		int getLeaveTime(stationData);
		int getStopDistance(stationData);
		bool isPass(stationData);
		bool isTarget(stationData);

		int getNum(int);
		int getArriveTime(int);
		int getLeaveTime(int);
		int getStopDistance(int);
		bool isPass(int);
		bool isTarget(int);

		stationData* getStationDataPointer();

		stationData getStationData(int);
		stationData getNextStopStationData(int);
		stationData getNextTargetStationData(int);

		void setScenarioData(int);
		int getDifficulty(int);
		int getRouteName(int);
		int getMissionName(int);
	private:
		int nextStation[2] = { 0,0 };
		int nextStopStation[2] = { 0,0 };
		int leaveStationName = 0;

		struct stationData s_data[100];
		struct scenarioData sc_data[100];
		struct stationData *p = s_data;
};

