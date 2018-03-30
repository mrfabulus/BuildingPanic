#pragma once

#include "Entity_base.hpp"
#include "../SDL2_Interface.hpp"
#include "../Scene/GameScene.hpp"
#include "../Resource/Bitmap.hpp"

struct EntityExtraPositionData
{
    Entity* entityPtr;
    double dCenterX;
    double dCenterY;
    double coordinateLikeThingie;
};

class Entity : public Entity_base
{
    public:
        GameScene* scene;
        Bitmap* entityImageBmp;
        EntityExtraPositionData* extraPositionData;
        bool attachedToLayer;
        int32_t entityFacingLeft;
        int32_t dword34;
        int32_t dword38_assignedZeroFromRenderSetup;
        int32_t dword3C;
        int16_t renderDataPtrIndex;
        int16_t field_42;
        int16_t firstWordFromRenderDataPtr1;
        int16_t field_46;
        void* dataPtrs;
        int16_t* dataPtr1;
        SDL_Rect* srcRectPtr;
        SDL_Rect* dimensionRectPtr;
        SDL_Rect* lastDataPtrRectanglePtr;
        int16_t word5C;
        int16_t AttachedRenderDataIndex;
        int32_t dword60;

        Entity(GameScene* aScene, void* aBitmap, void* dataPtrs);

        void ResetRenderRectangleMetadata();

        // VTable entries
        virtual void SetLayerIndex(uint16_t aLayerIndex);
        virtual void F3();
        virtual bool Render();
        virtual bool AttachWithPosition2(int32_t aX, int32_t aY, uint16_t AttachedRenderDataIndex);
        virtual bool AttachWithPosition(int32_t aX, int32_t aY, int32_t unk, uint16_t AttachedRenderDataIndex);
        virtual bool Detach();
        virtual void SetupRenderingInformation();
        virtual void ReleaseResources();
        virtual bool CheckRenderBoundaries(SDL_RECT* aSrcRect, SDL_RECT* aDstRect);
        virtual bool GetRenderRectangles(SDL_RECT* aSrcRect, SDL_RECT* aDstRect);
};
