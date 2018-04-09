#include "IntroCutSceneEntity.hpp"
#include "../../Globals.hpp"
#include "../../SDL2_Interface.hpp"
#include "../../Resource/Bitmap.hpp"
#include <iostream>
#include <stdlib.h>

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
    : Entity(aScene, aBitmap, IntroCutSceneEntity_RenderMeta::RenderMetaPtr)
{
    this->byte64 = 0;
    this->byte65 = 0;
    this->byte66 = 0;
    this->stretchOffset = 1;
    this->stretchAcceleration = 0;
    this->ddSurface = gSys.CreateSurface(160, 160);

    // TODO: Set palette of ddSurface using aScene->palette2

    // Set transparent color key to black
    SDL_SetColorKey(this->ddSurface, SDL_TRUE, SDL_MapRGB(this->ddSurface->format, 0, 0, 0));

    if (!this->attachedToLayer)
        this->layerIndex = 1;
}

IntroCutSceneEntity::~IntroCutSceneEntity()
{
}

// Disclaimer: I do not understand this logic... :D
void IntroCutSceneEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    if (this->byte64 == 1)
    {
        this->stretchOffset += this->stretchAcceleration;

        if (this->stretchOffset < 80)
        {
            this->stretchAcceleration++;
        }
        else
        {
            this->stretchOffset = 80;
            this->byte65 = 1;
            this->byte64 = 0;
        }
    }
    else if (this->byte64 == 2)
    {
        this->stretchOffset -= this->stretchAcceleration;

        if (this->stretchOffset > 0)
        {
            this->stretchAcceleration--;
        }
        else
        {
            this->stretchOffset = 1;
            this->byte66 = 1;
            this->byte64 = 0;
        }
    }
}

// TODO: Adept to Texture rendering to speed things up
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

    dstRect.left = 80 - this->stretchOffset;
    dstRect.right = 80 + this->stretchOffset;
    dstRect.top = 0;
    dstRect.bottom = 160;

    SDL_Rect srcRectSDL = srcRect.ToSDLRect();
    SDL_Rect dstRectSDL = dstRect.ToSDLRect();

    // Clear surface
    SDL_FillRect(this->ddSurface, NULL, SDL_MapRGB(this->ddSurface->format, 0, 0, 0));

    // Render one square (current character in cutscene)
    int32_t result = SDL_BlitScaled(this->entityImageBmp->SDL_surface, &srcRectSDL, this->ddSurface, &dstRectSDL);

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
    this->stretchOffset = 1;
    this->stretchAcceleration = 0;
}

void IntroCutSceneEntity::F_4146A0(uint16_t aRenderDataPtrIndex)
{
    this->AssignRenderRectangles(aRenderDataPtrIndex);
    this->byte65 = 1;
    this->byte64 = 0;
    this->byte66 = 0;
    this->stretchOffset = 80;
}

void IntroCutSceneEntity::F_4146D0()
{
    this->byte64 = 2;
    this->byte66 = 0;
    this->byte65 = 0;
    this->stretchOffset = 80;
}

// ------ IntroCutSceneEntity RenderMeta START ------
static const uint16_t RenderMeta_1_1[] =
{
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t RenderMeta_1_2[] =
{
    1,
    2,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t RenderMeta_1_3[] =
{
    1,
    3,
    1,
    0,
    0,
    0,
    0,
    0
};

static const void* RenderMeta_1[] =
{
    &RenderMeta_1_1,
    &RenderMeta_1_2,
    &RenderMeta_1_3,
    0
};

static const MSRect RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0xA0, 0xA0 },
    { 0xA0, 0, 0x140, 0xA0 },
    { 0x140, 0, 0x1E0, 0xA0 }
};

static const MSRect RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -80, -80, 80, 80 } // lengths to sides (dimensions)
};

static const void* RenderMeta[] =
{
    &RenderMeta_1,
    &RenderMeta_2,
    &RenderMeta_3,
    ((void*) gConsts::RenderMetaTerminatorPtr)
};

const uint32_t** IntroCutSceneEntity_RenderMeta::RenderMetaPtr = (const uint32_t**) RenderMeta;
// ------ IntroCutSceneEntity RenderMeta END ------
