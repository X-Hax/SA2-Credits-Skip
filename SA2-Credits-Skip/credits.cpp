#include "pch.h"

DataPointer(int, EventState, 0x1A283FC);
DataPointer(int, dword_1AF0F9C, 0x1AF0F9C);
FunctionHook<void, task*> staffRollExec_t(0x799270);
FunctionHook<int> EventSubmodule_t(0x5FB270);

void FreeTask(task* tp)
{
	if (tp)
	{
		tp->exec = (TaskFuncPtr)DeleteObject_;
		tp = nullptr;
	}
}

void __cdecl staffRollExec_r(task* tp)
{
	ControllerEnabled[0] = true;
	if (ControllerPointers[0]->press & Buttons_Start || Controllers[0].press & Buttons_Start)
	{
		FreeTask(tp);
		dword_1AF0F9C = 0; //needed to skip sequence properly
		return;
	}

	staffRollExec_t.Original(tp);
}

static int delay = 0;
int EventSubmodule_r()
{
	if (ControllerPointers[0]->press & Buttons_Start || Controllers[0].press & Buttons_Start)
	{
		if (EventState < 4 && EventID == 210) //wait that credits task is deleted before skipping cutscene
		{
			delay = 30;
		}
	}

	if (delay > 1)
	{
		delay--;
	}
	else if (delay == 1)
	{
		StopMusic();
		EventState = 4;
		delay = 0;
	}

	return EventSubmodule_t.Original();
}

void initCreditsSkip()
{
	EventSubmodule_t.Hook(EventSubmodule_r);
	staffRollExec_t.Hook(staffRollExec_r);
}