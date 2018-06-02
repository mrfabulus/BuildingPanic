#include "Entity/Stage/PlayerEntity.hpp"
#include "Entity/Generic/StaticPictureEntity.hpp"
#include "Manager/BitmapResourceManager.hpp"
#include "Manager/SoundResourceManager.hpp"
#include "Scene/Stages/Ingame_Stage_Scene.hpp"

PlayerEntity::PlayerEntity(Ingame_Stage_Scene* aScene, BitmapResourceManager* aBmpMgr, int aCharacterChosen, SoundResourceManager* aSndMgr, int a6)
    : AnimatedEntity(aScene, aBmpMgr->bitmapPtrs[aCharacterChosen], nullptr, aBmpMgr->bitmapCachePtrs[aCharacterChosen])
{
    this->double80 = 0;
    this->dword88 = 0;
    this->byte68 = aCharacterChosen;
    this->byte69 = 0;
    this->byte6A = 0;
    this->byte6B = 0;
    this->byte6C = 0;
    this->byte6D = 0;
    this->unsigned6E = 3;
    this->dword70 = 0;
    this->dword74 = 0;
    this->dword78 = 0;
    this->dword7C = a6;
    this->dword8C = 0;
    this->dword90 = 0;
    this->extraPositionData = 0;
    this->dword98 = 0;
    this->dword9C = nullptr;
    this->piyoBmp = 0;
    this->dwordA4 = 0;
    this->hitBmp = 0;
    this->sndMgr = aSndMgr;
    this->dwordBC = 0;

    this->piyoBmp = new StaticPictureEntity(aScene, aBmpMgr->bitmapPtrs[18], nullptr, 0);
    this->piyoBmp->dword10 = 0;

    this->hitBmp = new StaticPictureEntity(aScene, aBmpMgr->bitmapPtrs[20], nullptr, 0);
    this->hitBmp->SetLayerIndex(3);
    this->hitBmp->coordinateLikeThingie = 10;
    this->hitBmp->dword10 = 0;

    for (int i = 3; i > 0; i--)
    {
        // TODO: Create something??
    }

    this->extraPositionData = new EntityExtraPositionData3(this);

    // this->dword98 = new ???

    this->coordinateLikeThingie = 100 * this->unsigned6E + 20;
    this->AssignRenderRectangles(0);
}

PlayerEntity::~PlayerEntity()
{
    
}

void PlayerEntity::Update()
{
    if (!this->attachedToLayer)
        return;
    
    this->extraPositionData->ReassignPositionToEntity();

    if (this->byte69 != 0)
    {
        this->dword70--;

        if (this->dword70 == 0)
        {
            // TODO: call something
        }
    }

    switch (this->byte6A)
    {
        case 0:
            this->extraPositionData->double2 = 0;

            if (this->byte6B)
            {

            }
            else
            {
                this->AssignRenderRectangles(0);
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        default:
            break;
    }

    if (this->dword78 != 0)
        this->dword78--;

    this->AssignRenderRectanglesAdvanced();
    this->byte6B = 0;
    this->word5C = 0;
}

void PlayerEntity::Render()
{
    if ((this->dword78 & 1) == 0)
    {
        AnimatedEntity::Render();
    }
}

void PlayerEntity::SetupRenderingInformation()
{
    AnimatedEntity::SetupRenderingInformation();

    this->byte69 = 0;
    this->dword70 = 0;
    this->byte6B = 0;
    this->unsigned6E = 3;
    this->dword74 = 0;
    this->dword78 = 120;
    this->double80 = 2;
    this->dword90 = 0x1A6; // TODO: Is this correct?
    this->byte6A = 7;
    this->byte6C = 2;

    this->extraPositionData->double1 = 2;
    this->extraPositionData->double2 = 16;

    if (this->dword7C != 0)
    {
        this->extraPositionData->byte38 = -1;
    }
    else
    {
        this->extraPositionData->byte38 = 1;
    }

    this->renderCacheSurface = (this->extraPositionData->byte38 != -1);
    this->extraPositionData->byte39 = -1;

    this->AssignRenderRectangles(3);
}

void PlayerEntity::ReleaseResources()
{
    // TODO: Implement missing stuff
    if (this->byte69)
    {

    }


    AnimatedEntity::ReleaseResources();
}
