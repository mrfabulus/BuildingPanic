#pragma once

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

        Entity_base()
        {
            this->nextAttachedEntity = 0;
            this->latestEntity = 0;
            this->layerIndex = 2;
            this->dword10 = 1;
            this->centerX = 0;
            this->centerY = 0;
            this->dword1C_coordinateLikeThingie = 0;
        }
};
