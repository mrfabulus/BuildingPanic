#pragma once

#include "../SDL2_Interface.hpp"
#include "Entity_base.hpp"
#include "../Scene/GameScene.hpp"

class Entity : public Entity_base
{
    public:
        GameScene* scene;
        // Bitmap* entityImageBmp;
        void* entityImageBmp;
        // EntityExtraPositionData* extraPositionData;
        void* extraPositionData;
        bool attachedToLayer;
        int entityFacingLeft;
        int dword34;
        int dword38_assignedZeroFromRenderSetup;
        int dword3C;
        short renderDataPtrIndex;
        short field_42;
        short firstWordFromRenderDataPtr1;
        short field_46;
        void* dataPtrs;
        short* dataPtr1;
        SDL_Rect* srcRectPtr;
        SDL_Rect* dimensionRectPtr;
        SDL_Rect* lastDataPtrRectanglePtr;
        short word5C;
        short AttachedRenderDataIndex;
        int dword60;

        Entity(GameScene* aScene, void* aBitmap, void* dataPtrs)
            : Entity_base()
        {
            this->scene = aScene;
            this->entityImageBmp = aBitmap;
            this->extraPositionData = 0;
            this->attachedToLayer = 0;
            this->entityFacingLeft = 0;
            this->dword34 = 0;
            this->dword38_assignedZeroFromRenderSetup = 0;
            this->dword3C = 0;
            this->dataPtrs = dataPtrs;
            this->word5C = 0;
            this->AttachedRenderDataIndex = 0;
            this->dword60 = 0;

            if ( !aBitmap )
            {
                // bpanic_ShowError_wrapper(600, 1, &surfaceUninitializedErrorStr);// Surface is not initialized.
            }

            // Entity_ResetRenderRectangleMetadata(this);
        }

        void AttachWithPosition(int aX, int aY, uint16_t AttachedRenderDataIndex)
        {

        }
};
