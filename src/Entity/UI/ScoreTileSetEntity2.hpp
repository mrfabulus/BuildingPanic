#pragma once

#include "Entity/Generic/TileSetEntity.hpp"
#include <cstdint>

class GameScene;
class Bitmap;

struct ScoreTileSetEntity2_Meta
{
    static const TileMeta Default_TileMeta;
};

class ScoreTileSetEntity2 : public TileSetEntity
{
    public:
        uint16_t word4C;
        int16_t word4E;
        uint32_t dword50;
        uint32_t dword54;
        uint16_t word58;
        uint8_t gap5A[2];
        uint32_t dword5C;
        uint8_t byte60;

        ScoreTileSetEntity2(GameScene* aScene, Bitmap* aBitmap, int32_t a4);
        virtual ~ScoreTileSetEntity2();

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRendering() override;
};

