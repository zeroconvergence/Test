#include <Windows.h>
#include "AntiDump.h"

void ErasePEHeaderFromMemory() {
	DWORD OldProtect = 0;
	char *pBaseAddr = (char*)GetModuleHandle(NULL);
	VirtualProtect(pBaseAddr, 4096, PAGE_READWRITE, &OldProtect);

	SecureZeroMemory(pBaseAddr, 4096);
}
