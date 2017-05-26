#include <iostream>
#include <vector>

#include "Mesh.h"

Mesh::Mesh(const std::string& file_name) {
	std::cout << "Creating mesh from file: \"" << file_name << "\"..." << std::endl;
	IndexedModel model = OBJModel(file_name).ToIndexedModel();

	InitMesh(model);
}

Mesh::Mesh(Vertex *vertices, unsigned int num_vertices, unsigned int *indices, unsigned int num_indeces) {
	std::cout << "Creating mesh... " << std::endl;

	IndexedModel model;

	for (unsigned int ii = 0; ii < num_vertices; ii++) {
		model.positions.push_back(*vertices[ii].GetPos());
		model.texCoords.push_back(*vertices[ii].getTexCoord());
		model.normals.push_back(*vertices[ii].getNormal());
	}

	for (unsigned int ii = 0; ii < num_indeces; ii++){
		model.indices.push_back(indices[ii]);
	}

	InitMesh(model);

}


void Mesh::InitMesh(const IndexedModel& model) {
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	//Puts the data into the buffer.
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

    //This function defines the layout of each vertexBufferObject in the VertexArrayObject.
    //Arg list:
    //0: Which attribute number. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @NOTE: This is binded in the shader program itself. See line 25-27 in Shader.cpp. @@@@@@@@@
    //1: Number of values per item. e.g. 3 Means that each object is a vec3 made from 3 GL_FLOAT(s) in the buffer
    //2: The type of value to create objects from.
    //3: Should values be normalised?
    //4: Stride, how much data to skip between jumps.
    //5: Offset of the first component.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.positions[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}


void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);

    //Use this to draw wireframes.
    //glPolygonMode(GL_FRONT, GL_LINE);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	std::cout << "Destroying mesh... " << std::endl;

	glDeleteVertexArrays(1, &m_vertexArrayObject);
}



