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
	bool Gsenser;					// G�Z���T�[����
	bool ebOver20;					// �}����(20km/h��EB)
	bool ebStopping;				// �����(EB)
	bool reAccelerateInForm;		// �\���ĉ���
	bool brakeReload;				// �u���[�L���ߒ���
};
struct scoringItems {
	bool pointingPilotLamp;			// �˕w������
	bool accelerateAfterDoorClose;	// �˕����
	int pointingSpeed;				// ���x�v�w������
	int keepSpeedLimit;				// �������x����
	int keepConstantSpeed;			// �葬�߲�ď���
	int hornToWolker;				// �ې���ƈ��Ɍx�J
	int hornToBridge;				// �S���Ɍx�J
	int hornToPassenger;			// �z�[����q�Ɍx�J
	int reducedLight;				// ����Ⴂ�ԗ��Ɍ���
	bool Gsenser;					// G�Z���T�[����
	bool ebOver20;					// �}����(20km/h��EB)
	bool ebStopping;				// �����(EB)
	bool reAccelerateInForm;		// �\���ĉ���
	bool brakeReload;				// �u���[�L���ߒ���
};
struct  scoringItemsCount {
	int pointingSpeed[2];			// ���x�v�w������
	int keepSpeedLimit[2];			// �������x����
	int keepConstantSpeed[2];		// �葬�߲�ď���
	int hornToWolker[2];			// �ې���ƈ��Ɍx�J
	int hornToBridge[2];			// �S���Ɍx�J
	int hornToPassenger[2];			// �z�[����q�Ɍx�J
	int reducedLight[2];			// ����Ⴂ�ԗ��Ɍ���
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

