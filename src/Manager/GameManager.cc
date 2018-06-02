#include <iostream>

#include "Scene/GameScene.hpp"
#include "Scene/LogoScene.hpp"
#include "Scene/MenuScene.hpp"
#include "Scene/CharacterChoiceScene.hpp"
#include "Scene/Stages/Ingame_Stage1_Scene.hpp"
#include "Scene/Stages/Ingame_Stage2_Scene.hpp"
#include "Scene/Stages/Ingame_Stage3_Scene.hpp"
#include "Scene/Stages/Ingame_Stage4_Scene.hpp"
#include "Scene/Stages/Ingame_Stage5_Scene.hpp"
#include "Manager/GameManager.hpp"
#include "Manager/SaveManager.hpp"
#include "Input/InputProcessorBase.hpp"

GameManager::GameManager()
{
    this->currentSceneObjectPtr = nullptr;
    this->saveManager = nullptr;
    this->sceneState = 0;
    this->currentSceneID = 0;
    this->word14 = 0;
    this->nextDemoplayStage = 0;
    this->saveManager = new SaveManager();

    // Render an empty frame and flip it
    gSys.PerformEmptyBackSurfaceBlt();
    gSys.Flip();
}

GameManager::~GameManager()
{
    if (this->currentSceneObjectPtr != nullptr)
    {
        delete this->currentSceneObjectPtr;
        this->currentSceneObjectPtr = nullptr;
    }

    if (this->saveManager != nullptr)
    {
        delete this->saveManager;
        this->saveManager = nullptr;
    }
}

void GameManager::Update()
{
    gSys.PerformEmptyBackSurfaceBlt();

    switch (this->sceneState)
    {
        case 0:
            this->LoadNewScene();
            break;
        case 1:
            this->Tick();
            break;
        case 2:
            this->ChangeScene();
            break;
        default:
            break;
    }
}

bool GameManager::LoadNewScene()
{
    std::cout << "GameManager::LoadNewScene : " << this->currentSceneID << std::endl;
    GameScene* newScene = (GameScene*) nullptr;

    switch (this->currentSceneID)
    {
        case GameSceneID_Logo:
            newScene = new LogoScene(this->saveManager);
            break;
        case GameSceneID_Menu:
            newScene = new MenuScene(this->saveManager);
            break;
        case GameSceneID_Demoplay:
            this->saveManager->CreatePlayerObjects();
            this->saveManager->nextStage = this->nextDemoplayStage;
            this->saveManager->nextLevel = 0;

            if (this->nextDemoplayStage == 1)
            {
                this->saveManager->saveFlags = 0x1102;

                this->saveManager->playerObject1.characterSelected = 0; // Doka
                this->saveManager->playerObject2.characterSelected = 1; // Tobi

                this->currentSceneID = GameSceneID_Ingame_Stage2;
                this->nextDemoplayStage = 0;
                newScene = new Ingame_Stage2_Scene(this->saveManager);
            }
            else
            {
                this->saveManager->saveFlags = 0x1101;
                this->saveManager->playerObject1.characterSelected = 0; // Doka

                this->currentSceneID = GameSceneID_Ingame_Stage1;
                newScene = new Ingame_Stage1_Scene(this->saveManager);
            }
            break;
        case GameSceneID_CharacterChoice:
            newScene = new CharacterChoiceScene(this->saveManager);
            this->saveManager->saveFlags |= 0x100;
            break;
        case GameSceneID_Scoreboard:
            // newScene = new ScoreboardScene(this->saveManager);
            break;
        case GameSceneID_StageStatus:
            // newScene = new StageStatusScene(this->saveManager);
            break;
        case GameSceneID_AfterGameCredits:
            // newScene = new AfterGameCreditsScene(this->saveManager);
            break;
        case GameSceneID_Ingame_Stage1:
            newScene = new Ingame_Stage1_Scene(this->saveManager);
            break;
        case GameSceneID_Ingame_Stage2:
            newScene = new Ingame_Stage2_Scene(this->saveManager);
            break;
        case GameSceneID_Ingame_Stage3:
            newScene = new Ingame_Stage3_Scene(this->saveManager);
            break;
        case GameSceneID_Ingame_Stage4:
            newScene = new Ingame_Stage4_Scene(this->saveManager);
            break;
        case GameSceneID_Ingame_Stage5:
            newScene = new Ingame_Stage5_Scene(this->saveManager);
            break;
    }

    this->currentSceneObjectPtr = newScene;

    if (!this->currentSceneObjectPtr || !this->currentSceneObjectPtr->init_OK)
    {
        // bpanic_ShowError_wrapper(8019, 1, memAllocFailStr);// If malloc failed or palette loading failed
        return false;
    }

    this->sceneState = 1;

    // this is a bit weird since there was no rendering for this frame but original code does this
    gSys.Flip();

    return true;
}

bool GameManager::Tick()
{
    InputProcessorBase* input = this->currentSceneObjectPtr->inputProcessor;
    
    // Record current inputs and store it in the bitmask
    if (input != nullptr)
        input->Tick();

    // Renders frame and updates the scene
    this->currentSceneObjectPtr->Tick();

    // if the scene finished, go to ChangeScene()
    if (this->currentSceneObjectPtr->finished)
        this->sceneState = 2;

    // Flip is logical here, it pushes out the freshly rendered frame
    gSys.Flip();
    return true;
}

bool GameManager::ChangeScene()
{
    int reference = this->currentSceneObjectPtr->GetNextSceneIDReference();
    int newSceneID = gConsts::referenceToSceneID_Linker[reference];

    std::cout << "GameManager::ChangeScene to " << newSceneID << std::endl;

    this->sceneState = 0;
    this->currentSceneID = newSceneID;
    
    if (this->currentSceneObjectPtr)
    {
        delete this->currentSceneObjectPtr;
        this->currentSceneObjectPtr = nullptr;
    }

    // Render empty frame and push it
    gSys.PerformEmptyBackSurfaceBlt();
    gSys.Flip();

    return true;
}