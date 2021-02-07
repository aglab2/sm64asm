#pragma once

extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"
#include "two_d.h"

class BeachTwoDCtl : TwoD
{
protected:
    void Init();
    static void sInit() { reinterpret_cast<BeachTwoDCtl*>(gCurrentObject)->Init(); }
    void Step();
    static void sStep() { reinterpret_cast<BeachTwoDCtl*>(gCurrentObject)->Step(); }

public:
    static int Behavior[];
};

class BeachTwoDRevert : Object
{
protected:
    void Step();
    static void sStep() { reinterpret_cast<BeachTwoDRevert*>(gCurrentObject)->Step(); }
public:
    static int Behavior[];
};

class BeachTwoDMusicFixer : Object
{
protected:
    void Step();
    static void sStep() { reinterpret_cast<BeachTwoDMusicFixer*>(gCurrentObject)->Step(); }
public:
    static int Behavior[];
};
