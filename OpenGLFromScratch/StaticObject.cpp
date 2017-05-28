
#include "StaticObject.h"
#include "WorldObject.h"

StaticObject::StaticObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform)
    : WorldObject(name, shader, texture, mesh, transform)
{
    //Empty
}

void StaticObject::Update(double delta) {
    //Empty
}

StaticObject::~StaticObject() {
    //Empty
}