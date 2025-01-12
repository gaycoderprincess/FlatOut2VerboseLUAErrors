#include <windows.h>
#include <fstream>
#include "nya_commonhooklib.h"

#include "fo2.h"
#include "../nya-common-fouc/fo2versioncheck.h"

void* LogLUAErr(void* a1, int a2, void* a3) {
	MessageBoxA(nullptr, (const char*)lua_tolstring(a1, a2, a3), "Runtime error", 0x10);
	exit(0);
}

void* LogLUALoadErr(void* a1, int a2, void* a3) {
	MessageBoxA(nullptr, (const char*)lua_tolstring(a1, a2, a3), "Load error", 0x10);
	exit(0);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH: {
			DoFlatOutVersionCheck(FO2Version::FO2_1_2);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x525727, &LogLUAErr);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x5240C6, &LogLUALoadErr);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x524218, &LogLUALoadErr);
		} break;
		default:
			break;
	}
	return TRUE;
}