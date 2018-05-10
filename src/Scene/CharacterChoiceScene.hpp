#pragma once

#include <cstdint>
#include "Globals.hpp"
#include "Scene/GameScene.hpp"

class SaveManager;
class BitmapResourceManager;
class SoundResourceManager;
class StaticPictureEntity;
class TileSetEntity;

struct CharacterChoiceScene_Meta
{
    static const RenderMeta SelectTextEntity_RenderMeta;
    static const RenderMeta SelectSubtextsEntity_RenderMeta;
    static const RenderMeta SelectionCursorEntity_RenderMeta;
    static const RenderMeta UnknownStageSymbol_RenderMeta;
    static const RenderMeta PlayerPortraitEntity_RenderMeta;

    static const TileMeta BGSelect_TileMeta;
};

class CharacterChoiceScene : public GameScene
{
    public:
        bool tobiSelected;
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
