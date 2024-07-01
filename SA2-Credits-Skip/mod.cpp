#include "pch.h"

HelperFunctions HelperFunctionsGlobal;

void initCreditsSkip();

extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		HelperFunctionsGlobal = helperFunctions;
		initCreditsSkip();
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}