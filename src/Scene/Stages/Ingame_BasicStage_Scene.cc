#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"
#include "Manager/SaveManager.hpp"
#include "Manager/Level/LevelManager_Normal.hpp"
#include "Entity/Stage/PlayerEntity.hpp"
#include "Entity/Generic/StaticPictureEntity.hpp"
#include "Input/InputProcessorBase.hpp"

Ingame_BasicStage_Scene::Ingame_BasicStage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager)
    : Ingame_Stage_Scene(aPaletteDataBytes, aSaveManager)
{
    LevelManager_base* managerObject = nullptr;
    printf("Ingame_BasicStage_Scene::ctor\n");

    // Check demoplay flag
    /*if (((this->saveManager->saveFlags >> 8) & 0x10) == 0)
    {
        printf("Ingame_BasicStage_Scene Demoplay\n");
        // TODO: Create LevelManager_Demoplay
    }
    else */ if (this->saveManager->IsSecretMode())
    {
        printf("Ingame_BasicStage_Scene Secret mode\n");
        // TODO: Create LevelManager_Secret
    }
    else if (this->saveManager->nextLevel == 2)
    {
        printf("Ingame_BasicStage_Scene BonusLevel\n");
        // TODO: Create LevelManager_BonusLevel
    }
    else if (this->saveManager->nextLevel == 5)
    {
        printf("Ingame_BasicStage_Scene BossLvl\n");
        // TODO: Create LevelManager_BossLevel
    }
    else
    {
        printf("Ingame_BasicStage_Scene Normal\n");
        managerObject = new LevelManager_Normal(this);
    }

    this->levelManagerObject = managerObject;
}

Ingame_BasicStage_Scene::~Ingame_BasicStage_Scene()
{
    // TODO: Stop midi

    if (this->levelManagerObject != nullptr)
    {
        delete this->levelManagerObject;
        this->levelManagerObject = nullptr;
    }
}

void Ingame_BasicStage_Scene::InitStage()
{
    if (this->player1Entity->attachedToLayer || this->fadeIn_active || this->fadeAway_active)
    {
        this->levelManagerObject->Init();
        return;
    }

    if (!this->saveManager->IsFlagMaskEnabledAny(0x1000))
    {
        // TODO: stop midi
        // TODO: start right midi for level
    }

    this->player1Entity->AttachWithPosition(0x100, 512, 0);
    this->player1Entity->dword3C = 0;

    if (this->saveManager->Is2PMode())
    {
        this->player2Entity->AttachWithPosition(0xC0, 512, 0);
        this->player2Entity->dword3C = 0;
    }

    this->levelManagerObject->Init();
}

void Ingame_BasicStage_Scene::GameplayUpdate()
{
    if (this->paused)
    {
        // UNPAUSE
        if ( (this->inputProcessor->newButtonPressesMask & 2) != 0)
        {
            // bpanic_play_midi();
            // SoundResourceManager_Unpause(this->base.sceneSoundManager);
            this->pauseTextEntity->Detach();
            this->paused = false;
        }
        else
        {
            this->pauseTextEntity->Update();
        }
    }
    else
    {
        // PAUSE
        if (!this->saveManager->IsFlagMaskEnabledAny(0x1000)
            && (this->inputProcessor->newButtonPressesMask & 2) != 0
            && this->scenePhaseIndex == 1)
        {
            // bpanic_stop_midi();
            // SoundResourceManager_Pause(this->base.sceneSoundManager);

            this->pauseTextEntity->AttachWithPosition(320, 240, 0);
            this->paused = true;
        }

        this->levelManagerObject->Update();
    }
}
