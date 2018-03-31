#include "IntroCutSceneEntity.hpp"
#include "../../Globals.hpp"
#include <iostream>

static const MSRect IntroCutScene_DstRectangles[] =
{
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x0A0, 0x000, 0x140, 0x0A0 },
    { 0x140, 0x000, 0x1E0, 0x0A0 },
    { 0x1E0, 0x000, 0x280, 0x0A0 },
    { 0x000, 0x0A0, 0x050, 0x140 },
    { 0x050, 0x0A0, 0x0F0, 0x140 },
    { 0x0F0, 0x0A0, 0x190, 0x140 },
    { 0x190, 0x0A0, 0x230, 0x140 },
    { 0x230, 0x0A0, 0x280, 0x140 },
    { 0x000, 0x140, 0x0A0, 0x1E0 },
    { 0x0A0, 0x140, 0x140, 0x1E0 },
    { 0x140, 0x140, 0x1E0, 0x1E0 },
    { 0x1E0, 0x140, 0x280, 0x1E0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 }
};

static const MSRect IntroCutScene_SrcRectangles[] =
{
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x050, 0x000, 0x0A0, 0x0A0 }, // different
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x050, 0x0A0 }, // different
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 },
    { 0x000, 0x000, 0x0A0, 0x0A0 }
};

IntroCutSceneEntity::IntroCutSceneEntity(GameScene* aScene, Bitmap* aBitmap)
    : Entity(aScene, aBitmap, nullptr)
{
    this->byte64 = 0;
    this->byte65 = 0;
    this->byte66 = 0;
    this->dword68 = 1;
    this->dword6C = 0;
    this->ddSurface = gSys.CreateSurface(160, 160);


    if (!this->attachedToLayer)
        this->layerIndex = 1;
}

void IntroCutSceneEntity::Render()
{
    if (this->attachedToLayer)
        return;

    MSRect srcRect;
    MSRect dstRect;

    // copy src rectangle, no trickery
    srcRect.left = this->srcRectPtr->left;
    srcRect.top = this->srcRectPtr->top;
    srcRect.right = this->srcRectPtr->right;
    srcRect.bottom = this->srcRectPtr->bottom;

    // Don't ask me why???
    dstRect.left = 80 - this->dword68;
    dstRect.right = this->dword68 + 80;
    dstRect.top = 0;
    dstRect.bottom = 160;

    // this->surface->Render();
}

void IntroCutSceneEntity::SetupRenderingInformation()
{
    this->AssignRenderRectangles(this->AttachedRenderDataIndex);
    this->AssignRenderRectanglesAdvanced();
}
