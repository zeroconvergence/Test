#include "pch.h"
#include "TestDLL.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "obfuscate.h"

#define TESTDLL_EXPORTS
#define NTSTATUS LONG

#define JUNK_CODE_ONE        \
    __asm{push eax}            \
    __asm{xor eax, eax}        \
    __asm{setpo al}            \
    __asm{push edx}            \
    __asm{xor edx, eax}        \
    __asm{sal edx, 2}        \
    __asm{xchg eax, edx}    \
    __asm{pop edx}            \
    __asm{or eax, ecx}        \
    __asm{pop eax}

#define JUNK_CODE_TWO \
__asm{push eax} \
 __asm{xor eax, eax} \
__asm{mov eax,12} \
__asm{pop eax}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void Protection() {
	JUNK_CODE_ONE
	char value[128];
	DWORD dataSize = sizeof(value);

	if (GetHardVolumeInformation() == ("     WD-WX71A8135114") && getComputerName() == "0X6K7" && getUserName() == "k0x6k7" && ERROR_SUCCESS == RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVERSION", RRF_RT_ANY, nullptr, &value, &dataSize)) {
		
	}

	else {
		std::cout << AY_OBFUSCATE("You are not allowed to run this program") << std::endl;
		ExitProcess(1);
	}

	// Anti debug
	NtGlobalFlagsDetection();
	PushPopStack();
	NtGlobalFlag();
	NtQueryInformationProcess_SystemKernel();

	JUNK_CODE_TWO

	// Memory protection
	AntiMemoryModification();
	Patch_DebuggerBreakPoint();
	HardwareBreakPoint();
}