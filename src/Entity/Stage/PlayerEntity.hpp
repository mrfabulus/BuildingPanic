#pragma once

#include <cstdint>
#include "Entity/Generic/AnimatedEntity.hpp"

class StaticPictureEntity;
class Ingame_Stage_Scene;
class BitmapResourceManager;
class SoundResourceManager;
class HudHeartEntity;

struct PlayerEntity_Meta
{
    static const RenderMeta Doka_RenderMeta;
    static const RenderMeta Tobi_RenderMeta;
};

class PlayerEntity : public AnimatedEntity
{
    public:
        uint8_t byte68;
        uint8_t byte69;
        uint8_t byte6A;
        uint8_t byte6B;
        uint8_t byte6C;
        uint8_t byte6D;
        uint16_t unsigned6E;
        uint32_t dword70;
        uint32_t dword74;
        uint32_t dword78;
        uint32_t dword7C;
        double   double80;
        uint32_t dword88;
        uint32_t dword8C;
        uint32_t dword90;
        EntityExtraPositionData3* extraPositionData;
        uint32_t dword98;
        HudHeartEntity* dword9C;
        StaticPictureEntity* piyoBmp;
        uint32_t dwordA4;
        StaticPictureEntity* hitBmp;
        uint32_t dwordAC[3]; // some sort of entity*[]
        SoundResourceManager* sndMgr;
        uint32_t dwordBC;

        PlayerEntity(Ingame_Stage_Scene* aScene, BitmapResourceManager* aBmpMgr, int aCharacterChosen, SoundResourceManager* aSndMgr, int a6);
        virtual ~PlayerEntity();

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources() override;
};
