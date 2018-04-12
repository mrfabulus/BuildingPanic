#pragma once

#include <cstdint>
class Entity;

class GameObject
{
    public:
        GameObject* nextAttachedEntity;
        GameObject* previousAttachedEntity;
        uint16_t layerIndex;
        int32_t dword10;
        int32_t centerX;
        int32_t centerY;
        int32_t coordinateLikeThingie;

        GameObject();
        virtual ~GameObject();

        virtual void SetLayerIndex(uint16_t aLayerIndex);
        virtual void Update();
        virtual void Render();
};
