#include "Entity/HUD/HudHeartEntity.hpp"
#include "Scene/GameScene.hpp"
#include "Resource/Bitmap.hpp"

HudHeartEntity::HudHeartEntity(GameScene* aScene, Bitmap* aBitmap)
    : Entity(aScene, aBitmap, (const RenderMeta*) nullptr)
{
    this->heartsLeft = 0;
    this->dword68 = 0;

    if (!this->attachedToLayer)
        this->layerIndex = 4;
    
    this->dword10 = 0;
}

HudHeartEntity::~HudHeartEntity()
{
}

void HudHeartEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    if (this->dword68 != 0)
    {
        this->dword68--;
        this->AssignRenderRectanglesAdvanced();
    }
    else
    {
        this->AssignRenderRectangles(this->heartsLeft);
        this->AssignRenderRectanglesAdvanced();
    }
}

void HudHeartEntity::SetupRenderingInformation()
{
    this->heartsLeft = 8;
    this->dword68 = 0;
    this->ResetRenderRectangleMetadata();
    this->AssignRenderRectangles(this->heartsLeft);
}
