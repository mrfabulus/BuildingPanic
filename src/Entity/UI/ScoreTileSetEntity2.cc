#include "Entity/UI/ScoreTileSetEntity2.hpp"
#include "Scene/GameScene.hpp"
#include "Resource/Bitmap.hpp"

ScoreTileSetEntity2::ScoreTileSetEntity2(GameScene* aScene, Bitmap* aBitmap, int32_t a4)
    : TileSetEntity(aScene, aBitmap, &ScoreTileSetEntity2_Meta::Default_TileMeta)
{
    this->word4E = -1;
    this->word4C = 0;
    this->dword50 = 0;
    this->dword54 = 0;
    this->word58 = 0;
    this->dword5C = a4;
    this->byte60 = 0;

    if (!this->attachedToLayer)
        this->layerIndex = 4;
    
    this->dword10 = 0;
}

ScoreTileSetEntity2::~ScoreTileSetEntity2()
{
}

void ScoreTileSetEntity2::Update()
{
    TileSetEntity::Update();
    
    if ((this->word4C & 0x8000) == 0)
    {
        if (this->word4C > 0x63)
            this->word4C = 99;
    }
    else
    {
        this->word4C = 0;
    }

    if (this->dword50 != 0)
    {
        if (++this->word58 > 15)
        {
            this->word58 = 0;
            this->dword54 = (this->dword54 == 0);
        }
    }

    if (this->word4C != this->word4E)
    {
        this->byte60 = 0;

        MSRect dst = { 0 };
        dst.top = 0;
        dst.bottom = this->tileMetadata->tileSize;
        int32_t v12 = 0;
        int32_t v7_index = 0;
        uint16_t v7_array[] = { 0x0A, 1 };
        uint16_t v1 = this->word4C;

        do
        {
            dst.left = this->tileMetadata->tileSize * v12;
            dst.right = this->tileMetadata->tileSize + dst.left;
            int32_t v11 = v1 / v7_array[v7_index];
            v1 -= (v7_array[v7_index] * v11);

            if (this->dword5C == 0 || this->byte60 != 0 || v11 != 0 || v7_index > 0)
            {
                this->byte60 = 1;
                this->BltToComposed(v11, &dst);
            }
            else
            {
                this->BltToComposed(0xA, &dst);
            }

            v7_index++;
            v12++;
        }
        while (v7_index < 2);

        this->word4E = this->word4C;
    }
}

void ScoreTileSetEntity2::Render()
{
    if (this->dword54 == 0)
    {
        TileSetEntity::Render();
    }
}

void ScoreTileSetEntity2::SetupRendering()
{
    TileSetEntity::SetupRendering();
    this->word4E = -1;
    this->word4C = 0;
    this->dword50 = 0;
    this->dword54 = 0;
    this->word58 = 0;
}

// ------ Default_TileMeta TileMeta START ------
const uint16_t Default_TileMeta_1[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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

const TileMeta ScoreTileSetEntity2_Meta::Default_TileMeta =
{
    32,
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
