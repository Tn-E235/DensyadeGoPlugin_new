#pragma once
class G_SENSOR {
	public:
		void calc(ATS_VEHICLESTATE);
		void setUpper(double);
		int getValue();
		void dispGsensor(int*);

		void setScoringItemsCountPointer(scoringItemsCount*);
		void setChechedListPointer(checkedList*);
		void setBoxPointer(dispEvalute*);
	private:
		int value = 0;
		int deltaTime[10] = { 0,0,0,0,0,0,0,0,0,0 };
		double acceleration[10] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
		double d_acceleration[10] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
		double b_gSum = 0.0;
		double g_max = 5.0;
		double g_value = 0.0;
		bool g_over = false;

		EVALUTE evalute;
		struct scoringItemsCount* p_s_itemCount = nullptr;
		struct checkedList* p_cList = nullptr;
		struct dispEvalute* p_box = nullptr;
};
