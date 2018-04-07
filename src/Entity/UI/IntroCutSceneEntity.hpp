#pragma once

#include <cstdint>
#include "../Generic/Entity.hpp"

struct IntroCutSceneEntity_RenderMeta
{
    static const void** RenderMetaPtr;
};

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
        virtual ~IntroCutSceneEntity();
        // TODO: Implement dtor and release surface there

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRenderingInformation() override;

        void Custom_AssignRenderRectangles(uint16_t aRenderDataPtrIndex);
        void F_4146A0(uint16_t aRenderDataPtrIndex);
        void F_4146D0();
};