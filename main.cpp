#include <windows.h>
#include <fstream>
#include "nya_commonhooklib.h"

auto lua_tolstring = (const char*(*)(void*, int, void*))0x5B4400;
void* LogLUAErr(void* a1, int a2, void* a3) {
	MessageBoxA(nullptr, lua_tolstring(a1, a2, a3), "Runtime error", 0x10);
	exit(0);
}

void* LogLUALoadErr(void* a1, int a2, void* a3) {
	MessageBoxA(nullptr, lua_tolstring(a1, a2, a3), "Load error", 0x10);
	exit(0);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH: {
			if (NyaHookLib::GetEntryPoint() != 0x202638) {
				MessageBoxA(nullptr, "Unsupported game version! Make sure you're using DRM-free v1.2 (.exe size of 2990080 bytes)", "nya?!~", MB_ICONERROR);
				exit(0);
				return TRUE;
			}

			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x525727, &LogLUAErr);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x5240C6, &LogLUALoadErr);
			NyaHookLib::PatchRelative(NyaHookLib::CALL, 0x524218, &LogLUALoadErr);
		} break;
		default:
			break;
	}
	return TRUE;
}