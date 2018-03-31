#pragma once

#include <climits>
#include "../Generic/Entity.hpp"

class IntroCutSceneEntity : public Entity
{
    public:
        int8_t byte64;
        int8_t byte65;
        int8_t byte66;
        int32_t dword68;
        int32_t dword6C;
        
        // DDBLTFX cutSceneDDBLTFX;
        // LPDIRECTDRAWSURFACE7 ddSurface;
        SDL_Surface* ddSurface;

        IntroCutSceneEntity(GameScene* aScene, Bitmap* aBitmap);

        virtual void Render() override;
        virtual void SetupRenderingInformation() override;
};