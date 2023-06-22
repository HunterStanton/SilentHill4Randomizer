#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/sys/apps/sf_step.h"

// gets the current step in the game's state machine
// steps are used in the UI, loading, etc. loops to know when actions have completed so new actions can take place
// I am still not sure of the exact mechanisms involved when multiple state machines are active at once
injector::hook_back<int(__cdecl*)()> sfStepGet;

void InitializeSfStepFunctions()
{
	sfStepGet.fun = injector::auto_pointer(0x00555c40);
}