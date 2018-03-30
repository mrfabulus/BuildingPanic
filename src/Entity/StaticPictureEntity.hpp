#pragma once

#include "Entity.hpp"
#include "../Scene/GameScene.hpp"

class StaticPictureEntity : public Entity
{
    public:
        char byte64_lastArg;
        short renderDataPtrIndex;
        // EntityExtraPositionData *extraPositionData2;
        void* extraPositionData2;

        StaticPictureEntity (GameScene* aScene, void* aBitmap, void* dataPtrs, char a5)
            : Entity(aScene, aBitmap, dataPtrs)
        {
            this->byte64_lastArg = a5;
            this->renderDataPtrIndex = 0;
            this->extraPositionData2 = nullptr;
        }    
};
