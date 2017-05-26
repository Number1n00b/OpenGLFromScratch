#pragma once

#include <SDL.h>

#include "WorldObject.h"
#include "KeyboardListener.h"
#include "InputEventHandler.h"

class RotatingObject : public WorldObject
{
public:
    RotatingObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform, glm::vec3 axis, float speed);

    void Update();

    void SetSpeed(float speed);

    ~RotatingObject();

private:
    float m_Speed;
    float m_Counter;
    glm::vec3 m_start_angle;

    glm::vec3 m_Axis;
};

