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
    
    if ((this->dword4C & 0x80000000) == 0)
    {
        if (this->dword4C > 0x5F5E0FF)
            this->dword4C = 99999999;
    }
    else
    {
        this->dword4C = 0;
    }

    if (this->dword54 != 0)
    {
        if (++this->word5C > 15)
        {
            this->word5C = 0;
            this->dword58 = (this->dword58 == 0);
        }
    }

    if (this->dword4C != this->dword50)
    {
        this->byte64 = 0;

        MSRect dst = { 0 };
        dst.top = 0;
        dst.bottom = this->tileMetadata->tileSize;
        int32_t v12 = 0;

        do
        {
            dst.left = this->tileMetadata->tileSize * v12;
            dst.right = this->tileMetadata->tileSize + dst.left;
        }
    }


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
