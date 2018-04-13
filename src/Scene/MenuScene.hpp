#pragma once

#include "GameScene.hpp"

class SaveManager;
class BitmapResourceManager;
class SoundResourceManager;
class StaticPictureEntity;
class IntroCutSceneEntity;

struct MenuScene_RenderMeta
{
    static const RenderMeta* TitleEntity_RenderMetaPtr;
    static const RenderMeta* YamadaCopyrightEntity_RenderMetaPtr;
    static const RenderMeta* MenuOptionsEntity_RenderMetaPtr;
    static const RenderMeta* OptionLabelEntity_RenderMetaPtr;
    static const RenderMeta* MenuCursorEntity_RenderMetaPtr;
    static const RenderMeta* SelectCursorEntity_RenderMetaPtr;
    // static const void** TitleEntity_RenderMetaPtr;
};

class MenuScene : public GameScene
{
    public:
        int8_t cutScenePhase;
        int8_t field_8D9;
        int16_t menuChoice;
        int32_t cutSceneRenderDataPtrIndex;
        int32_t dword8E0;
        SaveManager* saveManager;
        StaticPictureEntity* titleEntity;
        int32_t gap8D8;
        StaticPictureEntity* yamadaCopyrightEntity;
        StaticPictureEntity* menuOptionsEntity;
        StaticPictureEntity* optionLabelEntity;
        StaticPictureEntity* menuCursorEntity;
        StaticPictureEntity* selectCursorEntity;
        IntroCutSceneEntity* introCutSceneObject;
        // TileSetEntity* fontCharsetEntity;
        void* fontCharsetEntity;
        BitmapResourceManager* sceneBitmapMgr;
        SoundResourceManager* sceneSoundMgr;
        InputProcessorBase* inputProcessorMenu; // I think this is redundant but I'll keep it here
        StaticPictureEntity* fontGlyphEntities[16];
        int8_t byte958;
        int8_t byte959;

        MenuScene(SaveManager* aSaveManager);
        virtual ~MenuScene();

        void CreateEntities();

        // VTable
        int GetNextSceneIDReference() override;

        virtual void MakeSureImagesAreReady();

        // virtual void UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount) override;

        virtual void Update() override;
        // END OF VTable

        void InitCutSceneObject();
        void CutSceneObject_F2();
        void CutSceneObject_F3();
        void CutSceneObject_F4();
        void CutSceneObject_F5();
        void CutSceneObject_F6();

        void InitMainMenu();
};
