#include <iostream>

#include "Player.h"
#include "InputEventHandler.h"

Player::Player(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform, InputEventHandler *handler)
    : WorldObject(name, shader, texture, mesh, transform)
{
    m_handler = handler;
    handler->RegisterKeyboardListener(this);

    m_speed = 0.05;
    m_RotationSpeed = 0.05;
}

//@NOTE: This now only handles special events, outside of the keys defined in InputEventhandler.h
void Player::NotifyKeyEvent(SDL_Event e) {
    switch (e.type) {
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym) {
                case SDLK_RETURN:
                {
                    //@Refactor, this isnt clean as this positio / orientation may not always be the right way.
                    m_transform.SetRotation(-3.14 / 2, 3.14, 0);
                    m_transform.SetPos(0, 0, 0);
                    break;
                }//End case RETURN

            }//End switch keysym

        }//End case KEYDOWN

    }//End switch event type
}

void Player::Update(double delta) {
    //Check for angle modifier first
    if (keys_down[KEY_DEL]) {
        if (keys_down[KEY_UP]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(m_RotationSpeed, 0, 0);
            m_transform.SetRotation(new_angle);
        }
        if (keys_down[KEY_DOWN]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(-m_RotationSpeed, 0, 0);
            m_transform.SetRotation(new_angle);
        }
        if (keys_down[KEY_LEFT]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(0, 0, m_RotationSpeed);
            m_transform.SetRotation(new_angle);
        }
        if (keys_down[KEY_RIGHT]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(0, 0, -m_RotationSpeed);
            m_transform.SetRotation(new_angle);
        }
        if (keys_down[KEY_RCTRL]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(0, -m_RotationSpeed, 0);
            m_transform.SetRotation(new_angle);
        }
        if (keys_down[KEY_NUM0]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(0, m_RotationSpeed, 0);
            m_transform.SetRotation(new_angle);
        }
    }
    else {
        //Forward
        if (keys_down[KEY_UP]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(0, m_speed, 0);
            m_transform.SetPos(new_pos);
        }
        //Down
        if (keys_down[KEY_DOWN]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(0, -m_speed, 0);
            m_transform.SetPos(new_pos);
        }
        //Left
        if (keys_down[KEY_LEFT]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(-m_speed, 0, 0);
            m_transform.SetPos(new_pos);
        }
        //Right
        if (keys_down[KEY_RIGHT]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(m_speed, 0, 0);
            m_transform.SetPos(new_pos);
        }
        //Up
        if (keys_down[KEY_RCTRL]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(0, 0, m_speed);
            m_transform.SetPos(new_pos);
        }
        //Down
        if (keys_down[KEY_NUM0]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(0, 0, -m_speed);
            m_transform.SetPos(new_pos);
        }

    }

}


Player::~Player()
{
    m_handler->RemoveKeyboardListener(this);
}
