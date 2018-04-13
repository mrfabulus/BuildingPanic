#pragma once

#include "GameObject.hpp"
#include "../../SDL2_Interface.hpp"
#include "../../Globals.hpp"

class GameScene;
class Bitmap;

class EntityExtraPositionData
{
    public:
        GameObject* entityPtr;
        double dCenterX;
        double dCenterY;
        double coordinateLikeThingie;

        EntityExtraPositionData(GameObject* aEntity);
        virtual ~EntityExtraPositionData();

        virtual void ReassignPositionToEntity();
};

class Entity : public GameObject
{
    public:
        GameScene* scene;
        Bitmap* entityImageBmp;
        EntityExtraPositionData* extraPositionDataBase;
        bool attachedToLayer;
        int32_t entityFacingLeft;
        int32_t dword34;
        int32_t dword38_assignedZeroFromRenderSetup;
        int32_t dword3C;
        int16_t renderConfigIndex;
        int16_t field_42;
        int16_t firstWordFromRenderConfig;
        int16_t field_46;
        const RenderMeta* renderMeta;
        uint16_t* renderConfiguration;
        MSRect* srcRectPtr;
        MSRect* dimensionRectPtr;
        MSRect* lastDataPtrRectanglePtr;
        int16_t word5C;
        int16_t AttachedRenderDataIndex;
        int32_t dword60;

        Entity(GameScene* aScene, Bitmap* aBitmap, const RenderMeta* aRenderMeta);
        virtual ~Entity();

        void ResetRenderRectangleMetadata();
        void AssignRenderRectangles(uint16_t aRenderConfigIndex);
        void AssignRenderRectanglesAdvanced();

        // VTable entries
        virtual void SetLayerIndex(uint16_t aLayerIndex) override;
        virtual void Update() override;
        virtual void Render() override;
        virtual bool AttachWithPosition(int32_t aX, int32_t aY, uint16_t AttachedRenderDataIndex);
        virtual bool AttachWithPosition2(int32_t aX, int32_t aY, int32_t unk, uint16_t AttachedRenderDataIndex);
        virtual void Detach();
        virtual void SetupRenderingInformation();
        virtual void ReleaseResources();
        virtual bool CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect);
        virtual void GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect);
};
