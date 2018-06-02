#include "Entity/UI/FontTileSetEntity.hpp"

FontTileSetEntity::FontTileSetEntity(GameScene* aScene, Bitmap* aBitmap, uint32_t a4)
    : TileSetEntity(aScene, aBitmap, &FontTileSet_Meta::Default_TileMeta)
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

// ------ Default_TileMeta TileMeta START ------
const uint16_t Default_TileMeta_1[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const MSRect Default_TileMeta_Rects[] =
{
    { 0x0, 0x0, 0x10, 0x10 },
    { 0x10, 0x0, 0x20, 0x10 },
    { 0x20, 0x0, 0x30, 0x10 },
    { 0x30, 0x0, 0x40, 0x10 },
    { 0x40, 0x0, 0x50, 0x10 },
    { 0x50, 0x0, 0x60, 0x10 },
    { 0x60, 0x0, 0x70, 0x10 },
    { 0x70, 0x0, 0x80, 0x10 },
    { 0x80, 0x0, 0x90, 0x10 },
    { 0x90, 0x0, 0x0A0, 0x10 },
    { 0x0A0, 0x0, 0x0B0, 0x10 }
};

const TileMeta FontTileSet_Meta::Default_TileMeta =
{
    128,
    16,
    16,
    0,
    8,
    0,
    0,
    &Default_TileMeta_1[0],
    &Default_TileMeta_Rects[0],
    0
};
// ------ Default_TileMeta TileMeta END ------
