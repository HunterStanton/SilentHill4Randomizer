#include "stdafx.h"
#include "sh4/sys/env/sf_env.h"
#include <plog/Log.h>

injector::hook_back<float(__cdecl*)()> sfSysEnvFps;

void InitializeSfEnvFunctions()
{
	sfSysEnvFps.fun = injector::auto_pointer(0x0055ae60);
}