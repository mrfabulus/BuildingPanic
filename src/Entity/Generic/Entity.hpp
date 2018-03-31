#pragma once

#include "Entity_base.hpp"
#include "../../SDL2_Interface.hpp"
#include "../../Globals.hpp"

class GameScene;
class Bitmap;

class EntityExtraPositionData
{
    public:
        Entity* entityPtr;
        double dCenterX;
        double dCenterY;
        double coordinateLikeThingie;

        EntityExtraPositionData(Entity* aEntity);
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
        MSRect* srcRectPtr;
        MSRect* dimensionRectPtr;
        MSRect* lastDataPtrRectanglePtr;
        int16_t word5C;
        int16_t AttachedRenderDataIndex;
        int32_t dword60;

        Entity(GameScene* aScene, Bitmap* aBitmap, void* dataPtrs);

        void ResetRenderRectangleMetadata();
        void AssignRenderRectangles(uint16_t aRenderDataPtrIndex);
        void AssignRenderRectanglesAdvanced();

        // VTable entries
        virtual void SetLayerIndex(uint16_t aLayerIndex);
        virtual void F3();
        virtual void Render();
        virtual bool AttachWithPosition(int32_t aX, int32_t aY, uint16_t AttachedRenderDataIndex);
        virtual bool AttachWithPosition2(int32_t aX, int32_t aY, int32_t unk, uint16_t AttachedRenderDataIndex);
        virtual bool Detach();
        virtual void SetupRenderingInformation();
        virtual void ReleaseResources();
        virtual bool CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect);
        virtual bool GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect);
};
