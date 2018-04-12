#include "Ingame_Stage1_Scene.hpp"
#include "../../Entity/Generic/TileSetEntity.hpp"
#include "../../Manager/BitmapResourceManager.hpp"

Ingame_Stage1_Scene::Ingame_Stage1_Scene(SaveManager* aSaveManager)
    : Ingame_BasicStage_Scene(nullptr, aSaveManager)
{
    this->LoadTileSets();
    this->AttachEntities();
}

Ingame_Stage1_Scene::~Ingame_Stage1_Scene()
{
}

void Ingame_Stage1_Scene::LoadTileSets()
{
    // TODO: Create Metadata
    this->stageBackgroundTileSetEntity = new TileSetEntity(this, this->sceneBitmapMgr->bitmapPtrs[38], nullptr); // BMP_BG_STG01
}
