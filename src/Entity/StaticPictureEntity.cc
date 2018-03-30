#include "StaticPictureEntity.hpp"

StaticPictureEntity::StaticPictureEntity (GameScene* aScene, Bitmap* aBitmap, void* dataPtrs, char a5)
    : Entity(aScene, aBitmap, dataPtrs)
{
    this->byte64_lastArg = a5;
    this->renderDataPtrIndex = 0;
    this->extraPositionData2 = nullptr;
}
