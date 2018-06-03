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
        int32_t v7_index = 0;
        uint32_t v7_array[] = { 0x989680, 0x0F4240, 0x186A0, 0x2710, 0x3E8, 0x64, 0x0A, 1 };
        uint32_t v5 = this->dword4C;
        
        do
        {
            dst.left = this->tileMetadata->tileSize * v12;
            dst.right = this->tileMetadata->tileSize + dst.left;
            dst.right = this->tileMetadata->tileSize + dst.left;
            int32_t v11 = v5 / v7_array[v7_index];
            v5 %= v7_array[v7_index];

            if (this->dword60 == 0 || this->byte64 != 0 || v11 != 0 || v7_index > 6)
            {
                this->byte64 = 1;
                this->BltToComposed(v11, &dst);
            }
            else
            {
                this->BltToComposed(0xA, &dst);
            }

            v7_index++;
            v12++;
        }
        while (v7_index < 8);

        this->dword50 = this->dword4C;
    }
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
