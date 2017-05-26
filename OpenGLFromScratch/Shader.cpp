#include "Shader.h"
#include <iostream>
#include <fstream>

static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string&& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	std::cout << "Creating shaders..." << std::endl;

	//Creates some space on the GPU for a program. 
	m_program = glCreateProgram();

	m_shaders[VERTEX] = CreateShader(LoadShader(fileName + ".v.glsl"), GL_VERTEX_SHADER);
	m_shaders[FRAGMENT] = CreateShader(LoadShader(fileName + ".f.glsl"), GL_FRAGMENT_SHADER);

	//Add the shaders to the program.
	for (unsigned int ii = 0; ii < NUM_SHADERS; ii++) {
		glAttachShader(m_program, m_shaders[ii]);
	}

	//Ensure 'position' is spelled the same as in the shader program itself.
    //These match up to the items defined in Mesh.cpp, each one is a VBO inside the VAO
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	//Link the program.
	glLinkProgram(m_program);

	//Check for errors.
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program failed to link: ");

	//Validate the program.
	glValidateProgram(m_program);

	//Check for errors.
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	//Set our Uniform variables.
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

void Shader::Bind() {
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera) {
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

Shader::~Shader()
{
	std::cout << "Deleting shaders..." << std::endl;

	for (int ii = 0; ii < NUM_SHADERS; ii++) {
		glDetachShader(m_program, m_shaders[ii]);
		glDeleteShader(m_shaders[ii]);
	}

	glDeleteProgram(m_program);
}

static GLuint CreateShader(const std::string&& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) {
		std::cout << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar *shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!");

	return shader;
}


static std::string LoadShader(const std::string& fileName) {
	std::ifstream file;

	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cout << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cout << errorMessage << " '" << error << "'" << std::endl;
	}
}

