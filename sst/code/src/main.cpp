#include <sm64.h>
#include <inputs.h>

int GlobalTimer = 0;
int Deadline = 5 * 60 * 30;

int BestAttemptTime = 0;
int WhenAttemptTime = 0;

int FramesOff = 1000000;

static void PrintTime(int time, int x, int y)
{
    int ms = (time % 30) * 100 / 30;
    int s  = (time / 30)  % 60;
    int m  = time / 30 / 60; 

    const int letterSize = 11;
    const int spaceSize = 8;

    PrintInt(x +  0, y, "%d", m);

    PrintInt(x +     letterSize +     spaceSize, y, "%d", s / 10);
    PrintInt(x + 2 * letterSize +     spaceSize, y, "%d", s % 10);
    
    PrintInt(x + 3 * letterSize + 2 * spaceSize, y, "%d", ms / 10);
    PrintInt(x + 4 * letterSize + 2 * spaceSize, y, "%d", ms % 10);
}

static void Reset()
{
        // reset
        *(char*) (0x8033B21E) = 0x8;
        *(short*)(0x8033B262) = 0x0;
        *(short*)(0x8033B218) = 0x0;
        *(char*) (0x8033B248) = 0x2;
        *(short*)(0x80361414) = 0x5;

        // some other crap
        *(short*)(0x8033B26C) = 0x00;
}

static void FixCamera()
{
    // cam fix
    auto idk = *(char*)(0x8033B249);
    if (idk == 0x1d)
        *(short*)(0x802872DA) = 0x1;
    else
        *(short*)(0x802872DA) = 0x0;

    *(int*)(0x80286D24) = 1;
}

extern "C" void _start()
{
    FixCamera();
	{
		auto time = *(short*)0x8033B26C;
		if (1 == time)
		{
			 ParallelLakituAngle = (M64_MARIO_STRUCT->rotation + 0x9000) & 0xc000;
		}
	}

    auto curStage = M64_CURRENT_LEVEL_ID;
    bool isSpeedrun = curStage != 0x10 && curStage != 0x06 && curStage != 0x1A;

    if (BestAttemptTime != 0)
    {
        PrintTime(BestAttemptTime, 228, 207);
    }
    
    if (WhenAttemptTime != 0)
    {
        PrintTime(WhenAttemptTime, 20, 40);
    }
	
	if (FramesOff != 1000000)
	{
		if (FramesOff > 0)
		{
			PrintInt(20, 207, "%d", FramesOff);
		}
		if (FramesOff < 0)
		{
			PrintInt(20, 207, "PB %d", -FramesOff);
		}
		if (FramesOff == 0)
		{
			PrintInt(20, 207, "TIE %d", FramesOff);
		}
	}

    if (isSpeedrun)
    {
        auto mario = M64_MARIO_STRUCT;

        if (GlobalTimer < Deadline)
        {
            GlobalTimer++;
            if (M64_CONTROLLER1_BUTTONS_HOLD & BUTTON_L)
            {
				FramesOff = 1000000;
                return Reset();
            }
        }
        
        if ((SM64Health & 0xff00) == 0)
		{
			FramesOff = 1000000;
            return Reset();
		}
        
        auto action = mario->action;
        // Handle Grab
        if (action == 0x00001302 || action == 0x00001303 || action == 0x00001307 || action == 0x00001904)
        {
			auto time = *(short*)0x8033B26C;
			if (BestAttemptTime)
				FramesOff = time - BestAttemptTime;
            
			if (BestAttemptTime == 0 || BestAttemptTime > time)
            {
                BestAttemptTime = time;
                WhenAttemptTime = GlobalTimer;
            }

            if (GlobalTimer < Deadline)
                return Reset();
        }

        // Handle qs
        if (action == 0x00021312)
        {
			FramesOff = 1000000;
            return Reset();
        }

        // Handle Death from deathfloor
        // FIXME: Cheap solution :)
        if (mario->curr_collision_triangle != nullptr)
        {
            auto coll = mario->curr_collision_triangle->collision_type;

            if (coll == 0xA)
            {
                if (mario->pos.y < mario->ground_y + 2200.f)
				{
					FramesOff = 1000000;
                    return Reset();
				}
            }

            // Handle Death from qs
            if (coll == 0x23)
            {
                if (mario->pos.y < mario->ground_y)
				{
					FramesOff = 1000000;
                    return Reset();
				}
            }
        }
    }
    else
    {
        if (M64_CONTROLLER1_BUTTONS_HOLD & BUTTON_L)
        {
            GlobalTimer = 0;
            BestAttemptTime = 0;
            WhenAttemptTime = 0;
			FramesOff = 1000000;
        }
    }
    
    PrintTime(Deadline - GlobalTimer, 20, 20);
}