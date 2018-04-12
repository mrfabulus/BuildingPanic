#include "GameObject.hpp"

GameObject::GameObject()
{
    this->nextAttachedEntity = nullptr;
    this->previousAttachedEntity = nullptr;
    this->layerIndex = 2;
    this->dword10 = 1;
    this->centerX = 0;
    this->centerY = 0;
    this->coordinateLikeThingie = 0;
}

GameObject::~GameObject()
{
}

void GameObject::SetLayerIndex(uint16_t aLayerIndex)
{
    if (aLayerIndex >= 5)
    {
        this->layerIndex = 1;
    }
    else
    {
        this->layerIndex = aLayerIndex;
    }
}

void GameObject::Update()
{
}

void GameObject::Render()
{
}
