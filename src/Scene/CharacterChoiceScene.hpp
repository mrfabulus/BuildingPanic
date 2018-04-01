#pragma once

#include <cstdint>
#include "GameScene.hpp"

class SaveManager;
class BitmapResourceManager;
class SoundResourceManager;
class StaticPictureEntity;

class CharacterChoiceScene : public GameScene
{
    public:
        int8_t byte8D8;
        int16_t selectedStageNumber;
        int32_t dword8DC;
        SaveManager* saveMgr;
        BitmapResourceManager* sceneBitmapMgr;
        SoundResourceManager* sceneSoundMgr;
        // TileSetEntity *stageSelectTiles;
        int* stageSelectTiles;
        StaticPictureEntity* selectTextEntity;
        StaticPictureEntity* selectSubtextsEntity;
        StaticPictureEntity* selectionCursorEntity;
        StaticPictureEntity* unknownStageSymbol1;
        StaticPictureEntity* unknownStageSymbol2;
        StaticPictureEntity* unknownStageSymbol3;
        StaticPictureEntity* player1PortraitEntity;
        StaticPictureEntity* player2PortraitEntity;

        CharacterChoiceScene(SaveManager* aSaveManager);
        ~CharacterChoiceScene();

        bool CreateEntities();
        void Init();

        virtual int32_t GetNextSceneIDReference() override;

        virtual void MakeSureImagesAreReady();

        // Not overridden
        // virtual void UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount) override;

        virtual void Update() override;
};