#include <iostream>

#include "RotatingObject.h"


RotatingObject::RotatingObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform, glm::vec3 axis, float speed)
    : WorldObject(name, shader, texture, mesh, transform)
{
    m_Speed = speed;
    m_Axis = axis;
    m_Counter = 0;

    m_start_angle = transform.GetRotation();
}


void RotatingObject::Update(double delta) {
    GetTransform().SetRotation(m_start_angle + (m_Axis * m_Counter));

    m_Counter += m_Speed;
}


RotatingObject::~RotatingObject()
{
    //Empty
}
