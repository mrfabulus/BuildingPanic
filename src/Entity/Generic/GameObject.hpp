#pragma once

#include <cstdint>
class Entity;

class GameObject
{
    public:
        GameObject* nextAttachedEntity;
        GameObject* previousAttachedEntity;
        uint16_t layerIndex;
        int dword10;
        int centerX;
        int centerY;
        int dword1C_coordinateLikeThingie;

        GameObject();
        virtual ~GameObject();

        virtual void SetLayerIndex(uint16_t aLayerIndex);
        virtual void Update();
        virtual void Render();
};
