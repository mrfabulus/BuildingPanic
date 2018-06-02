#pragma once

#include <cstdint>
#include "Entity/Generic/TileSetEntity.hpp"

class GameScene;
class Bitmap;

struct FontTileSet_Meta
{
    static const TileMeta Default_TileMeta;
};

class FontTileSetEntity : public TileSetEntity
{
    public:
        uint32_t dword4C;
        uint32_t dword50;
        uint32_t dword54;
        uint32_t dword58;
        uint16_t word5C;
        // uint8_t gap5E[2]; padding ?
        uint32_t dword60;
        uint8_t byte64;

        FontTileSetEntity(GameScene* aScene, Bitmap* aBitmap, uint32_t a4);
        virtual ~FontTileSetEntity();

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRendering() override;
};
