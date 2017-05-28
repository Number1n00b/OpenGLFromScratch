#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"

class Drawable
{
    public:
        Drawable(Shader *shader, Texture *texture, Mesh *mesh);

        virtual void Draw() = 0;

        //The camera input is to extract how the object should be drawn; from which perspective, and should be the same for all drawable objects.
        static Camera *s_camera;

        static void SetCamera(Camera* cam);

        ~Drawable();

    protected:
        //Flag to ensure camera is always set.
        static bool camera_set;

        //Position and orientation in worldspace.
        Transform m_transform;

        //The shader to use when drawing this object.
        Shader *m_shader;

        //Which texture the object should be drawn with.
        Texture *m_texture;

        //The mesh of the object which will be drawn.
        Mesh *m_mesh;

};

