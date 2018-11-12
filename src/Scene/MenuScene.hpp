#pragma once

#include "GameScene.hpp"

class SaveManager;
class BitmapResourceManager;
class SoundResourceManager;
class StaticPictureEntity;
class IntroCutSceneEntity;
class TileSetEntity;

struct MenuScene_Meta
{
    static const RenderMeta TitleEntity_RenderMeta;
    static const RenderMeta YamadaCopyrightEntity_RenderMeta;
    static const RenderMeta MenuOptionsEntity_RenderMeta;
    static const RenderMeta OptionLabelEntity_RenderMeta;
    static const RenderMeta MenuCursorEntity_RenderMeta;
    static const RenderMeta SelectCursorEntity_RenderMeta;
    static const RenderMeta FontCharset_RenderMeta;
    static const TileMeta FontCharset_TileMeta;
};

class MenuScene : public GameScene
{
    public:
        int8_t cutScenePhase;
        int8_t field_8D9;
        int16_t menuChoice;
        int32_t cutSceneRenderDataPtrIndex;
        int32_t portraitFlipsLeft;
        SaveManager* saveManager;
        StaticPictureEntity* titleEntity;
        int32_t gap8D8;
        StaticPictureEntity* yamadaCopyrightEntity;
        StaticPictureEntity* menuOptionsEntity;
        StaticPictureEntity* optionLabelEntity;
        StaticPictureEntity* menuCursorEntity;
        StaticPictureEntity* selectCursorEntity;
        IntroCutSceneEntity* introCutSceneObject;
        TileSetEntity* fontCharsetEntity;
        BitmapResourceManager* sceneBitmapMgr;
        SoundResourceManager* sceneSoundMgr;
        MenuScene_InputProcessor* inputProcessorMenu;
        StaticPictureEntity* fontGlyphEntities[16];
        int8_t byte958;
        int8_t byte959; // options cursor place?

        MenuScene(SaveManager* aSaveManager);
        virtual ~MenuScene();

        void CreateEntities();

        // VTable
        int GetNextSceneIDReference() override;

        virtual void MakeSureImagesAreReady();

        // UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount) is not overridden

        virtual void Update() override;
        // END OF VTable

        void InitCutSceneObject();
        void CutSceneObject_F2();
        void CutSceneObject_F3();
        void CutSceneObject_F4();
        void CutSceneObject_F5();
        void CutSceneObject_PortraitFlip();

        void InitMainMenu();
};
