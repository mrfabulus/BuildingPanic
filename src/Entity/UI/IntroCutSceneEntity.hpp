#pragma once

#include <cstdint>
#include "../Generic/Entity.hpp"

struct IntroCutSceneEntity_Meta
{
    static const RenderMeta CutScene_RenderMeta;
};

class IntroCutSceneEntity : public Entity
{
    public:
        int8_t byte64;
        int8_t byte65;
        int8_t byte66;
        int32_t stretchOffset;
        int32_t stretchAcceleration;

        SDL_Surface* ddSurface;

        IntroCutSceneEntity(GameScene* aScene, Bitmap* aBitmap);
        virtual ~IntroCutSceneEntity();

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRenderingInformation() override;

        void Custom_AssignRenderRectangles(uint16_t aRenderDataPtrIndex);
        void F_4146A0(uint16_t aRenderDataPtrIndex);
        void F_4146D0();
};