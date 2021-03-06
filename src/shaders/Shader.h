#pragma once

#include <string>
#include <GL/glew.h>

#include "../model/Transform.h"
#include "../model/Camera.h"

class Shader{
	public:
		Shader(const std::string& file_name);

		void Bind();
		void Update(const Transform& transform, const Camera& camera);

		virtual ~Shader();

	private:
		//One for vertex and one for fragment. (Could also have 'geometry shaders').
        enum shaders{
            VERTEX,
            FRAGMENT,

            NUM_SHADERS
        };

		//Just a way to refer to all our uniform variables for the shader.
		enum uniforms{
			TRANSFORM_U,

			NUM_UNIFORMS
		};

		GLuint m_program;
		GLuint m_shaders[NUM_SHADERS];
		GLuint m_uniforms[NUM_UNIFORMS];
};
