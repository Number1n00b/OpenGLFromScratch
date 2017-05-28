#include "WorldObject.h"

bool WorldObject::camera_set = false;
Camera* WorldObject::s_camera = nullptr;

void WorldObject::SetCamera(Camera *cam) {
    s_camera = cam;
    camera_set = true;
}


WorldObject::WorldObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform) {
    this->name = name;

    //Check that none of the imports are null.
    if (!shader) {
        char error_message[100];
        sprintf(error_message, "Shader for object %s was null.", name);
        std::string str_msg = error_message;
        Game::FailAndExit(str_msg);
    }
    if (!texture) {
        char error_message[100];
        sprintf(error_message, "Texture for object %s was null.", name);
        std::string str_msg = error_message;
        Game::FailAndExit(str_msg);
    }
    if (!mesh) {
        char error_message[100];
        sprintf(error_message, "Mesh for object %s was null.", name);
        std::string str_msg = error_message;
        Game::FailAndExit(str_msg);
    }

    m_shader = shader;
    m_texture = texture;
    m_mesh = mesh;
    m_transform = transform;
}


Transform& WorldObject::GetTransform() {
    return m_transform;
}


void WorldObject::Draw() {
    if (!camera_set) {
        std::cout << "!!!!!!!!!!! No camera set for Drawable class. !!!!!!!!!!!" << std::endl;
    }
    else {
        //@Speed, we shouldn't need to bind the shader every draw call, it most likely remains the same for multiple objects.
        m_shader->Bind();

        //@Speed, same for texture, multiple objects in a row could have the same texture. we should group objects with the same tecture to be drawn
        //        sequentually so that textures dont have to be swapped out as often.
        m_texture->Bind(0);

        //@Speed, the camera should remain unchanging between draw calls in a single frame, shader should not need to update it all the time.
        m_shader->Update(m_transform, *s_camera);

        //Draw the object's mesh.
        m_mesh->Draw();
    }
}

WorldObject::~WorldObject() {
    //Empty
    //@Incomplete? Should i set all class member pointers to null? I dont think so, it should be done automatically.
}