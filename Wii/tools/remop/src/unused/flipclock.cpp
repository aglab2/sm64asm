#include <sm64.h>

#define absf(x) ((x > 0) ? x : -x)

static bool FlipClockNearMario()
{
    auto me = M64_CURR_OBJ_PTR;
    auto mario = M64_MARIO_OBJ_PTR;
    
    auto distX = mario->pos.x - me->pos.x;
    distX = absf(distX);

    if (distX > 104.0f)
        return false;

    auto distY = mario->pos.y - me->pos.y;
    distY = absf(distY);
    
    // Relaxed from original 304 -> 300
    if (distY > 300.0f)
        return false;

    auto distZ = mario->pos.z - me->pos.z;
    distZ = absf(distZ);

    if (distZ > 104.0f)
        return false;

    return true;
}

void FlipClock()
{
    auto me = M64_CURR_OBJ_PTR;
    auto mario = M64_MARIO_OBJ_PTR;
    auto marioStr = M64_MARIO_STRUCT;

    if (me->action == 0)
    {
        if (IsMarioGroundpounding())
        {
            me->action = 1;
            return;
        }
        bool isHitting = FlipClockNearMario();
        if (isHitting && (mario->pos.y <= me->pos.y) && (marioStr->speed.y >= 15.0f))
        {
            me->action = 1;
            marioStr->speed.y = 0;
            return;
        }
        ProcessCollision();
    }
    else
    {
        if (me->timer == 0)
        {
            me->speedRotationPitch = 0x1680;
            me->scaling.z = 0.099609375f;
            PlaySoundProperly(0x300a0081);
        }

        me->x_rotation2 += me->speedRotationPitch;
        me->speedRotationPitch -= 0x20;
        if (me->speedRotationPitch == 0)
        {
            me->scaling.z = 1.0f;
            me->action = 0;
            me->x_rotation2 = 0;
        }

        if ((me->x_rotation2 & 0xffff) < me->x_rotation2)
        {
            me->x_rotation2 &= 0xffff;
            PlaySoundProperly(0x300a0081);
        }
    }
}
