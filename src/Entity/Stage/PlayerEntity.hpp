#pragma once

#include <cstdint>
#include "Entity/Generic/FastEntity.hpp"

class StaticPictureEntity;
class Ingame_Stage_Scene;
class BitmapResourceManager;
class SoundResourceManager;
class HudHeartEntity;
class PlayerWeaponEntity;

struct PlayerEntity_Meta
{
    static const RenderMeta Doka_RenderMeta;
    static const RenderMeta Tobi_RenderMeta;
    static const RenderMeta* Player_RenderMetaArray[2];
};

class PlayerEntity : public FastEntity
{
    public:
        uint8_t byte68;
        uint8_t byte69;
        uint8_t updatePhase;
        uint8_t byte6B;
        uint8_t byte6C;
        uint8_t byte6D;
        uint16_t unsigned6E;
        uint32_t dword70;
        uint32_t dword74;
        uint32_t dword78;
        uint32_t dword7C;
        double   double80;
        double   double88;
        uint32_t dword90;
        EntityExtraPositionData3* extraPositionData;
        FastEntityExtraPositionPair* extraPositionPair;
        HudHeartEntity* dword9C;
        StaticPictureEntity* piyoBmp; // Dizzy star particles above the player's head
        uint32_t dwordA4; // some pointer
        StaticPictureEntity* hitBmp; // Hit particle when an item fall's on the player
        PlayerWeaponEntity* playerWeaponEntities[3];
        SoundResourceManager* sndMgr;
        uint32_t dwordBC;

        PlayerEntity(Ingame_Stage_Scene* aScene, BitmapResourceManager* aBmpMgr, int aCharacterChosen, SoundResourceManager* aSndMgr, int a6);
        virtual ~PlayerEntity();

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources() override;

        void Update_0();
        void Update_1();

        void Update_1_1();
        void Update_1_2();
        void Update_1_3();
        uint16_t Update_1_4();
        void Update_1_5();

        void Update_2();
        void Update_3();
        void Update_4();
        void Update_5();
        void Update_6();
        void Update_7();
        void Update_10();
        void Update_11();

        
        
};
