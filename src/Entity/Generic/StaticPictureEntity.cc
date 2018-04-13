#include "StaticPictureEntity.hpp"

StaticPictureEntity::StaticPictureEntity (GameScene* aScene, Bitmap* aBitmap, const RenderMeta* dataPtrs, char a5)
    : Entity(aScene, aBitmap, dataPtrs)
{
    this->byte64_lastArg = a5;
    this->renderDataPtrIndex = 0;
    this->extraPositionData = nullptr;
}

StaticPictureEntity::~StaticPictureEntity()
{
}

void StaticPictureEntity::SetupRenderingInformation()
{
    EntityExtraPositionData* ptr = new EntityExtraPositionData(this);
    this->extraPositionData = ptr;
    this->extraPositionDataBase = ptr;
    this->ResetRenderRectangleMetadata();
    this->AssignRenderRectangles(this->renderDataPtrIndex);
}
