#include "combiner.h"
#include "macro.h"
extern "C"
{
    #include "types.h"
    #include "game/memory.h"
    #include "game/object_helpers.h"
    #include "game/print.h"
    #include "engine/graph_node.h"
    #include "PR/os_libc.h"
}
#include "trap.h"

namespace Combiner
{
    enum class CombinerTypes
    {
        SHADED_SHADED,
        SHADED_ONE,
        SHADED_ENV,
        SHADEDENV_ONE,
        UNKNOWN,
    };

    static unsigned int originalCombiners[] = 
    { 
        0xFC121824, 0xFF33FFFF,
        0xFC127E24, 0xFFFFFDFE,
        0xFC121A24, 0xFF37FFFF,
        0xFC42FE85, 0xFFFFFDFE,
    };
    static unsigned int patchedCombiners[] = 
    { 
        0xFC6218C4, 0x1133FFFF,
        0xFC627EC4, 0x11FFFDFE,
        0xFC621AC4, 0x1137FFFF,
        0xFC627EC4, 0x55FFFDFE
    };

    struct Combiner
    {
        unsigned int* ptr;
        CombinerTypes type;
    };

#define FOUND_COMBINERS_COUNT 32
    static struct Combiner foundCombiners[FOUND_COMBINERS_COUNT];

    static int combinersInDlCount[] = { 0, 3, 0, 1, 1, 2, 0 };

__attribute__((noinline)) // static
    CombinerTypes Decode(unsigned int* ptr)
    {
        for (int i = 0; i < ARRAY_SIZE(originalCombiners); i += 2)
        {
            if (originalCombiners[i + 0] == ptr[0])
                return (CombinerTypes) (i / 2);
        }

        trap();
        return CombinerTypes::UNKNOWN;
    }

__attribute__((noinline)) // static
    void Find(int& pos, int* dataSegmentedPtr, int cnt)
    {
        unsigned int* dataPtr = (unsigned int*) segmented_to_virtual(dataSegmentedPtr);
        while (cnt)
        {
            unsigned char* cmdPtr = (unsigned char*) dataPtr;
            if (0xfc == *cmdPtr)
            {
                foundCombiners[pos].ptr = dataPtr;
                foundCombiners[pos].type = Decode(dataPtr);
                cnt--;
                pos++;
            }

            dataPtr += 2;
        }
    }

    // TODO: This is super lazy :)
__attribute__((noinline)) // static
    void ParseObject(int& pos, int id, int cnt)
    {
        // node is GRAPH_NODE_TYPE_CULLING_RADIUS - GraphNodeCullingRadius
        auto node = gLoadedGraphNodes[id];
        // child is GRAPH_NODE_TYPE_DISPLAY_LIST - GraphNodeDisplayList 
        auto graphNode = node->children;

        auto curNode = graphNode;
        do 
        {
            auto dlNode = (struct GraphNodeDisplayList*) curNode;
            auto dataSegPtr = dlNode->displayList;
            Find(pos, (int*) dataSegPtr, cnt);
        } 
        while ((curNode = curNode->next) != graphNode);
    }
/*
[0127E4C0 / 19005E40]             15 04 00 00 0E01F4D0 // Load display list 0x0E01F4D0 into layer 4
[0127E4C8 / 19005E48]             15 01 00 00 0E01FAE0 // Load display list 0x0E01FAE0 into layer 1
[0127E4D0 / 19005E50]             15 03 00 00 0E023090 // Load display list 0x0E023090 into layer 3
[0127E4D8 / 19005E58]             15 05 00 00 0E023638 // Load display list 0x0E023638 into layer 5
 */
__attribute__((noinline))
    void Find()
    {
        bzero(foundCombiners, sizeof(foundCombiners));        
        int pos = 0;
        
        ParseObject(pos, 0xfb, 1);

        // Parse course dl
        int* geoPtr = (int*) segmented_to_virtual((void*) 0x19005E40);
        while (true)
        {
            char* geoCmdPtr = (char*) geoPtr;
            if (*geoCmdPtr != 0x15)
                break;

            char* geoLayerPtr = geoCmdPtr + 1;
            int layer = *geoLayerPtr;
            int** geoDataPtr = (int**) (geoPtr + 1);
            Find(pos, *geoDataPtr, combinersInDlCount[layer]);

            geoPtr += 2;
        }

        // Parse object dl
        ParseObject(pos, 0xeb, 1);
        ParseObject(pos, 0xec, 1);
        ParseObject(pos, 0xed, 1);
        ParseObject(pos, 0xee, 1);
        ParseObject(pos, 0xef, 1);
        ParseObject(pos, 0xef, 1);
        ParseObject(pos, 0xf3, 1);
        ParseObject(pos, 0xf4, 1);
        ParseObject(pos, 0xf5, 1);
        ParseObject(pos, 0xf6, 1);
        ParseObject(pos, 0xf9, 1);

        if (pos >= FOUND_COMBINERS_COUNT)
            trap();
    }

__attribute__((noinline))
    void Switch(int type)
    {
        unsigned int* neededCombiners = type  ? patchedCombiners : originalCombiners;
        unsigned int* otherCombiners  = !type ? patchedCombiners : originalCombiners;
        for (int i = 0; i < FOUND_COMBINERS_COUNT; i++)
        {
            const auto& comb = foundCombiners[i];
            if (!comb.ptr)
            {
                return;
            }

            unsigned int* combiners = i >= 5 ? neededCombiners : otherCombiners;
            comb.ptr[0] = combiners[0 + (int) comb.type * 2];
            comb.ptr[1] = combiners[1 + (int) comb.type * 2];
        }
    }
} // namespace Combiner