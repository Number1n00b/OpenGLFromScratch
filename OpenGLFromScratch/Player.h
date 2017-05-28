#pragma once

#include <SDL.h>

#include "WorldObject.h"
#include "KeyboardListener.h"
#include "InputEventHandler.h"

class Player : public WorldObject, public KeyboardListener
{
    public:
        Player(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform, InputEventHandler *handler);

        void NotifyKeyEvent(SDL_Event e);

        void Update(double delta);

        ~Player();

    private:
        InputEventHandler *m_handler;

        float m_speed;

        float m_RotationSpeed;

};

