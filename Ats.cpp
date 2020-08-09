#include "stdafx.h"
#include "atsplugin.h"
#include "inputIni.h"
#include "result.h"
#include "stationDB.h"
#include "evaluate.h"
#include "speedNoice.h"
#include "gSensor.h"
#include "dengo.h"
#include "Ats.h"

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved){
	char filePath[_MAX_PATH + 1] = _T("");						// ファイルパス格納
	char* posIni;												// 検索文字列へのポインタ
	bool loadCheck;												// INIファイルのロードに成功したかどうか
	::GetModuleFileName((HMODULE)hModule, filePath, _MAX_PATH);	// Ats.dllのファイルパスを取得
	posIni = strstr(filePath, ".dll");							// パスから.dllの位置を検索
	memmove(posIni, ".ini", 4);									// .dllを.iniに置換
	loadCheck = dIni.load(filePath);							// INIファイルをロードして結果を取得
	dgo.setGsensorEnable(dIni.GSENSOR.enable);					// Gセンサー有効設定
	dgo.setGsensorMode(dIni.GSENSOR.mode);						// Gセンサーのモードを設定
	dgo.setGsensorLimit(dIni.GSENSOR.limit);					// Gセンサーの上限値を設定
	return TRUE;
}
ATS_API int WINAPI GetPluginVersion() { return ATS_VERSION; }
ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC vehicleSpec) {
	g_svcBrake = vehicleSpec.BrakeNotches;
	g_emgBrake = g_svcBrake + 1;
	dgo.emergencyBrake(g_emgBrake);
}
ATS_API void WINAPI Initialize(int brake) { 
	g_speed = 0; 
	dgo.init();
}
ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehicleState, int *panel, int *sound){
	if (g_pilotlamp) { g_output.Reverser = g_reverser; }
	else { g_output.Reverser = 0; }
	g_output.Brake = g_brakeNotch;
	g_output.Power = g_powerNotch;
	g_output.ConstantSpeed = ATS_CONSTANTSPEED_CONTINUE;
	dgo.main(vehicleState, panel, sound);
	int speedLimit = dgo.speedLimit();
	if (vehicleState.Speed > speedLimit + 1) {
		g_output.Power = 0;
		g_output.Brake = g_svcBrake;
	}
    return g_output;
}
ATS_API void WINAPI SetPower(int notch) { 
	g_powerNotch = notch; 
	dgo.powerState(notch);
}
ATS_API void WINAPI SetBrake(int notch) {
	g_brakeNotch = notch;
	dgo.brakeState(notch);
}
ATS_API void WINAPI SetReverser(int pos) {
	g_reverser = pos; 
	dgo.reverserState(pos);
}
ATS_API void WINAPI KeyDown(int keyCode) {
	dgo.keyDown(keyCode);
}
ATS_API void WINAPI KeyUp(int keyCode) {
	dgo.keyUp(keyCode);
}
ATS_API void WINAPI HornBlow(int atsHornBlowIndex) { dgo.hornBlow(atsHornBlowIndex); }
ATS_API void WINAPI DoorOpen() { 
	g_pilotlamp = false; 
	dgo.doorState(true);
}
ATS_API void WINAPI DoorClose() { 
	g_pilotlamp = true; 
	dgo.doorState(false);
}
ATS_API void WINAPI SetSignal(int signal) {}
ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData) {
	dgo.beaconData(beaconData);
}

ATS_API void WINAPI Load() {}

ATS_API void WINAPI Dispose() {}
