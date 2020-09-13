#include <sm64.h>

int gLagCounter = 0;
int gPrevLagCounter = 0;
int gConsecutiveLagCounter = 0;

#define FPS_PRECISION 60
char gLagCounters[FPS_PRECISION] = {};
int gLagCountersPtr = 0;
int gLagSum = 0;

int gPrevLevelNum = 0;
int gPrevLevelArea = 0;

// 30fps and a single digit
#define FPS_BASE 300
int gFPS = 0;

static void RecalcFPS(int newLag)
{
    int removedLag = gLagCounters[gLagCountersPtr];
    gLagCounters[gLagCountersPtr] = newLag;
    gLagSum = gLagSum - removedLag + newLag;
    
    gLagCountersPtr++;
    gLagCountersPtr %= FPS_PRECISION;

    int laglessCount = FPS_PRECISION * 2;
    int lagCount = laglessCount + gLagSum;
    gFPS = FPS_BASE * laglessCount / lagCount;
}

void LagCounter()
{
    auto lagAmount = gLagCounter - gPrevLagCounter;

    RecalcFPS(lagAmount);

    if (lagAmount)
    {
        if (gConsecutiveLagCounter < 100)
            gConsecutiveLagCounter += 2 * lagAmount;

        for (int i = 0; i < gConsecutiveLagCounter; i++)
        {
            auto obj = FindUnimportantObject();
            if (obj)
                UnloadObject(obj);
            else
                break;
        }
    }
    else
    {
        if (gConsecutiveLagCounter)
            gConsecutiveLagCounter--;
    }

fini:
    gPrevLagCounter = gLagCounter;
}