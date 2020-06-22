#include "stdafx.h"
#include "stationDB.h"

void STATION_DB::init() {
	for (int i = 0; i < 100; ++i) {
		s_data[i].num = -1;
		s_data[i].arriveTime = 0;
		s_data[i].leaveTime = 0;
		s_data[i].stopDistance = -1;
		s_data[i].isPass = false;
		s_data[i].isTarget = false;
	}
}

void STATION_DB::setNum(int sendData) {
	//                  01010203
	int idx = sendData / 1000000;
	if (idx < 1) return;
	s_data[idx - 1].num = sendData / 10000 % 100;
	s_data[idx - 1].isPass = (sendData / 100 % 100 > 0) ? true : false;
	s_data[idx - 1].isTarget = (sendData % 100 > 0) ? true : false;
}

void STATION_DB::setArriveTime(int sendData) {
	//                  01123456
	int idx = sendData / 1000000;
	if (idx < 1) return;
	s_data[idx - 1].arriveTime = sendData % 1000000;
}

void STATION_DB::setLeaveTime(int sendData) {
	int idx = sendData / 1000000;
	if (idx < 1) return;
	s_data[idx - 1].leaveTime = sendData % 1000000;
}

void STATION_DB::setStopDistance(int sendData) {
	int idx = sendData / 1000000;
	if (idx < 1) return;
	s_data[idx - 1].stopDistance = sendData % 1000000;
}

void STATION_DB::setNextStation(int sendData) {
	int  sta1 = sendData / 1000000;
	bool stop1 = (sendData / 100000 % 10 > 0) ? 1 : 0;
	int  sta2 = sendData / 100 % 100;
	bool stop2 = (sendData / 10 % 10 > 0) ? 1 : 0;
	nextStation[0] = sta1 * 10 + stop1;
	nextStation[1] = sta2 * 10 + stop2;
}

void STATION_DB::setNextStopStation(int n) {
	nextStopStation[0] = 0;
	nextStopStation[1] = 0;
}

int STATION_DB::getNum(stationData s) { return s.num; }
int STATION_DB::getNum(int n) { return s_data[n].num; }

int STATION_DB::getArriveTime(stationData s) { return s.arriveTime; }
int STATION_DB::getArriveTime(int n) { return s_data[n].arriveTime; }

int STATION_DB::getLeaveTime(stationData s) { return s.leaveTime; }
int STATION_DB::getLeaveTime(int n) { return s_data[n].leaveTime; }

int STATION_DB::getStopDistance(stationData s) { return s.stopDistance; }
int STATION_DB::getStopDistance(int n) { return s_data[n].stopDistance; }

bool STATION_DB::isPass(stationData s) { return s.isPass; }
bool STATION_DB::isPass(int n) { return s_data[n].isPass; }

bool STATION_DB::isTarget(stationData s) { return s.isTarget; }
bool STATION_DB::isTarget(int n) { return s_data[n].isTarget; }

int STATION_DB::getStationNum(int n) {
	for (int i = 0; i < 99; ++i) 
		if (s_data[i].num == n) return i;
	return -1;
}

stationData* STATION_DB::getStationDataPointer() { return p; }

stationData STATION_DB::getStationData(int n) { return s_data[n]; }
stationData STATION_DB::getNextStopStationData(int n) {
	int m = 99;
	for (int i = n + 1; i < 99; ++i) {
		if (s_data[i].stopDistance == -1) break;
		if (!s_data[i].isPass) {
			m = i;
			break;
		}
	}
	return s_data[m];
}

stationData STATION_DB::getNextTargetStationData(int n) {
	int m = 99;
	for (int i = n + 1; i < 99; ++i) {
		if (s_data[i].stopDistance == -1) break;
		if (s_data[i].isTarget) {
			m = i;
			break;
		}
	}
	return s_data[m];
}

void STATION_DB::setScenarioData(int sendData) {
	//                  01010101
	int idx = sendData / 1000000;
	if (idx < 1) return;
	sc_data[idx - 1].difficulty = sendData / 10000 % 100;
	sc_data[idx - 1].routeName = sendData / 100 % 100;
	sc_data[idx - 1].missionName = sendData % 100;
}

int STATION_DB::getDifficulty(int n) { return sc_data[n].difficulty; }
int STATION_DB::getRouteName(int n) { return sc_data[n].routeName; }
int STATION_DB::getMissionName(int n) { return sc_data[n].missionName;}