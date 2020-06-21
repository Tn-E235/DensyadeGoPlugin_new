#pragma once
#define G_ARRAY 60
class G_SENSOR {
	public:
		void init();
		void calc(ATS_VEHICLESTATE);
		int getValue();
		void dispGsensor(int*);

		void setEnable(int);
		void setMode(int);
		void setUpper(double);

		void setScoringItemsCountPointer(scoringItemsCount*);
		void setChechedListPointer(checkedList*);
		void setBoxPointer(dispEvalute*);
	private:
		int currentTime = 0;
		int delta_T = 0;
		int v_deltaTime[G_ARRAY];
		double v_acceleration[G_ARRAY];
		double v_speed[G_ARRAY];
		int v_time[G_ARRAY];
		double v_gValue[G_ARRAY];
		double g_value;
		bool g_over = false;

		bool enable = false;
		int mode = 0;
		double g_max = 5.0;

		EVALUTE evalute;
		struct scoringItemsCount* p_s_itemCount = nullptr;
		struct checkedList* p_cList = nullptr;
		struct dispEvalute* p_box = nullptr;

};
