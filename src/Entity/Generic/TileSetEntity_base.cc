#include "Entity/Generic/TileSetEntity_base.hpp"
#include "Entity/Generic/GameObject.hpp"

TileSetEntity_base::TileSetEntity_base(GameScene* aScene, Bitmap* aBitmap)
    : GameObject()
{
    this->scenePtr = aScene;
    this->extraPositionDataBase = nullptr;
    this->attachedToLayer = false;
    this->bitmap = aBitmap;
}

TileSetEntity_base::~TileSetEntity_base()
{
}

// New entries in the VTable
void TileSetEntity_base::SetupRendering()
{
}

void TileSetEntity_base::ReleaseResources()
{
}

void TileSetEntity_base::MakeSureImageIsReady()
{
}