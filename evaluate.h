#pragma once
struct dispEvalute {
	int idx;		// �o�͂���p�l��Idx
	int totalTime;	// �\����������
	int score;		// �\������X�R�A
};
class EVALUTE {
	public:
		void init();
		void init(int);
		void main(ATS_VEHICLESTATE, int*, int*);
		void setDisp(int,int);
		void setDisp(dispEvalute*,int,int);
		dispEvalute* getBoxPointer();
	private:
		void updateInfo();
		void pushup();
		void pushup(dispEvalute*);
		void disp(int*);

		int delta_T = 0;
		int currentTime = 0;

		struct dispEvalute box[3] = {
			{0,0,0},
			{0,0,0},
			{0,0,0}
		};
		struct dispEvalute *p = box;
};

