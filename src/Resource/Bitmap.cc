#include "Bitmap.hpp"

Bitmap::Bitmap()
{
    this->refCount = 0;
}

void Bitmap::incRefCount()
{
    if (this->refCount == 0)
    {
        // TODO: create new OSS
    }

    this->refCount++;
}

void Bitmap::decRefCount()
{
    this->refCount--;

    if (this->refCount == 0)
    {
        // TODO: release OSS
    }
}

