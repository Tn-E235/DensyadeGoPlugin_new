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

		bool doorOpen;				// �h�A���
		int b_notch;				// B���[�L�m�b�`
		int p_notch;				// P�m�b�`
		int reverser;				// ���o�[�T�[
		float currentSpeed;			// ���ݑ��x
		int currentTime;			// ���ݎ���
		double currentZposition;	// ���݈ʒu(z���W)
		int updateCurrentStation;	// ���w�w�ԍ�
		bool target;				// �ڕW����/�ʉ߉w
		int currentStation;	// ���ݒ�Ԓ�/�ʉ�/���Ԃ����w -> �n��q�ő����X�V
		int nextStopStation;// ���w��ԉw -> �X�V��DB�����ԉw���Q��
		int nextStation;	// ���w(�ʉ�/���) -> ���݉w�̎��w���Q��
		bool update;		// �X�V���� -> 300�Ԓn��q
		bool finalStop;		// �I���w���� -> ���w�����w���Ȃ��Ƃ��I���w����

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

