#include <string.h>
#include "Manager/Level/LevelManager_Normal.hpp"
#include "Manager/SaveManager.hpp"
#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"
#include "Entity/Stage/PlayerEntity.hpp"
#include "Entity/Generic/StaticPictureEntity.hpp"
#include "Entity/HUD/HudHeartEntity.hpp"
#include "Manager/BitmapResourceManager.hpp"
#include "Entity/UI/FontTileSetEntity.hpp"

LevelManager_Normal::LevelManager_Normal(Ingame_BasicStage_Scene* aScene)
    : LevelManager_base(aScene)
{
    this->levelPhase = 0;
    this->dwordE4 = 0;
    this->dwordE8 = 0;
    this->dwordC4[0] = nullptr;
    this->dwordC4[1] = nullptr;
    this->dwordCC[0] = nullptr;
    this->dwordCC[1] = nullptr;
    this->dwordCC[2] = nullptr;
    this->dwordCC[3] = nullptr;
    this->dwordDC = 0;
    this->wordE0 = 0;
    this->dword88 = nullptr;
    memset(this->buffer8C, 0, sizeof(this->buffer8C));

    if (this->CreateEntities())
    {
        this->Scene->player1Entity->dword9C = this->Scene->hudHeartP1;
        uint16_t heartsLeft = this->Scene->saveManager->playerObject1.heartsLeft;
        this->Scene->hudHeartP1->heartsLeft = heartsLeft;
        this->Scene->hudHeartP1->AssignRenderRectangles(heartsLeft);

        // this->Scene->hudScoreP1->renderConfiguration = this->Scene->saveManager->playerObject1.dword4;

        if (this->Scene->saveManager->Is2PMode())
        {
            this->Scene->player2Entity->dword9C = this->Scene->hudHeartP2;
            heartsLeft = this->Scene->saveManager->playerObject2.heartsLeft;
            this->Scene->hudHeartP2->heartsLeft = heartsLeft;
            this->Scene->hudHeartP2->AssignRenderRectangles(heartsLeft);

            // this->Scene->hudScoreP2->renderConfiguration = this->Scene->saveManager->playerObject2.dword4;
        }

        this->SetupLamps1();
        this->SetupLamps2();
    }
}

LevelManager_Normal::~LevelManager_Normal()
{
}

bool LevelManager_Normal::CreateEntities()
{
    // TODO: Create enemy factories

    for (uint32_t i = 0; i < 2; i++)
    {
        this->dwordC4[i] = new FontTileSetEntity(this->Scene, this->Scene->sceneBitmapMgr->bitmapPtrs[21], 0);
    }

    for (uint32_t i = 0; i < 4; i++)
    {
        // TODO: Create score tiles
    }

    this->dword88 = new StaticPictureEntity(this->Scene, this->Scene->sceneBitmapMgr->bitmapPtrs[37], nullptr, 0); // CURSOR
    this->dword88->SetLayerIndex(4);
    this->dword88->dword10 = 0;

    for (uint32_t i = 0; i < 14; i++)
    {
        this->buffer8C[i] = new StaticPictureEntity(this->Scene, this->Scene->sceneBitmapMgr->bitmapPtrs[36], nullptr, 0); // WNDMSG
        this->buffer8C[i]->SetLayerIndex(4);
        this->buffer8C[i]->dword10 = 0;
    }

    return true;
}

void LevelManager_Normal::SetupLamps1()
{
}

void LevelManager_Normal::SetupLamps2()
{
}

void LevelManager_Normal::F2()
{
}

void LevelManager_Normal::F3()
{
}

void LevelManager_Normal::F4()
{
}

void LevelManager_Normal::F5()
{
}

void LevelManager_Normal::F6()
{
}

void LevelManager_Normal::F7()
{
}

void LevelManager_Normal::F8()
{
}

void LevelManager_Normal::F9()
{
}
