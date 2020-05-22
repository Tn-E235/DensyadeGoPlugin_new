#pragma once
struct dispEvalute {
	int idx;		// 出力するパネルIdx
	int totalTime;	// 表示した時間
	int score;		// 表示するスコア
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

