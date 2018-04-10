#pragma once

#include <cstdint>
#include "GameScene.hpp"

class SaveManager;
class BitmapResourceManager;
class SoundResourceManager;
class StaticPictureEntity;
class TileSetEntity;

struct CharacterChoiceScene_RenderMeta
{
    static const uint32_t** SelectTextEntityPtr;
    static const uint32_t** SelectSubtextsEntityPtr;
    static const uint32_t** SelectionCursorEntityPtr;
    static const uint32_t** UnknownStageSymbolPtr;
    static const uint32_t** PlayerPortraitEntityPtr;

    static const uint32_t* BG_SelectTilePtr;
};

class CharacterChoiceScene : public GameScene
{
    public:
        int8_t byte8D8; // bool dokaSelected;
        int16_t selectedStageNumber;
        int32_t dword8DC;
        SaveManager* saveMgr;
        BitmapResourceManager* sceneBitmapMgr;
        SoundResourceManager* sceneSoundMgr;
        TileSetEntity *stageSelectTiles;
        StaticPictureEntity* selectTextEntity;
        StaticPictureEntity* selectSubtextsEntity;
        StaticPictureEntity* selectionCursorEntity;
        StaticPictureEntity* unknownStageSymbol1;
        StaticPictureEntity* unknownStageSymbol2;
        StaticPictureEntity* unknownStageSymbol3;
        StaticPictureEntity* player1PortraitEntity;
        StaticPictureEntity* player2PortraitEntity;

        CharacterChoiceScene(SaveManager* aSaveManager);
        virtual ~CharacterChoiceScene();

        bool CreateEntities();
        void Init();

        virtual int32_t GetNextSceneIDReference() override;

        virtual void MakeSureImagesAreReady();

        // Not overridden
        // virtual void UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount) override;

        virtual void Update() override;
};