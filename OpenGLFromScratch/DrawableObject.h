#pragma once

#include "WorldObject.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"

class DrawableObject : public WorldObject
{
    public:
        DrawableObject(std::string name, Shader* shader, Texture *texture, Mesh *mesh, Transform transform);

        virtual void Draw();

        Transform& GetTransform();

        //The camera input is to extract how the object should be drawn; from which perspective, and should be the same for all drawable objects.
        static Camera *s_camera;

        static void SetCamera(Camera* cam);

        ~DrawableObject();

    protected:
        //Flag to ensure camera is always set.
        static bool camera_set;

        //The shader to use when drawing this object.
        Shader *m_shader;

        //Which texture the object should be drawn with.
        Texture *m_texture;

        //The mesh of the object which will be drawn.
        Mesh *m_mesh;
};


