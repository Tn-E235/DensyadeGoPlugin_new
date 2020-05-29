int g_emgBrake;			// 非常ノッチ
int g_svcBrake;			// 常用最大ノッチ
int g_brakeNotch;		// ブレーキノッチ
int g_powerNotch;		// 力行ノッチ
int g_reverser;			// レバーサ
bool g_pilotlamp;		// パイロットランプ
int g_time;				// 現在時刻
float g_speed;			// 速度計の速度[km/h]
int g_deltaT;			// フレーム時間[ms/frame]

ATS_HANDLES g_output;	// 出
DENGO dgo;
Dgo_acIni dIni;