#include "Entity/Stage/FontTileSetEntity.hpp"

// TODO: add tile meta
FontTileSetEntity::FontTileSetEntity(GameScene* aScene, Bitmap* aBitmap, uint32_t a4)
    : TileSetEntity(aScene, aBitmap, nullptr)
{
    this->dword50 = -1;
    this->dword4C = 0;
    this->dword54 = 0;
    this->dword58 = 0;
    this->word5C = 0;
    this->dword60 = a4;
    this->byte64 = 0;

    if (!this->attachedToLayer)
        this->layerIndex = 4;

    this->dword10 = 0;
}

FontTileSetEntity::~FontTileSetEntity()
{
}


void FontTileSetEntity::Update()
{
    TileSetEntity::Update();

    // TODO: a lot more from 004046E0
}

void FontTileSetEntity::Render()
{
    if (this->dword58 == 0)
    {
        TileSetEntity::Render();
    }
}

void FontTileSetEntity::SetupRendering()
{
    TileSetEntity::SetupRendering();

    this->dword50 = -1;
    this->dword4C = 0;
    this->dword54 = 0;
    this->dword58 = 0;
    this->word5C = 0;
}
