#include <sm64.h>
#include <inputs.h>

int DoneTimer = 0;
int PrevActionTimer = 0;
int PrevAction = 0;

static void PrintTime(int time, int x, int y)
{
    int ms = (time % 60) * 100 / 60;
    int s  = (time / 60)  % 60;
    int m  = time / 60 / 60; 

    const int letterSize = 11;
    const int spaceSize = 8;

    PrintInt(x +  0, y, "%d", m);

    PrintInt(x +     letterSize +     spaceSize, y, "%d", s / 10);
    PrintInt(x + 2 * letterSize +     spaceSize, y, "%d", s % 10);
    
    PrintInt(x + 3 * letterSize + 2 * spaceSize, y, "%d", ms / 10);
    PrintInt(x + 4 * letterSize + 2 * spaceSize, y, "%d", ms % 10);
}

extern "C" void _start()
{
	auto action = *(int*) (0x8033B17C);
	auto vi = *(int*) (0x8032D580);
	
	if (action == 0x00001300 || action == 0x00001320 || action == 0x00001321 || action == 0x00001337)
	{
		if (PrevAction != action)
		{
			PrevActionTimer = vi;
		}
		PrintTime(PrevActionTimer, 20, 20);
	}
	PrevAction = action;

	if (DoneTimer)
	{
		PrintTime(DoneTimer, 20, 40);
	}
	else if ((*(char*)(0x8033B24A) == 2) && (*(float*) (0x8033B1B0)) < -7000.f)
	{
		DoneTimer = vi;
	}
}