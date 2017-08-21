#include <iostream>

#include "RotatingObject.h"
#include "Util.h"


RotatingObject::RotatingObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform, glm::vec3 axis, float speed)
    : WorldObject(name, shader, texture, mesh, transform)
{
    m_Speed = speed;
    m_Axis = axis;

    m_start_angle = transform.GetRotation();
}


void RotatingObject::Update(double delta) {
    glm::vec3 new_rotation = GetTransform().GetRotation() + m_Axis * float(delta / 1000 * m_Speed / 180 * M_PI);

    GetTransform().SetRotation(new_rotation);
}


RotatingObject::~RotatingObject()
{
    //Empty
}
