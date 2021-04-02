//
// Created by shifeng on 3/18/21.
//

#include "Mesh.h"
#include <vector>

Mesh::Mesh() : m_vertexArrayBuffers{0}, m_vertexArrayObject(0), m_drawCount(0) {}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices){
    m_drawCount = numVertices;

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);  // Bind or mount into GL

    std::vector<glm::vec3> positions;

    positions.reserve(numVertices);

    // split the composite list of texture and positions into separate lists
    for(unsigned int i = 0; i< numVertices; i++){
        positions.push_back(*vertices[i].GetPos());
    }

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);  // give data to GPU
    glEnableVertexAttribArray(0);  // how to interpret attribute, 0 is normal sequential data attribute list.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // how to actually read each attribute

    glBindVertexArray(0);  // unmount the vertex object from GL machine once done.
}

Mesh::Mesh(const Mesh& other) {
    // FIX
    m_drawCount = other.m_drawCount;
    m_vertexArrayObject = other.m_vertexArrayObject;

    for (GLuint i = 0; i < NUM_BUFFERS; ++i)
        m_vertexArrayBuffers[i] = other.m_vertexArrayBuffers[i];
}

void Mesh::operator=(const Mesh& other) {
    m_drawCount = other.m_drawCount;
    m_vertexArrayObject = other.m_vertexArrayObject;

    for (GLuint i = 0; i < NUM_BUFFERS; ++i)
        m_vertexArrayBuffers[i] = other.m_vertexArrayBuffers[i];
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
}

void Mesh::draw() {
    glBindVertexArray(m_vertexArrayObject);

    glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
    // glDrawArrays(GL_QUADS,0, m_drawCount);
    glBindVertexArray(0);
}

void Mesh::drawQuads() {
    // draw quadrilaterals
    glBindVertexArray(m_vertexArrayObject);
    glDrawArrays(GL_QUADS,0, m_drawCount);
    glBindVertexArray(0);
}




//GL_POINT?
