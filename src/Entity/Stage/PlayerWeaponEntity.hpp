#pragma once

#include <cstdint>
#include "Entity/Generic/FastEntity.hpp"

class GameScene;
class BitmapResourceManager;

struct PlayerWeaponEntity_Meta
{
    static const RenderMeta PlayerWeaponEntity_RenderMeta;
};

class PlayerWeaponEntity : public FastEntity
{
    public:
        EntityExtraPositionData3* extraPosData;
        FastEntityExtraPositionPair* feExtraPos3;
        uint8_t byte70;
        uint8_t byte71;
        uint8_t characterChosen;

        PlayerWeaponEntity(GameScene* aScene, BitmapResourceManager* aBmpMgr, uint8_t aCharacterChosen);
        virtual ~PlayerWeaponEntity();

        virtual void Update() override;
};
