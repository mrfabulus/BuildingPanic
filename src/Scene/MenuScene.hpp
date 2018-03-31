#pragma once

#include "GameScene.hpp"

class SaveManager;
class BitmapResourceManager;
class SoundResourceManager;
class StaticPictureEntity;
class IntroCutSceneEntity;


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
        InputProcessorBase* inputProcessor;
        StaticPictureEntity* fontGlyphEntities[16];
        int8_t byte958;
        int8_t byte959;

        MenuScene(SaveManager* aSaveManager);

        void CreateEntities();

        int GetNextSceneIDReference() override;

        virtual void F3();

        virtual void F4() override;

        virtual void Update() override;
};
