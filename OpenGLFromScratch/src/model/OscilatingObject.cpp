#include <iostream>

#include "OscilatingObject.h"

OscilatingObject::OscilatingObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform, glm::vec3 axis, float speed, float amplitude)
    : WorldObject(name, shader, texture, mesh, transform)
{
    m_Speed = speed;
    m_Axis = axis;
    m_Counter = 0;

    m_Amp = amplitude;
}


void OscilatingObject::Update() {
    GetTransform().SetPos(m_Axis * (m_Amp * sinf(m_Counter)));
    
    m_Counter += m_Speed;
}


OscilatingObject::~OscilatingObject()
{
    //Empty
}
