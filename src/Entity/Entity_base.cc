#include "Entity_base.hpp"

Entity_base::Entity_base()
{
    this->nextAttachedEntity = 0;
    this->latestEntity = 0;
    this->layerIndex = 2;
    this->dword10 = 1;
    this->centerX = 0;
    this->centerY = 0;
    this->dword1C_coordinateLikeThingie = 0;
}