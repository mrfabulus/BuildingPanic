#pragma once

#include <cstdint>
class Entity;

class Entity_base
{
    public:
        Entity* nextAttachedEntity;
        Entity* latestEntity;
        uint16_t layerIndex;
        int dword10;
        int centerX;
        int centerY;
        int dword1C_coordinateLikeThingie;

        Entity_base();
};