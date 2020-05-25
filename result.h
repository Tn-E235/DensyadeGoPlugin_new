#pragma once
struct checkedList {
	bool pointingPilotLamp;			// �˕w������
	bool accelerateAfterDoorClose;	// �˕����
	bool pointingSpeed;				// ���x�v�w������
	bool pointingConstant;			// ���x�v�w������
	bool keepSpeedLimit;			// �������x����
	bool keepConstantSpeed;			// �葬�߲�ď���
	bool hornToWolker;				// �ې���ƈ��Ɍx�J
	bool hornToBridge;				// �S���Ɍx�J
	bool hornToPassenger;			// �z�[����q�Ɍx�J
	bool reducedLight;				// ����Ⴂ�ԗ��Ɍ���
	bool Gsenser;					// G�Z���T�[�쓮
	bool ebOver20;					// �}����(20km/h��EB)
	bool ebStopping;				// �����(EB)
	bool reAccelerateInForm;		// �\���ĉ���
	bool brakeReload;				// �u���[�L���ߒ���
	bool overRun;					// �I�[�o�[����
	bool speedOver;					// �������x�I�[�o�[
};
// �X�R�A
struct  scoringItemsCount {
	int pointingPilotLamp;			// �˕w������
	int accelerateAfterDoorClose;	// �˕����
	int pointingSpeed;				// ���x�v�w������
	int keepSpeedLimit;				// �������x����
	int keepConstantSpeed;			// �葬�߲�ď���
	int hornTo;						// �x�J
	int reducedLight;				// ����Ⴂ�ԗ��Ɍ���
	int gSensor;					// G�Z���T�[
	int eBrake;						// ���u���[�L
	bool reAccelerateInForm;		// �\���ĉ���
	bool brakeReload;				// �u���[�L���ߒ���
	int speedOver;					// �������x�I�[�o�[
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

