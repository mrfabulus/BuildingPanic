#include "IntroCutSceneEntity.hpp"
#include "../../Globals.hpp"
#include "../../SDL2_Interface.hpp"
#include "../../Resource/Bitmap.hpp"
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

    // TODO: Handle palette and color key (?)

    if (!this->attachedToLayer)
        this->layerIndex = 1;
}

// Disclaimer: I do not understand this logic... :D
void IntroCutSceneEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    if (this->byte64 == 1)
    {
        this->dword68 += this->dword6C;

        if (this->dword68 < 80)
        {
            this->dword6C++;
        }
        else
        {
            this->dword68 = 80;
            this->byte65 = 1;
            this->byte64 = 0;
        }
    }
    else if (this->byte64 == 2)
    {
        this->dword68 -= this->dword6C;

        if (this->dword68 > 0)
        {
            this->dword6C--;
        }
        else
        {
            this->dword68 = 1;
            this->byte66 = 1;
            this->byte64 = 0;
        }
    }
}

void IntroCutSceneEntity::Render()
{
    if (!this->attachedToLayer)
        return;

    MSRect srcRect;
    MSRect dstRect;

    // copy src rectangle, no trickery
    srcRect.left = this->srcRectPtr->left;
    srcRect.top = this->srcRectPtr->top;
    srcRect.right = this->srcRectPtr->right;
    srcRect.bottom = this->srcRectPtr->bottom;

    // ugly workaround until src & dst metainfo + clipping is implemented
    srcRect.bottom += 130;

    // Don't ask me why???
    dstRect.left = 80 - this->dword68;
    dstRect.right = this->dword68 + 80;
    dstRect.top = 0;
    dstRect.bottom = 160;

    SDL_Rect srcRectSDL = srcRect.ToSDLRect();
    SDL_Rect dstRectSDL = dstRect.ToSDLRect();

    // Clear surface
    SDL_FillRect(this->ddSurface, NULL, SDL_MapRGB(this->ddSurface->format, 0, 0, 0));

    // Render one square (current character in cutscene)
    SDL_BlitSurface(this->entityImageBmp->SDL_surface, &srcRectSDL, this->ddSurface, &dstRectSDL);

    // SDL_Texture* texture = SDL_CreateTextureFromSurface(gSys.GetRenderer(), this->ddSurface);

    // Render some more
    for (int i = 0; i < 13; i++)
    {
        MSRect* partialSrcPtr = (MSRect*) &(IntroCutScene_SrcRectangles[i]);
        MSRect* partialDstPtr = (MSRect*) &(IntroCutScene_DstRectangles[i]);

        SDL_Rect partialSrcRect = partialSrcPtr->ToSDLRect();
        SDL_Rect partialDstRect = partialDstPtr->ToSDLRect();

        // SDL_RenderCopy(gSys.GetRenderer(), texture, &partialSrcRect, &partialDstRect);
        SDL_BlitSurface(this->ddSurface, &partialSrcRect, gSys.GetMainSurface(), &partialDstRect);
    }

    // SDL_DestroyTexture(texture);
}

void IntroCutSceneEntity::SetupRenderingInformation()
{
    this->AssignRenderRectangles(this->AttachedRenderDataIndex);
    this->AssignRenderRectanglesAdvanced();
}

void IntroCutSceneEntity::Custom_AssignRenderRectangles(uint16_t aRenderDataPtrIndex)
{
    this->AssignRenderRectangles(aRenderDataPtrIndex);
    this->byte64 = 1;
    this->byte66 = 0;
    this->byte65 = 0;
    this->dword68 = 1;
    this->dword6C = 0;
}

void IntroCutSceneEntity::F_4146A0(uint16_t aRenderDataPtrIndex)
{
    this->AssignRenderRectangles(aRenderDataPtrIndex);
    this->byte65 = 1;
    this->byte64 = 0;
    this->byte66 = 0;
    this->dword68 = 80;
}

void IntroCutSceneEntity::F_4146D0()
{
    this->byte64 = 2;
    this->byte66 = 0;
    this->byte65 = 0;
    this->dword68 = 80;
}
