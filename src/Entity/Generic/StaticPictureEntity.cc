#include "Entity/Generic/StaticPictureEntity.hpp"

StaticPictureEntity::StaticPictureEntity (GameScene* aScene, Bitmap* aBitmap, const RenderMeta* dataPtrs, char a5)
    : Entity(aScene, aBitmap, dataPtrs)
{
    this->byte64_lastArg = a5; // shown/hidden?
    this->renderDataPtrIndex = 0;
    this->extraPositionData = nullptr;
}

StaticPictureEntity::~StaticPictureEntity()
{
}

// TODO: Check this.. ; may cause troubles but supposedly correct
void StaticPictureEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    /*
    this->extraPositionData->ReassignPositionToEntity();

    if (this->AssignRenderRectanglesAdvanced() && this->byte64_lastArg != 0)
    {
        this->Detach();
    }
    */
}

void StaticPictureEntity::SetupRenderingInformation()
{
    EntityExtraPositionData* ptr = new EntityExtraPositionData(this);
    this->extraPositionData = ptr;
    this->extraPositionDataBase = ptr;
    this->ResetRenderRectangleMetadata();
    this->AssignRenderRectangles(this->renderDataPtrIndex);
}

void StaticPictureEntity::ReleaseResources()
{
    this->extraPositionDataBase = nullptr;
    
    if (this->extraPositionData != nullptr)
    {
        delete this->extraPositionData;
        this->extraPositionData = nullptr;
    }
}
