#include "Entity_base.hpp"

Entity_base::Entity_base()
{
    this->nextAttachedEntity = nullptr;
    this->previousAttachedEntity = nullptr;
    this->layerIndex = 2;
    this->dword10 = 1;
    this->centerX = 0;
    this->centerY = 0;
    this->dword1C_coordinateLikeThingie = 0;
}

Entity_base::~Entity_base()
{
}