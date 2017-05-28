#pragma once

#include "WorldObject.h"

class StaticObject : public WorldObject
{
public:
    StaticObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform);

    virtual void Update(double delta);

    ~StaticObject();
};

